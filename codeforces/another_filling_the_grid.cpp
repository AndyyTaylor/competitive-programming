// https://codeforces.com/problemset/problem/1228/E

#include <iostream>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 305;

int n, k;

ll dp[N][N];
ll f[N];

ll choose[N][N];

ll pow(ll x, ll n) {
    if (n == 0) {
        return 1;
    }

    ll a = pow(x, n / 2);
    a = a * a % MOD;

    if (n % 2 == 1) {
        a = a * x % MOD;
    }

    return a;
}

ll inv(ll x) {
    // By Fermat ’s little theorem , a^(p -2) is the inverse of a mod p
    return pow(x, MOD - 2);
}

ll calcChoose(ll n, ll k) {
    ll res = (f[n] * inv(f[n-k])) % MOD;
    res = (res * inv(f[k])) % MOD;

    return res;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    f[0] = 1;
    for (int i = 1; i < N; i++) f[i] = (i * f[i - 1]) % MOD;

    std::cin >> n >> k;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            choose[i][j] = calcChoose(i, j);
        }
    }

    ll kpow[N];
    ll km1pow[N];
    for (int i = 0; i < N; i++) {
        kpow[i] = pow(k, i);
        km1pow[i] = pow(k - 1, i);
    }

    for (int i = 1; i <= n; i++) {
        dp[i][0] = pow(kpow[n] - km1pow[n], i);
    }

    for (int i = 1; i <= n; i++) {
        dp[1][i] = kpow[n - i];
    }

    for (int r = 2; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            dp[r][c] = (kpow[n - c] - km1pow[n - c]) * km1pow[c] % MOD * dp[r - 1][c] % MOD;

            for (int c0 = 1; c0 <= c; c0++) {
                dp[r][c] += km1pow[c - c0] * kpow[n - c] % MOD * choose[c][c0] % MOD * dp[r - 1][c - c0] % MOD;
                dp[r][c] %= MOD;
            }
        }
    }

    std::cout << (dp[n][n] % MOD + MOD) % MOD;

    return 0;
}
