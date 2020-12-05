// https://codeforces.com/gym/100200/attachments

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

#define ll long long

const int INF = 1<<30;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 1005;
const int E = 20005;

int n, m, a, b;
int s, t;

int start[N], lvl[N], nextchld[N];
bool seen[N];
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
    // add_edge_sub(v, u, 0);
} 

int inv(int e) {
    return e ^ 1;
}

bool bfs() {
    for (int i = 0; i < N; i++) {
        lvl[i] = -1;
    }

    std::queue<int> q;
    q.push(s);
    lvl[s] = 0;

    while (!q.empty()) {
        int u = q.front();
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
        }
    }

    return total;
}

void check_reach(int u) {
    if (seen[u]) return;

    seen[u] = true;

    for (int e = start[u]; ~e; e = succ[e]) {
        if (cap[e] > 0) {
            check_reach(to[e]);
        }
    }
}

int mf, oldMF;
std::vector<int> min_cut() {
    mf = get_max_flow();
    std::vector<int> ans;

    std::fill(seen, seen + N, false);
    check_reach(s);

    for (int e = 0; e < edge_counter; e += 2) {
        if (!seen[to[e]] && seen[to[inv(e)]]) {
            ans.push_back(e);
        }
    }

    return ans;
}

int us[E];
int vs[E];
int cs[E];

void init() {
    edge_counter = 0;
    std::fill(start, start + N, -1);
    std::fill(cap, cap + E, 0);
    std::fill(to, to + E, 0);
    std::fill(succ, succ + E, 0);
    std::fill(nextchld, nextchld + N, 0);
    std::fill(lvl, lvl + N, -1);

    for (int i = 0; i < m; i++) {
        add_edge(us[i], vs[i], cs[i]);
        add_edge(vs[i], us[i], cs[i]);
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::ifstream in("attack.in");
    std::cin.rdbuf(in.rdbuf());

    std::ofstream out("attack.out");
    std::cout.rdbuf(out.rdbuf());

    std::cin >> n >> m >> a >> b;

    n += 1;
    s = a;
    t = b;

    for (int i = 0; i < m; i++) {
        std::cin >> us[i] >> vs[i] >> cs[i];
    }

    init();

    auto min = min_cut();
    oldMF = mf;

    bool ambig = false;
    for (auto v : min) {
        init();
        cap[v]++;
        cap[inv(v)]++;
        min_cut();

        // std::cout << oldMF << " vs " << mf << "\n";
        if (oldMF == mf) {
            std::cout << "AMBIGUOUS\n";
            ambig = true;
            break;
        }
        cap[v]--;
        cap[inv(v)]--;
    }

    if (!ambig) {
        std::cout << "UNIQUE\n";
    }
    // std::cout << get_max_flow() << "\n";

    return 0;
}
