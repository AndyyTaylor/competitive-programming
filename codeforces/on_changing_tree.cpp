// https://codeforces.com/problemset/problem/396/C

#include <iostream>
#include <vector>

#define ll long long
#define mod(x) (((x) % 1000000007 + 1000000007) % 1000000007)

const int INF = 1e9;
const ll LINF = 1e18;

const int N = 1 << 19;

struct node {
    ll v1, v2;
};

node t[2*N];
std::vector<int> adj[N];

int range_idx;
int start_range[N];
int end_range[N];
int level[N];

int n, q;

void dfs(int u, int lvl) {
    start_range[u] = range_idx++;
    level[u] = lvl;
    for (auto v : adj[u]) {
        dfs(v, lvl+1);
    }
    end_range[u] = range_idx;
}

void update_range(int p, int rs, int re, int s, int e, ll v1, ll v2) {
    if (rs >= s && re <= e) {
        t[p].v1 = mod(t[p].v1 + v1);
        t[p].v2 = mod(t[p].v2 + v2);
        return;
    }

    if (rs >= e || re <= s) {
        return;
    }

    int mid = (rs + re) / 2;
    update_range(p*2, rs, mid, s, e, v1, v2);
    update_range(p*2+1, mid, re, s, e, v1, v2);
}

ll query_point(int v) {
    ll v1 = 0;
    ll v2 = 0;
    for (int p = start_range[v] + N; p; p /= 2) {
        v1 = mod(v1 + t[p].v1);
        v2 = mod(v2 + t[p].v2);
    }
    return mod(v1 - v2 * level[v]);
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n;
    for (int i = 2; i <= n; i++) {
        int p;
        std::cin >> p;

        adj[p].push_back(i);
    }

    dfs(1, 0);

    // check segment construction
    // for (int i = 1; i <= n; i++) {
    //     std::cout << start_range[i] << " - " << end_range[i] << "\n";
    // }

    std::cin >> q;
    for (int qi = 0; qi < q; qi++) {
        int type;
        std::cin >> type;

        if (type == 1) {
            ll v, x, k;
            std::cin >> v >> x >> k;

            update_range(1, 0, N, start_range[v], end_range[v], mod(x + k*level[v]), k);
        } else {
            int v;
            std::cin >> v;

            std::cout << query_point(v) << "\n";
        }
    }

    // std::cout << query_point(2) << "\n";

    return 0;
}
