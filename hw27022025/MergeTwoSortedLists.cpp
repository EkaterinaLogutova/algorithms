#include <iostream>
#include <vector>

using namespace std;

vector<int> merge(const vector<int>& vec1, const vector<int>& vec2) {
    vector<int> result;
    size_t i = 0, j = 0;

    //проходим два вектора до конца
    while (i < vec1.size() && j < vec2.size()) {
        if (vec1[i] < vec2[j]) {
            result.push_back(vec1[i]);
            i++;
        } else {
            result.push_back(vec2[j]);
            j++;
        }
    }
    //если один из векторов закончился, добавляем оставшиеся элементы другого
    while (i < vec1.size()) {
        result.push_back(vec1[i]);
        i++;
    }
    while (j < vec2.size()) {
        result.push_back(vec2[j]);
        j++;
    }

    return result;
}

int main() {
    vector<int> vec1 = {1, 2, 4};
    vector<int> vec2 = {1, 3, 4};
    vector<int> mergedVec = merge(vec1, vec2);
    for (int num : mergedVec) {
        cout << num << " ";
    }
    cout << endl; //1 1 2 3 4 4
    vector<int> vec3 = {};
    vector<int> vec4 = {};
    vector<int> mergedVec2 = merge(vec3, vec4);
    for (int num : mergedVec2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}