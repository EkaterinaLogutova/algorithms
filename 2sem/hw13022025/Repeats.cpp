#include <iostream>
#include <vector>

using namespace std;

int find_duplicate(const vector<int>& arr) {
  int n = arr.size();

  // Используем концепцию "медленного" и "быстрого" указателей.
  int slow = arr[0];
  int fast = arr[arr[0]];

  // Поиск пересечения "медленного" и "быстрого" указателей.
  while (slow != fast) {
    slow = arr[slow];
    fast = arr[arr[fast]];
  }

  //Поиск начала цикла (повторяющегося элемента).
  slow = 0;
  while (slow != fast) {
    slow = arr[slow];
    fast = arr[fast];
  }

  return slow;
}

int main() {
  vector<int> arr = {1, 2, 3, 1, 4, 5}; 

  int duplicate = find_duplicate(arr);

  cout << duplicate << endl;

  return 0;
}