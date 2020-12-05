// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1498

#include <vector>
#include <iostream>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

struct edge {
    int u, v, w;
    edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

int N;
int room_energy[105];

int fDist[105][105];

std::vector<edge> edges;
std::vector<int> dist(105);
std::vector<int> cycleNodes;

bool relax() {
    cycleNodes.clear();
    bool relaxed = false;
    for (auto& e : edges) {
        if (dist[e.u] + e.w > 0 && dist[e.v] < dist[e.u] + e.w) {
            // std::cout << "relax " << e.u << "-" << e.v << " " << e.w << '\n';
            relaxed = true;
            dist[e.v] = dist[e.u] + e.w;
            cycleNodes.push_back(e.v);
            cycleNodes.push_back(e.u);
        }
    }

    return relaxed;
}

bool find_and_check() {
    fill(dist.begin(), dist.end(), -INF);
    dist[0] = 100;

    for (int i = 0; i < N; i++) relax();

    return relax();
}

void floydWarshal() {
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            fDist[u][v] = INF;
        }
    }

    for (auto& e : edges) {
        fDist[e.u][e.v] = 1;
    }

    for (int u = 0; u < N; u++) {
        fDist[u][u] = 0;
    }

    for (int i = 0; i < N; i++) {
        for (int u = 0; u < N; u++) {
            for (int v = 0; v < N; v++) {
                fDist[u][v] = std::min(fDist[u][v], fDist[u][i] + fDist[i][v]);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    while (1) {
        std::cin >> N;
        if (N == -1) break;

        cycleNodes.clear();
        edges.clear();

        for (int i = 0; i < N; i++) {
            std::cin >> room_energy[i];

            int num_edges;
            std::cin >> num_edges;

            for (int e = 0; e < num_edges; e++) {
                int v;
                std::cin >> v;
                v--;

                edges.push_back(edge(i, v, -1));
            }
        }

        for (auto& e : edges) {
            e.w = room_energy[e.v];
        }

        int has_cycle = find_and_check();
        // std::cout << has_cycle << ", " << dist[N - 1] << "\n";
        if (!has_cycle && dist[N - 1] > 0) {
            std::cout << "winnable\n";
            continue;
        }

        floydWarshal();

        // if we can reach neg cycle, & there's a path from the neg cycle to the finish
        // the dist from the neg cycle to the finish is irrelevant
        bool winnable = false;
        for (auto& c : cycleNodes) {
            if (fDist[c][N-1] < INF) {
                winnable = true;
                break;
            }
        }

        if (winnable) {
            std::cout << "winnable\n";
        } else {
            std::cout << "hopeless\n";
        }
    }

    return 0;
}
