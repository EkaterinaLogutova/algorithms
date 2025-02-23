#include <iostream>
#include <vector>
#include <string>

using namespace std;

//возможно ли достичь n не более, чем за k?

bool can_reach(int n, int k, const string& a, int max_jump) {
    vector<int> dp(n + 1, k + 1); // dp[i] - минимальное кол-во прыжков, чтобы достичь i
    dp[0] = 0; //начальное положение
    //dp[i]=k+1 для остальных точек, 
    //чтобы обозначить, что они недостижимы изначально

    for (int i = 0; i < n; ++i) {
        if (dp[i] > k) continue; // Невозможно достичь i за k прыжков

        for (int j = 1; j <= max_jump; ++j) {
            if (i + j <= n) {
                if (i + j == n || (i + j < n && a[i + j - 1] == '1')) { //либо конечная, либо можно приземлиться
                    dp[i + j] = min(dp[i + j], dp[i] + 1);
                }
            }
        }
    }

    return dp[n] <= k;
}


int main(){

    int n, k;
    cin >> n >> k;
    string a;
    cin >> a;

    int left = 1;
    int right = n;
    int ans = n;

    while (left <= right) { //бин поиск для определения минимально возможной max_jump
        int mid = left + (right - left) / 2;
        if (can_reach(n, k, a, mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << ans << endl;

    return 0;
}