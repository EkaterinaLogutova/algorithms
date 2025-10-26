#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> validArrangement(vector<vector<int>> &pairs)
    {
        // строим граф и считаем степени вершин
        unordered_map<int, vector<int>> graph;
        unordered_map<int, int> degree;

        for (auto &p : pairs)
        {
            graph[p[0]].push_back(p[1]);
            degree[p[0]]++; // исходящая степень +
            degree[p[1]]--; // входящая степень -
        }

        // ищем стартовую вершину - ту, у которой исходящих ребер больше
        int start = pairs[0][0];
        for (auto &[node, deg] : degree)
        {
            if (deg == 1)
            {
                start = node;
                break;
            }
        }

        // dfs для нахождения эйлерова пути
        vector<int> path;
        stack<int> st;
        st.push(start);

        while (!st.empty())
        {
            int node = st.top();
            if (!graph[node].empty())
            {
                // берем следующее ребро
                int next = graph[node].back();
                graph[node].pop_back();
                st.push(next);
            }
            else
            {
                // все ребра использованы - добавляем в путь
                path.push_back(node);
                st.pop();
            }
        }

        reverse(path.begin(), path.end());

        // преобразуем путь в пары
        vector<vector<int>> result;
        for (int i = 0; i < path.size() - 1; i++)
        {
            result.push_back({path[i], path[i + 1]});
        }

        return result;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> pairs1 = {{5, 1}, {4, 5}, {11, 9}, {9, 4}};
    vector<vector<int>> result1 = sol.validArrangement(pairs1);
    cout << "Test 1: ";
    for (auto &p : result1)
    {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;

    vector<vector<int>> pairs2 = {{1, 3}, {3, 2}, {2, 1}};
    vector<vector<int>> result2 = sol.validArrangement(pairs2);
    cout << "Test 2: ";
    for (auto &p : result2)
    {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }
    cout << endl;

    return 0;
}