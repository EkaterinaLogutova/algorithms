#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> g, gr; // граф и обратный граф
vector<bool> used;         // посещенные вершины
vector<int> comp;          // номер компоненты для вершины
stack<int> order;          // порядок выхода

// заполняем порядок выхода
void dfs1(int v)
{
    used[v] = true;
    for (int u : g[v])
    {
        if (!used[u])
            dfs1(u);
    }
    order.push(v);
}

// раскрашиваем компоненты на обратном графе
void dfs2(int v, int cl)
{
    comp[v] = cl;
    for (int u : gr[v])
    {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

int main()
{
    int n = 4;
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};

    g.resize(n);
    gr.resize(n);
    for (auto &e : edges)
    {
        g[e.first].push_back(e.second);
        gr[e.second].push_back(e.first);
    }

    // порядок выхода
    used.assign(n, false);
    for (int i = 0; i < n; i++)
    {
        if (!used[i])
            dfs1(i);
    }

    // компоненты связности
    comp.assign(n, -1);
    int cnt = 0;
    while (!order.empty())
    {
        int v = order.top();
        order.pop();
        if (comp[v] == -1)
            dfs2(v, cnt++);
    }

    // граф уже сильно связный?
    if (cnt == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    // степени компонент
    vector<int> in(cnt, 0), out(cnt, 0);
    for (int v = 0; v < n; v++)
    {
        for (int u : g[v])
        {
            if (comp[v] != comp[u])
            {
                out[comp[v]]++;
                in[comp[u]]++;
            }
        }
    }

    // источники и стоки
    int no_in = 0, no_out = 0;
    for (int i = 0; i < cnt; i++)
    {
        if (!in[i])
            no_in++;
        if (!out[i])
            no_out++;
    }

    // Ответ - макс источников и стоков
    cout << max(no_in, no_out) << endl;

    return 0;
}