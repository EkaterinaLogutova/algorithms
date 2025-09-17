#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int min_dead_ends(vector<pair<int, int>>& schedule) { //в векторе пары прибытие-отправление
    //для хранения времени освобождения тупиков
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for (const auto& train : schedule) {
        int arrival = train.first;
        int departure = train.second;

        //если есть тупик, который освободился до прибытия текущей электрички, используем его
        if (!minHeap.empty() && minHeap.top() < arrival) {
            minHeap.pop();
        }

        minHeap.push(departure); //добавляем время отправвления текущей электрички
    }

    return minHeap.size();
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> schedule(n);

    for (int i = 0; i < n; ++i) {
        cin >> schedule[i].first >> schedule[i].second;
    }

    cout << min_dead_ends(schedule) << endl;
    return 0;
}