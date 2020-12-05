// http://acm.hdu.edu.cn/showproblem.php?pid=4185

#include <iostream>
#include <queue>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 610*610;

int n, m, k;
int s, t;

int start[N];
int succ[4*N], cap[4*N], to[4*N];
bool grid[610][610];

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
    for (int i = 0; i < n * n + 2; i++) {
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

int cell_id(int x, int y) {
    return y * n + x + 2;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    s = 0;
    t = 1;

    std::cin >> k;
    for (int kk = 0; kk < k; kk++) {
        std::cin >> n;
        edge_counter = 0;
        std::fill(start, start + n * n + 2, -1);

        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                char c;
                std::cin >> c;

                grid[y][x] = (c == '#');
            }
        }

        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                // std::cout << cell_id(x, y) << " " << grid[y][x] << "\n";
                if (!grid[y][x]) {
                    continue;
                }

                if (y % 2 == x % 2) {
                    // source to vertex set 1
                    add_edge(s, cell_id(x, y), 1);

                    // add edges to tile pairs
                    if (x > 0 && grid[y][x - 1]) {
                        add_edge(cell_id(x, y), cell_id(x - 1, y), 1);
                    }

                    if (x < n - 1 && grid[y][x + 1]) {
                        add_edge(cell_id(x, y), cell_id(x + 1, y), 1);
                    }

                    if (y > 0 && grid[y - 1][x]) {
                        add_edge(cell_id(x, y), cell_id(x, y - 1), 1);
                    }

                    if (y < n - 1 && grid[y + 1][x]) {
                        add_edge(cell_id(x, y), cell_id(x, y + 1), 1);
                    }
                } else {
                    // vertex set 2 to sink
                    add_edge(cell_id(x, y), t, 1);
                }
            }
        }

        std::cout << "Case " << (kk + 1) << ": " << get_max_flow() << "\n";
    }

    return 0;
}
