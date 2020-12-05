// https://codeforces.com/problemset/problem/449/B

#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int MAXN = 2e5+10;

int N, M, K;

typedef std::tuple<ll, int, bool> pii;
std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

std::vector<pii> adj[MAXN];

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> N >> M >> K;
    for (int i = 1; i <= M; i++) {
        int u, v, x;
        std::cin >> u >> v >> x;

        adj[u].push_back({x, v, false});
        adj[v].push_back({x, u, false});
    }

    ll dist[N+10];
    // bool usingTrain[N+10];
    // int trainCount[N+10];
    for (int i = 1; i <= N; i++) {
        dist[i] = LINF;
        // trainCount[i] = 0;
        // usingTrain[i] = false;
    }

    for (int i = 1; i <= K; i++) {
        ll s, y;
        std::cin >> s >> y;

        adj[1].push_back({y, s, true});
        // trainCount[s]++;
        // usingTrain[s] = true;
        // dist[s] = std::min(dist[s], y);
    }

    bool seen[N+10];
    for (int i = 1; i <= N; i++) seen[i] = false;

    int trainCount = 0;
    pq.push({0, 1, false});
    while (!pq.empty()) {
        pii cur = pq.top();
        pq.pop();

        ll v = std::get<1>(cur), d = std::get<0>(cur);
        bool isTrain = std::get<2>(cur);
        if (seen[v]) {
            continue;
        }

        // std::cout << v << ": " << dist[v] << " vs " << d << "\n";
        dist[v] = d;

        if (isTrain) {
            trainCount++;
        }

        seen[v] = true;

        for (auto& next : adj[v]) {
            ll u = std::get<1>(next), weight = std::get<0>(next);
            bool isTrain = std::get<2>(next);

            if (!seen[u]) {
                pq.push({d + weight, u, isTrain});
            }
        }
    }

    std::cout << K - trainCount << "\n";

    return 0;
}
