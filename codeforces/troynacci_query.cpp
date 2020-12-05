// https://codeforces.com/gym/100571/problem/B


#include <iostream>
#include <unordered_map>

const int MAX = 1e5+5;
const long long MOD = 1e9+7;
long long x[MAX];
long long diff[MAX];
long long F[MAX];
long long p[MAX * 2];

long long N, Q, F1, F2, A, B;

// calc f using dynamic programming & cache results
std::unordered_map<int, long long> dp;
long long f(int i) {
    if (i == 1) {
        return F1;
    } else if (i == 2) {
        return F2;
    }

    if (dp.find(i) != dp.end()) {
        return dp[i];
    }

    return dp[i] = ((A * f(i - 2) + B * f(i - 1)) % MOD + MOD) % MOD;
}

int main() {
    std::cin >> N >> Q;
    std::cin >> F1 >> F2;
    std::cin >> A >> B;

    for (int i = 1; i <= N; i++) {
        std::cin >> x[i];
    }

    for (int q = 0; q < Q; q++) {
        int l, r;
        std::cin >> l >> r;

        // works kinda like prefix sums
        diff[l] = ((diff[l] + f(1)) % MOD + MOD) % MOD;
        diff[l + 1] = ((diff[l + 1] + f(2) - B * f(1)) % MOD + MOD) % MOD;
        diff[r + 1] = ((diff[r + 1] - f(r - l + 2)) % MOD + MOD) % MOD;
        diff[r + 2] = ((diff[r + 2] - A * f(r - l + 1)) % MOD + MOD) % MOD;
    }

    for (int i = 1; i <= N; i++) {
        if (i >= 2) {
            diff[i] = (((A * diff[i - 2]) + (B * diff[i - 1]) + diff[i]) % MOD + MOD) % MOD;
        }
        std::cout << ((x[i] + diff[i]) % MOD + MOD) % MOD << " ";
    }
}
