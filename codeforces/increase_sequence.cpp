// https://codeforces.com/contest/466/problem/D

#include <iostream>

const int MAX = 2005;

int n, h;
int a[MAX];
int dp[MAX][MAX];

int main() {
    int n, h;
    std::cin >> n >> h;

    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    // either not open an interval || create a [1, 1] intervaln
    if (a[1] == h || a[1] + 1 == h) {
        dp[1][0] = 1;
    } else {
        dp[1][0] = 0;
    }

    // start an interval from [1, ...]
    if (a[1] + 1 == h) {
        dp[1][1] = 1;
    } else {
        dp[1][1] = 0;
    }

    for (int i = 2; i <= n; ++i) {
        for (int open = 0; open <= i; open++) {
            if (a[i] + open == h) {
                // keep existing segments open
                dp[i][open] += dp[i - 1][open];

                if (open > 0) {
                    // open a new segment
                    dp[i][open] += dp[i - 1][open - 1];
                }
            } else if (a[i] + open + 1 == h) {
                // close a segment
                dp[i][open] += dp[i - 1][open + 1] * (open + 1);

                // create a 1 length segment
                dp[i][open] += dp[i - 1][open];

                // close an old segment and open a new one
                dp[i][open] += dp[i - 1][open] * open;
            }
        }
    }

    std::cout << dp[n][0] << '\n';

    return 0;
}
