// https://codeforces.com/problemset/problem/553/A

#include <iostream>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 1005;

int k;
int count[N];
int prefix_sum[N];

int dp[N];
ll f[N];

ll modpow(ll x, ll n) {
    if (n == 0) {
        return 1;
    }

    ll a = modpow(x, n / 2);
    a = a * a % MOD;

    if (n % 2 == 1) {
        a = a * x % MOD;
    }

    return a;
}

ll inv(ll x) {
    // By Fermat ’s little theorem , a^(p -2) is the inverse of a mod p
    return modpow(x, MOD - 2);
}

ll choose(ll n, ll k) {
    ll res = (f[n] * inv(f[n-k])) % MOD;
    res = (res * inv(f[k])) % MOD;

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    f [0] = 1;
    for (int i = 1; i < N; i++) f[i] = (i * f[i - 1]) % MOD;

    std::cin >> k;

    prefix_sum[0] = 0;
    for (int i = 1; i <= k; i++) {
        std::cin >> count[i];
        prefix_sum[i] = prefix_sum[i - 1] + count[i];
    }

    dp[1] = 1;
    for (int i = 2; i <= k; i++) {
        dp[i] = (choose(prefix_sum[i] - 1, count[i] - 1) * dp[i - 1]) % MOD;
    }

    std::cout << (dp[k] % MOD + MOD) % MOD;

    return 0;
}
