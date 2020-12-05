// https://www.codechef.com/problems/SETDIFF

#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    int T;
    std::cin >> T;

    std::vector<int> nums;

    for (int tt = 0; tt < T; tt++) {
        int N;
        std::cin >> N;

        nums.clear();
        for (int i = 0; i < N; i++) {
            int n;
            std::cin >> n;

            nums.push_back(n);
        }

        std::sort(nums.begin(), nums.end());

        ll sum_min = 0;
        ll sum_max = 0;
        for (int i = 0; i < N; i++) {
            sum_min = (2 * sum_min + nums[i]) % MOD;
        }

        std::sort(nums.rbegin(), nums.rend());

        for (int i = 0; i < N; i++) {
            sum_max = (2 * sum_max + nums[i]) % MOD;
        }

        std::cout << (sum_max + MOD - sum_min) % MOD << "\n";
    }

    return 0;
}
