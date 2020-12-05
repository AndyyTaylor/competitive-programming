// https://codeforces.com/problemset/problem/416/E

#include <vector>
#include <iostream>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int MAXN = 505;

struct edge {
    int u, v;
    ll w;
    edge(int _u, int _v, ll _w) : u(_u), v(_v), w(_w) {}
};

int M, N;

std::vector<edge> edges;
ll dist[MAXN][MAXN];

void floyd() {
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            dist[u][v] = INF;
        }
    }

    for (auto& e : edges) {
        dist[e.u][e.v] = e.w;
    }

    for (int u = 0; u < N; u++) {
        dist[u][u] = 0;
    }

    for (int i = 0; i < N; i++) {
        for (int u = 0; u < N; u++) {
            for (int v = 0; v < N; v++) {
                dist[u][v] = std::min(dist[u][v], dist[u][i] + dist[i][v]);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int x, y;
        ll l;
        std::cin >> x >> y >> l;

        x--;
        y--;

        edges.push_back({x, y, l});
        edges.push_back({y, x, l});
    }

    floyd();

    int dp[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = 0;
        }
    }

    for (auto& e : edges) {
        for (int i = 0; i < N; i++) {
            // edge is a part of one of the shortest paths from e.u -> e.v
            if (dist[i][e.v] == dist[i][e.u] + e.w) {
                dp[i][e.v]++;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            int ans = 0;
            for (int p = 0; p < N; p++) {
                if (dist[i][p] + dist[p][j] == dist[i][j]) {
                    ans += dp[i][p];
                }
            }

            std::cout << ans << " ";
        }
    }

    return 0;
}
