#include <iostream>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Vertex
{
public:
    virtual ~Vertex() {}
    virtual int num_inputs() const = 0;
    virtual void set_input(int inp_idx, double inp_val) = 0;
    virtual int num_outputs() const = 0;
    virtual double get_output(int out_idx) = 0;
    virtual void calc_value() = 0;
};

struct Edge
{
    int out_vertex_id;
    int out_port_id;
    int inp_vertex_id;
    int inp_port_id;
};

class CalcGraph : public Vertex
{
private:
    std::vector<Vertex *> vertices;
    std::vector<Edge> edges;
    // для быстрого поиска ребер по номеру вершины и порта входа
    std::unordered_map<int, std::unordered_map<int, Edge>> input_edges_map;
    // свободные порты ввода и вывода графа, которые не связаны рёбрами
    std::vector<std::pair<int, int>> free_inputs; // (vertex_id, port_id)
    std::vector<std::pair<int, int>> free_outputs;

    std::vector<int> indegree;                              // кол-во входящих рёбер для каждой вершины
    std::vector<std::vector<std::pair<int, int>>> adj_list; // список смежности

    std::vector<double> external_inputs; // внешние значения входов

    bool sorted = false;
    std::vector<int> topo_order;

public:
    void set_data(const std::vector<Vertex *> &vertex, const std::vector<Edge> &edge)
    {
        vertices = vertex;
        edges = edge;

        input_edges_map.clear();
        free_inputs.clear();
        free_outputs.clear();
        indegree.clear();
        adj_list.clear();
        topo_order.clear();

        int n = (int)vertices.size();
        indegree.resize(n, 0);
        adj_list.resize(n);

        std::unordered_map<int, std::unordered_set<int>> connected_inputs;
        std::unordered_map<int, std::unordered_set<int>> connected_outputs;

        for (const auto &e : edges)
        {
            input_edges_map[e.inp_vertex_id][e.inp_port_id] = e; // по входу вершины находим ребро
            connected_inputs[e.inp_vertex_id].insert(e.inp_port_id);
            connected_outputs[e.out_vertex_id].insert(e.out_port_id);

            adj_list[e.out_vertex_id].push_back({e.inp_vertex_id, e.inp_port_id}); // связь для обхода
            indegree[e.inp_vertex_id]++;
        }
        // находим свободные входы, не занятые рёбрами
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < vertices[i]->num_inputs(); j++)
            {
                if (connected_inputs[i].count(j) == 0)
                {
                    free_inputs.push_back({i, j});
                }
            }
        }
        // и выходы
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < vertices[i]->num_outputs(); j++)
            {
                if (connected_outputs[i].count(j) == 0)
                {
                    free_outputs.push_back({i, j});
                }
            }
        }

        external_inputs.resize(free_inputs.size(), 0.0);

        topological_sort();
        sorted = true;
    }

    int num_inputs() const override
    {
        return (int)free_inputs.size();
    }
    // ф-я устанавливает значение на внешний вход графа по индексу
    void set_input(int inp_idx, double inp_val) override
    {
        if (inp_idx < 0 || inp_idx >= (int)free_inputs.size())
            throw std::out_of_range("Bad inp_idx in CalcGraph::set_input");
        external_inputs[inp_idx] = inp_val;
    }

    int num_outputs() const override
    {
        return (int)free_outputs.size();
    }
    // получение значения с внешнего выхода графа
    double get_output(int out_idx) override
    {
        if (out_idx < 0 || out_idx >= (int)free_outputs.size())
            throw std::out_of_range("Bad out_idx in CalcGraph::get_output");
        auto &p = free_outputs[out_idx];
        return vertices[p.first]->get_output(p.second);
    }

    void calc_value() override
    {
        if (!sorted)
        {
            throw std::runtime_error("Graph data not set or not sorted");
        }
        // внешние входы - по соотв. внутренним вершинам
        for (int i = 0; i < (int)free_inputs.size(); i++)
        {
            auto &p = free_inputs[i];
            vertices[p.first]->set_input(p.second, external_inputs[i]);
        }

        for (int v : topo_order)
        { // для каждого входа вершины, если он связан ребром, подставляем значение с выхода другой вершины
            for (int inp_i = 0; inp_i < vertices[v]->num_inputs(); inp_i++)
            {
                if (input_edges_map[v].count(inp_i) > 0)
                {
                    Edge &e = input_edges_map[v][inp_i];
                    double val = vertices[e.out_vertex_id]->get_output(e.out_port_id);
                    vertices[v]->set_input(inp_i, val);
                }
            }
            vertices[v]->calc_value(); // обновляем выход своего значения
        }
    }

private:
    void topological_sort()
    {
        std::queue<int> q;
        std::vector<int> temp_indegree = indegree;
        // сначала кладем вершины без входящих рёбер
        for (int i = 0; i < (int)temp_indegree.size(); i++)
        {
            if (temp_indegree[i] == 0)
                q.push(i);
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            topo_order.push_back(u);
            // уменьшаем степень входа каждой вершины, пока она не станет 0.
            // затем добавляем ее в очередь
            for (auto &w : adj_list[u])
            {
                int v = w.first;
                if (--temp_indegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }

        if (topo_order.size() != vertices.size())
        {
            throw std::runtime_error("Graph has cycles or disconnected components");
        }
    }
};

class PlusOperator : public Vertex
{
    double m_inp_val[2] = {0};
    double m_out_val = 0;

public:
    int num_inputs() const override
    {
        return 2;
    }

    void set_input(int inp_idx, double inp_val) override
    {
        if (inp_idx < 0 || inp_idx >= 2)
            throw std::out_of_range("Bad inp_idx in PlusOperator::set_input");
        m_inp_val[inp_idx] = inp_val;
    }

    void calc_value() override
    {
        m_out_val = m_inp_val[0] + m_inp_val[1];
    }

    int num_outputs() const override
    {
        return 1;
    }

    double get_output(int out_idx) override
    {
        if (out_idx != 0)
            throw std::out_of_range("Bad out_idx in PlusOperator::get_output");
        return m_out_val;
    }
};

int main()
{
    // создаем графи из двух "+"" вершин
    CalcGraph cg;
    std::vector<Vertex *> vertex;
    std::vector<Edge> edges;

    vertex.push_back(new PlusOperator); // id 0
    vertex.push_back(new PlusOperator); // id 1
    // выход вершины 0 на вход вершины 1
    edges.push_back({0, 0, 1, 0});

    cg.set_data(vertex, edges);

    std::cout << "num of inputs: " << cg.num_inputs() << std::endl;
    std::cout << "num of outputs: " << cg.num_outputs() << std::endl;

    cg.set_input(0, 1.0);
    cg.set_input(1, 2.0);
    cg.set_input(2, 3.0);

    cg.calc_value();

    std::cout << "Output: " << cg.get_output(0) << std::endl; // 1+2+3 = 6

    for (auto v : vertex)
        delete v;
    return 0;
}
