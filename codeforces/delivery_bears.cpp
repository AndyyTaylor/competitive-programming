// https://codeforces.com/problemset/problem/653/D

#include <iostream>
#include <queue>

#define ll long long

const int INF = 8e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 510;
const int E = 2*510;

int s, t;

int n, m, x;

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
            // std::cout << e << " " << cap[e] << std::endl;
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
        for (int x2 = aug(s, INF); x2; x2 = aug(s, INF)) {
            total += x2;

            if (total >= x) {
                return total;
            }
        }
    }

    return total;
}

int original_cap[E];
int u[N];
int v[N];

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> m >> x;
    n += 2;

    s = 0;
    t = 1;
    // n = n + 2;  // source and sink

    for (int i = 0; i < m; i++) {
        std::cin >> u[i] >> v[i] >> original_cap[i];
        u[i] += 1;
        v[i] += 1;
    }

    double l = 0;
    double r = 1e12;
    double mid;
    int runs = 0;
    while (++runs < 100) {
        std::fill(start, start + n, -1);
        // std::fill(succ, succ + m, 0);

        mid = (l + r) / 2;
        edge_counter = 0;
        for (int i = 0; i < m; i++) {
            add_edge(u[i], v[i], std::min(1.0 * original_cap[i] / mid, 1.0 * x));
        }
        add_edge(0, 2, x);
        add_edge(n - 1, 1, x);

        // std::cout << get_max_flow()  << std::endl;
        // std::cout << (get_max_flow() >= x) << std::endl;

        if (get_max_flow() >= x) {
            l = mid;
        } else {
            r = mid;
        }
    }

    printf("%.7f\n", x * mid);

    return 0;
}
