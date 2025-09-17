#include <iostream>
#include <queue>
#include <vector>

using namespace std;

long long quick_sum(vector<int>& numbers) {
    priority_queue<int, vector<int>, greater<int>> minHeap(numbers.begin(), numbers.end()); //greater int это 
                                                                //чтобы наименьший элемент извлекался первым
    long long totalTime = 0;

    /*
    пока в куче больше одного элемента, извлекаем два минимальных элемента, 
    складываем их и добавляем сумму обратно в кучу. 
    время, затраченное на сложение, добавляем к общему времени.
    */
    while (minHeap.size() > 1) {
        int first = minHeap.top();
        minHeap.pop();
        int second = minHeap.top();
        minHeap.pop();
        int sum = first + second;
        totalTime += sum;
        minHeap.push(sum);
    }

    return totalTime;
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << quick_sum(numbers) << endl;
    return 0;
}