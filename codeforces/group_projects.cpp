// https://codeforces.com/problemset/problem/626/F

#include <iostream>
#include <algorithm>
#include <cstring>

#define modadd(y, x) (y = (((x % ((long long) 1e9 + 7)) + (y % ((long long) 1e9 + 7))) % ((long long) 1e9 + 7)))

int n, K;
int a[205];

long long dp[2][205][1005] = {0};

int main() {
    std::cin >> n >> K;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::sort(a, a+n);

    // 2 ways to start
    //      a) a[0] in their own group
    //      b) a[0] in an "open" group
    dp[0][0][0] = 1;
    dp[0][1][0] = 1;

    for (int i = 1; i < n; ++i) {
        int diff = a[i] - a[i - 1];

        int cur_ind = i%2;
        int prev_ind = (i-1)%2;
        memset(dp[cur_ind], 0, sizeof(dp[cur_ind]));
        for (int open = 0; open < n; ++open) {
            for (int k = 0; k <= K; ++k) {
                // new total imbalance for all groups
                int new_k = diff * open + k;

                if (new_k > K) {
                    break;
                }

                // add student i to their own group && add student i to an existing group
                modadd(dp[cur_ind][open][new_k], dp[prev_ind][open][k] * (open + 1));
                // create a new "open" group with student i
                modadd(dp[cur_ind][open + 1][new_k], dp[prev_ind][open][k]);

                if (open > 0) {
                    // de
                    // modadd(dp[cur_ind][open][new_k], dp[prev_ind][open][k] * open);
                    // add student i to an existing group, and "close" that group
                    modadd(dp[cur_ind][open - 1][new_k], dp[prev_ind][open][k] * open);
                }
            }
        }
    }

    long long total = 0;
    for (int k = 0; k <= K; ++k) {
        modadd(total, dp[(n-1)%2][0][k]);
    }

    std::cout << total << '\n';

    return 0;
}
