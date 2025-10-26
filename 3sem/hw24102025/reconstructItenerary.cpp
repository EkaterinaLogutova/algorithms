#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<string> findItinerary(vector<vector<string>> &tickets)
    {
        // строим граф рейсов
        for (auto &ticket : tickets)
        {
            graph[ticket[0]].push_back(ticket[1]);
        }

        // сортируем аэропорты назначения по алфавиту
        for (auto &[from, toList] : graph)
        {
            sort(toList.begin(), toList.end());
        }

        // ищем маршрут с помощью dfs
        vector<string> itinerary;
        dfs("JFK", itinerary);
        reverse(itinerary.begin(), itinerary.end());
        return itinerary;
    }

private:
    unordered_map<string, vector<string>> graph;

    void dfs(string airport, vector<string> &itinerary)
    {
        auto &destinations = graph[airport];
        // посещаем все доступные аэропорты
        while (!destinations.empty())
        {
            string next = destinations.front();
            destinations.erase(destinations.begin());
            dfs(next, itinerary);
        }
        // добавляем аэропорт в маршрут когда все его рейсы обработаны
        itinerary.push_back(airport);
    }
};

int main()
{
    Solution sol;

    vector<vector<string>> tickets1 = {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
    vector<string> result1 = sol.findItinerary(tickets1);

    cout << "Test 1: ";
    for (const string &s : result1)
    {
        cout << s << " ";
    }
    cout << endl;

    vector<vector<string>> tickets2 = {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}};
    vector<string> result2 = sol.findItinerary(tickets2);

    cout << "Test 2: ";
    for (const string &s : result2)
    {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}