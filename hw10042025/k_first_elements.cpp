#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> get_top_k_numbers(int total_numbers, int k, istream& input_stream) {
    priority_queue<int> largest_k;
    
    int current_number;
    for (int i = 0; i < total_numbers; ++i) {
        input_stream >> current_number;
        
        if (largest_k.size() < k) {
            largest_k.push(current_number);
        }
        else if (current_number < largest_k.top()) {
            largest_k.pop();
            largest_k.push(current_number);
        }
    }
    
    vector<int> sorted_result;
    while (!largest_k.empty()) {
        sorted_result.push_back(largest_k.top());
        largest_k.pop();
    }
    
    reverse(sorted_result.begin(), sorted_result.end());
    return sorted_result;
}

int main() {
    int total_elements, needed_elements;
    cin >> total_elements >> needed_elements;
    
    vector<int> smallest_elements = get_top_k_numbers(total_elements, needed_elements, cin);
    
    for (int elem : smallest_elements) {
        cout << elem << " ";
    }
    cout << endl;
    
    return 0;
}