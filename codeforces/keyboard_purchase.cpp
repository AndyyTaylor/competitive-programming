// https://codeforces.com/problemset/problem/1238/E

#include <iostream>
#include <cstring>

#define ll long long

// const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 20;
const int INF = (1<<N) - 1;
int n, m;

int dp[INF+10];

void printBits(int val) {
    for (int j = m-1; j >= 0; j--) {
        if (val & (1<<j)) {
            std::cout << "1";
        } else {
            std::cout << "0";
        }
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> m;

    std::string s;
    std::cin >> s;

    int pairs[m][m];
    memset(pairs, 0, sizeof(pairs));

    for (int i = 1; i < n; i++) {
        pairs[s[i] - 'a'][s[i - 1] - 'a']++;
        pairs[s[i - 1] - 'a'][s[i] - 'a']++;
    }

    int inf = (1<<m) - 1;

    for (int i = 0; i < INF+10; i++) dp[i] = 1e9;

    dp[0] = 0;
    for (int msk = 1; msk <= inf; msk++) {
        // printBits(msk);

        int cost = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (i == j) continue;

                if ((msk & (1<<i)) && !(msk & (1<<j))) {
                    cost += pairs[i][j];
                    // std::cout << "adding pairs " << i << " " << j << '\n';
                }
            }
        }


        // std::cout << cost << '\n';

        for (int j = 0; j < m; j++) {
            if (msk & (1<<j)) {
                dp[msk] = std::min(dp[msk], dp[msk^(1<<j)] + cost);
            }
        }

        // std::cout << dp[msk] << '\n';
    }

    std::cout << dp[inf] << '\n';

    return 0;
}
