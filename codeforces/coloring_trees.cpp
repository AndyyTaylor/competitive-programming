// https://codeforces.com/problemset/problem/711/C

#include <iostream>
#include <unordered_map>

const int MAX = 115;
const long long INF = 500 * 1e10;

int c[MAX];
long long p[MAX][MAX];

int N, M, K;

// base case
// f(0, k, prevColor) = 0
// f(0, !k, prevColor) = INF

// if k > K: return INF
// if c == 0
//      if k == K: return 0
//      else: return INF

// recurrence relation
// f(c, k, prevColor)
// if tree is colored
//      if color != prevColor: return f(c - 1, k + 1, color)
//      else: return f(c - 1, k, color)
// else
//      return min(
//          f(c - 1, k + (1 if color != prevColor), color) + p[c][color],
//      )

long long dp[MAX][MAX][MAX];
long long paint(int ci, int k, int prevColor) {
    if (ci < 0) {
        if (k == K) {
            return 0;
        } else {
            return INF;
        }
    }

    if (prevColor != -1 && dp[ci][k][prevColor] != -1) {
        return dp[ci][k][prevColor];
    }

    long long val;
    if (c[ci] != 0) {
        if (c[ci] != prevColor) {
            val = paint(ci - 1, k + 1, c[ci]);
        } else {
            val = paint(ci - 1, k, c[ci]);
        }
    } else {
        long long min = INF;
        for (int i = 1; i <= M; i++) {
            int kadj = 0;
            if (i != prevColor) {
                kadj = 1;
            }

            min = std::min(min, paint(ci - 1, k + kadj, i) + p[ci][i]);
        }

        val = min;
    }

    dp[ci][k][prevColor] = val;
    return val;
}

int main() {
    std::cin >> N >> M >> K;

    for (int i = 0; i < N; i++) {
        std::cin >> c[i];
    }

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            for (int q = 0; q < MAX; q++) {
                dp[i][j][q] = -1;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> p[i][j+1];
        }
    }

    long long litres = paint(N - 1, 0, -1);
    if (litres == INF) {
        litres = -1;
    }

    std::cout << litres << '\n';
}
