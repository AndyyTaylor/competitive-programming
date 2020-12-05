// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=870


#include <iostream>
#include <queue>
#include <vector>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

int N, M;

typedef std::pair<int, int> pii;
std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

std::vector<pii> adj[1005 * 1005];

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
        std::cin >> N >> M;
        for (int i = 0; i < N * M; i++) adj[i].clear();
        while (!pq.empty()) pq.pop();

        int grid[N][M];
        for (int n = 0; n < N; n++) {
            for (int m = 0; m < M; m++) {
                std::cin >> grid[n][m];
            }
        }

        for (int n = 0; n < N; n++) {
            for (int m = 0; m < M; m++) {
                if (n > 0) {
                    adj[n*M + m].push_back({grid[n - 1][m], (n - 1) * M + m});
                }
                if (m > 0) {
                    adj[n*M + m].push_back({grid[n][m - 1], n * M + m - 1});
                }
                if (n < N - 1) {
                    adj[n*M + m].push_back({grid[n+1][m], (n + 1) * M + m});
                }
                if (m < M - 1) {
                    adj[n*M + m].push_back({grid[n][m+1], n*M + m + 1});
                }
            }
        }

        bool seen[N * M];
        for (int i = 0; i < N * M; i++) seen[i] = false;
        int dist[N * M];
        pq.push({grid[0][0], 0});
        while (!pq.empty()) {
            pii cur = pq.top();
            pq.pop();

            int v = cur.second, d = cur.first;
            if (seen[v]) {
                continue;
            }

            dist[v] = d;
            seen[v] = true;

            for (auto& next : adj[v]) {
                int u = next.second, weight = next.first;

                if (!seen[u]) {
                    pq.push({d + weight, u});
                }
            }
        }

        std::cout << dist[N * M - 1] << "\n";
    }
    
    return 0;
}
