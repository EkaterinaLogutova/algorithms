#include <iostream>
#include <vector>

using namespace std;

bool check(const vector<int>& ind, int k, int mid) {
    int j = 0;
    int ans = 1;
    int delta{};
    int i =1;
    while(i < ind.size()) {
        delta = ind[i] - ind[j];
        if (delta > mid) {
            if (i - j == 1) {
                return false;
            } else {
                ans++;
                j = i - 1;
            }
        } else if (delta == mid) {
            ans++;
            j = i;
            i++;
        } else {
            if (i == ind.size()) {
                ans++;
            }
            i++;
        }
    }
    return ans <= k;
}

int bin_search(int n, int k, const vector<int>& ma, const vector<int>& ind) {
    int left = 0;
    int right = n;
    int mid{};
    while (right - left > 1) {
        mid = (right + left) / 2;
        if (check(ind, k, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    if (check(ind, k, left)) {
        return left;
    }
    return right;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> ma(n);
    int i=0;
    while(i<n-1)
    {
        cin>>ma[i];
        i++;
    }

    vector<int> ind;
    ind.push_back(0);
    
    for (int i = 0; i < n - 1; i++) {
        if (ma[i]) {
            ind.push_back(i + 1);
        }
    }
    
    ind.push_back(n);
    
    cout << bin_search(n, k, ma, ind) << endl;

    return 0;
}
