// https://codeforces.com/gym/101981/attachments

#include <iostream>
#include <queue>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 510 + 510 + 5;
const int E = 1e6;

int n, m, k;
int s, t;

int start[N];
int succ[E], cap[E], to[E];

int edge_counter = 0;
void add_edge_sub(int u, int v, int c) {
    // std::cout << "adding edge " << edge_counter << " from " << u << " to " << v << " with cap " << c << std::endl;
    cap[edge_counter] = c;
    to[edge_counter] = v;

    succ[edge_counter] = start[u];
    start[u] = edge_counter;
    ++edge_counter;
}

void add_edge(int u, int v, int  c) {
    add_edge_sub(u, v, c);
    add_edge_sub(v, u, 0);
}

int inv(int e) {
    return e ^ 1;
}

int lvl[N];
int nextchld[N];

bool bfs() {
    for (int i = 0; i < n; i++) {
        lvl[i] = -1;
    }

    std::queue<int> q;
    q.push(s);
    lvl[s] = 0;

    int c;
    while (!q.empty()) {
        int u = q.front();
        // std::cout << u << std::endl;
        q.pop();

        nextchld[u] = start[u];  // reset nextchld
        for (int e = start[u]; ~e; e = succ[e]) {
            if (cap[e] <= 0) {
                continue;
            }

            int nxt = to[e];
            if (lvl[nxt] != -1) {
                continue;  // already seen / added to list
            }

            lvl[nxt] = lvl[u] + 1;
            q.push(nxt);
        }
    }

    // std::cout << lvl[t] << std::endl;

    return lvl[t] != -1;  // since is still reachable?
}

int aug(int u, int cflow) {
    // std::cout << "aug " << u << std::endl;
    if (u == t) {
        return cflow;
    }

    for (int& i = nextchld[u]; i >= 0; i = succ[i]) {
        // std::cout << cap[i] << std::endl;
        if (cap[i] > 0) {
            int nxt = to[i];

            if (lvl[nxt] != lvl[u] + 1) continue;

            int rf = aug(nxt, std::min(cflow, cap[i]));

            if (rf > 0) {
                cap[i] -= rf;
                cap[inv(i)] += rf;

                return rf;
            }
        }
    }

    lvl[u] = -1;
    return 0;
}

int get_max_flow() {
    int total = 0;
    while (bfs()) {
        for (int x = aug(s, INF); x; x = aug(s, INF)) {
            total += x;
        }
    }

    return total;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> m >> k;

    std::fill(start, start + n + m + 1 + 2, -1);

    // 0 - source
    // 1 - sink
    // 2 - potion constraint

    add_edge(0, 2, k);
    for (int i = 1; i <= n; i++) {
        add_edge(0, 2 + i, 1);
        add_edge(2, 2 + i, 1);
    }

    for (int i = 1; i <= m; i++) {
        add_edge(2 + n + i, 1, 1);
    }

    for (int i = 1; i <= n; i++) {
        int t;
        std::cin >> t;

        for (int ti = 0; ti < t; ti++) {
            int m;
            std::cin >> m;

            add_edge(2 + i, 2 + n + m, 1);
        }
    }

    s = 0;
    t = 1;

    n = n + m + 1 + 2;
    std::cout << get_max_flow() << "\n";

    return 0;
}
