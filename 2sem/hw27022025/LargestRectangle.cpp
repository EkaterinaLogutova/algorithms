//Эта задача была разобрана на семинаре, но освежим принцип решения:
//будем использовать стек, храним столбцы в порядке возрастания
//Когда мы находим столбец, который меньше текущего, 
//мы вычисляем площадь прямоугольника, который можно образовать с вершиной стека. 
//Мы продолжаем это делать, пока не найдем столбец, который меньше текущего или пока стек не опустеет.
//обновляем максимальную площадь, если найденная площадь больше текущего максимума

//сложность O(n), так как каждый столбец добавляется и удаляется из стека только один раз.
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int largestRectangleArea(vector<int>& heights) {
    stack<int> s;
    int maxArea = 0;
    int n = heights.size();
    
    for (int i = 0; i <= n; ++i) {
        //пока стек не пуст и текущий столбец меньше столбца на вершине стека
        //или мы дошли до конца массива
        while (!s.empty() && (i == n || heights[s.top()] > heights[i])) {
            int height = heights[s.top()]; //высота столбца на вершине стека
            s.pop(); //удаляем индекс столбца из стека, так как мы уже обработали его
            //если стек пуст, то ширина равна i,
            //иначе ширина равна разнице между текущим индексом и индексом на вершине стека - 1 
            int width = s.empty() ? i : i - s.top() - 1;
            maxArea = max(maxArea, height * width);
        }
        s.push(i);
    }
    
    return maxArea;
}

int main() {
    vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    cout << "Output: " << largestRectangleArea(heights1) << endl;

    vector<int> heights2 = {2, 4};
    cout << "Output: " << largestRectangleArea(heights2) << endl;
    cout << endl;

    return 0;
}