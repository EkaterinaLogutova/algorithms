#include <iostream>
#include <vector>

using namespace std;

int find_min_index(const vector<int>& a, int b_i) {
  int left = 0;
  int right = 1;

  // Расширяем область поиска до тех пор, пока a[right] не станет >= b_i, или пока не достигнем конца массива
  while (right < a.size() && a[right] < b_i) {
    left = right;
    right *= 2;
  }

  // Бинарный поиск в найденном диапазоне [left, min(right, a.size() - 1)]
  right = min((int)right, (int)a.size() - 1); // Предотвращаем выход за границы массива

  int result = a.size(); // Значение по умолчанию, если не найдено

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (a[mid] >= b_i) {
      result = mid;
      right = mid - 1; // Ищем минимальный индекс
    } else {
      left = mid + 1;
    }
  }
  return result;
}

int main() {
  vector<int> a = {2,4,5,7};
  vector<int> b = {4,6,1};

  for (int b_i : b) {
    int index = find_min_index(a, b_i);
    cout << index << endl;
  }

  return 0;
}

