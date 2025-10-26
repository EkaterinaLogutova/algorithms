#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int countPaths(int n, int start, int end, vector<vector<int>> &g)
{
    vector<int> dist(n, -1); // расстояния от start
    vector<int> cnt(n, 0);   // количество кратчайших путей
    queue<int> q;

    dist[start] = 0;
    cnt[start] = 1;
    q.push(start);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (int u : g[v])
        {
            // первое посещение - кратчайший путь
            if (dist[u] == -1)
            {
                dist[u] = dist[v] + 1;
                cnt[u] = cnt[v]; // пути через v
                q.push(u);
            }
            // еще один кратчайший путь той же длины
            else if (dist[u] == dist[v] + 1)
            {
                cnt[u] += cnt[v]; // добавляем пути через v
            }
        }
    }

    return cnt[end];
}

int main()
{
    vector<vector<int>> g = {
        {1, 2},
        {0, 2, 3},
        {0, 1, 4},
        {1, 4},
        {2, 3}};

    cout << countPaths(5, 0, 4, g) << endl;
    return 0;
}