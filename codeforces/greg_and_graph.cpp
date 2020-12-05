// https://codeforces.com/problemset/problem/295/B

#include <iostream>
#include <vector>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int MAXN = 505;

ll dist[MAXN][MAXN];
int N;

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> N;

    for (int u = 1; u <= N; u++) {
        for (int v = 1; v <= N; v++) {
            std::cin >> dist[u][v];
        }
    }

    int x[N];
    for (int i = 0; i < N; i++) {
        std::cin >> x[N - i - 1];
    }

    std::vector<ll> distances;
    for (int ii = 0; ii < N; ii++) {
        // std::cout << "adding " << x[ii] << "\n";
        for (int ui = 0; ui < N; ui++) {
            for (int vi = 0; vi < N; vi++) {
                int u = x[ui];
                int v = x[vi];
                int i = x[ii];

                dist[u][v] = std::min(dist[u][v], dist[u][i] + dist[i][v]);
            }
        }

        ll totalDist = 0;
        for (int ui = 0; ui <= ii; ui++) {
            for (int vi = 0; vi <= ii; vi++) {
                int u = x[ui];
                int v = x[vi];

                totalDist += dist[u][v];

                // std::cout << "dist from " << u << " to " << v << " = " << dist[u][v] << "\n";
            }
        }

        // std::cout << totalDist << "\n";
        distances.push_back(totalDist);
    }

    for (auto it = distances.rbegin(); it != distances.rend(); it++) {
        std::cout << *it << " ";
    }

    return 0;
}
