// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1271

#include <iostream>
#include <queue>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 110*2;
const int E = 1e6;

int n, m, b, d;
int s, t;

int start[N];
int succ[E], cap[E], to[E];

int edge_counter = 0;
void add_edge(int u, int v, int c) {
    cap[edge_counter] = c;
    to[edge_counter] = v;

    succ[edge_counter] = start[u];
    start[u] = edge_counter;
    ++edge_counter;
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

    while (std::cin >> n) {
        n *= 2;

        std::fill(start, start + n + 2, -1);
        for (int i = 2; i <= n; i += 2) {
            int c;
            std::cin >> c;

            add_edge(i, i + 1, c);
            add_edge(i + 1, i, 0);
        }

        std::cin >> m;
        for (int i = 0; i < m; i++) {
            int u, v, c;
            std::cin >> u >> v >> c;

            u *= 2; u++;
            v *= 2;

            add_edge(u, v, c);
            add_edge(v, u, 0);
        }

        std::cin >> b >> d;
        for (int i = 0; i < b; i++) {
            int u;
            std::cin >> u;

            u *= 2;

            add_edge(0, u, INF);
            add_edge(u, 0, 0);
        }

        // std::cout << b;

        for (int i = 0; i < d; i++) {
            int u;
            std::cin >> u;

            u *= 2;
            u++;

            add_edge(u, 1, INF);
            add_edge(1, u, 0);
        }

        n += 2;


        s = 0;
        t = 1;
        // todo next test case

        // std::cout << "test" << std::endl;

        std::cout << get_max_flow() << "\n";
    }

    return 0;
}
