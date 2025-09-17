#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int64_t merge_and_count(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    int64_t inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++]; //инверсий нет
        } else {
            temp[k++] = arr[j++]; //добавляем инверсии
            inv_count += (mid - i + 1); //dсе элементы от i до mid 
                                    //образуют инверсии с arr[j]
        }
    }
    //оставшиеся
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }
    //копируем в исходный массив
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

int64_t merge_sort_and_count(vector<int>& arr, vector<int>& temp, int left, int right) {
    int64_t inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inv_count += merge_sort_and_count(arr, temp, left, mid); //left
        inv_count += merge_sort_and_count(arr, temp, mid + 1, right); //right
        inv_count += merge_and_count(arr, temp, left, mid, right); //merge
    }
    return inv_count;
}

int64_t count_inversions(vector<int>& arr) {
    vector<int> temp(arr.size());
    return merge_sort_and_count(arr, temp, 0, arr.size() - 1);
}

int main() {
    vector<int> numbers;
    int num;
    
    while (cin >> num) {
        numbers.push_back(num);
    }

    int64_t inversions = count_inversions(numbers);
    cout << inversions << endl;

    return 0;
}