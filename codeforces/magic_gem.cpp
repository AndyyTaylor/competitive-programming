// https://codeforces.com/problemset/problem/1117/D

#include <iostream>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const ll N = 1e18;
const int M = 105;

// Implementation for square matrices.
struct Matrix {
  const static int N = 105;
  int n;
  long long v[N][N];

  Matrix(int _n) : n(_n) {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) v[i][j] = 0;
  }

  Matrix operator*(const Matrix &o) const {
    Matrix res(n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        for (int k = 0; k < n; k++)
          res.v[i][j] = (res.v[i][j] + v[i][k] * o.v[k][j]) % MOD;
    return res;
  }

  static Matrix getIdentity(int n) {
    Matrix res(n);
    for (int i = 0; i < n; i++) res.v[i][i] = 1;
    return res;
  }

  Matrix operator^(long long k) const {
    Matrix res = Matrix::getIdentity(n);
    Matrix a = *this;
    while (k) {
      if (k&1) res = res*a;
      a = a*a;
      k /= 2;
    }
    return res;
  }
};

int dp[M];

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    ll n, m;
    std::cin >> n >> m;

    Matrix rec(m);

    rec.v[0][0] = 1;
    rec.v[0][m-1] = 1;
    for (int i = 1; i < m; i++) {
        rec.v[i][i-1] = 1;
    }

    rec = rec ^ n;

    // for (int i = 0; i < m; i++) {
    //     dp[i] = 1;
    // }

    // for (int i = m; i <= n; i++) {
    //     dp[i % m] = dp[(i - m) % m] + dp[(i - 1) % m];
    // }

    // for (int i = 0; i <= n; i++) {
    //     std::cout << dp[i] << " ";
    // }

    // for (int i = 0; i < m; i++) {
    //     std::cout << rec.v[0][i] << " ";
    // }

    std::cout << (rec.v[0][0] % MOD + MOD) % MOD << "\n";
    return 0;
}
