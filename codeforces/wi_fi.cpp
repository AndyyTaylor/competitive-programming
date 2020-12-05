// https://codeforces.com/problemset/problem/1216/F

#include <iostream>
#include <unordered_map>
#include <string>
#include <set>

const long long INF = 2e10;
const int MAX = 2e5+5;
int n, k;

std::set<int> routers;

int main() {
    long long dp[MAX];
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            routers.emplace(i + 1);
        }
    }

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + i;

        auto next = routers.lower_bound(i - k);
        if (next != routers.end() && *next <= i + k) {
            auto a = dp[std::max(0, *next - k - 1)];
            dp[i] = std::min(dp[i], dp[std::max(0, *next - k - 1)] + *next);
        }
    }

    std::cout << dp[n] << '\n';

    return 0;
}
