
#include <iostream>
#include <vector>

//O(1) по памяти, O(n) по времени (все элементы перебираем строго один раз)
//записываем уникальные элементы в начало

using namespace std;

vector<int> remove_duplicate(vector<int> head) {
    if (head.empty()) return head;

    int write_index = 0; //индекс для записи уникальных элементов
    int n = head.size();
    int i = 0;

    while (i < n) {
        if (i < n - 1 && head[i] == head[i + 1]) {
            //пропускаем все дубликаты
            int current = head[i];
            while (i < n && head[i] == current) {
                i++;
            }
        } else {
            //записываем уникальный элемент
            head[write_index] = head[i];
            write_index++;
            i++;
        }
    }
    //обрезаем массив до write_index
    head.resize(write_index);
    return head;
}

int main() {
    vector<int> head = {1,1,1,2,3};
    vector<int> new_head = remove_duplicate(head);

    for (auto i : new_head)
        cout << i << " ";
    return 0;
}