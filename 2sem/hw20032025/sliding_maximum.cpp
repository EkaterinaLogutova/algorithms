#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> slidingMax(const vector<int>& nums, int k) {
    vector<int> result;
    priority_queue<pair<int, int>> pq; //пары (значение, индекс)
    //на вершине наибольший элемент

    for (int i = 0; i < nums.size(); ++i) {
        //удаляем элементы, которые вышли за пределы окна
        while (!pq.empty() && pq.top().second <= i - k) {
            pq.pop();
        }

        //текущий элемент в кучу
        pq.push({nums[i], i});

        //если окно сформировано, то добавляем максимум в результат
        if (i >= k - 1) {
            result.push_back(pq.top().first);
        }
    }

    return result;
}

int main() {
    int n, k;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    cin >> k;

    vector<int> result = slidingMax(nums, k);

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}