#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                dfs(isConnected, visited, i);
                provinces++;
            }
        }

        return provinces;
    }

private:
    void dfs(vector<vector<int>> &isConnected, vector<bool> &visited, int city)
    {
        visited[city] = true;
        for (int neighbor = 0; neighbor < isConnected.size(); neighbor++)
        {
            if (isConnected[city][neighbor] == 1 && !visited[neighbor])
            {
                dfs(isConnected, visited, neighbor);
            }
        }
    }
};

int main()
{
    Solution solution;

    vector<vector<int>> test1 = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    cout << "Test 1: " << solution.findCircleNum(test1) << endl;

    vector<vector<int>> test2 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    cout << "Test 2: " << solution.findCircleNum(test2) << endl;

    vector<vector<int>> test3 = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    cout << "Test 3: " << solution.findCircleNum(test3) << endl;

    vector<vector<int>> test4 = {{1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1}, {1, 0, 1, 1}};
    cout << "Test 4: " << solution.findCircleNum(test4) << endl;

    return 0;
}