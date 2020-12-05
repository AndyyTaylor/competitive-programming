// https://codeforces.com/problemset/problem/609/E

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;
const int MAX = 200005;

struct edge {
    int id, u, v;

    ll w;
};

int n, m;

ll parent[MAX];
ll size[MAX];

int P[MAX][25];
ll Pw[MAX][25];
int level[MAX];

std::vector<std::pair<int, long>> adj_list[MAX];

void setup_dsu() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        size[i] = 1;
    }
}

int find_set(int v) {
    if (v == parent[v]) {
        return v;
    }

    return parent[v] = find_set(parent[v]);
}

void merge(int v, int u) {
    u = find_set(u);
    v = find_set(v);
    if (u == v) {
        return;
    }

    if (size[u] > size[v]) {
        std::swap(u, v);
    }

    parent[v] = u;
    size[u] += size[v];
}

void dfs(int from, int u, int dep) {
    P[u][0] = from;
    level[u] = dep;

    for (auto v : adj_list[u]) {
        if (v.first == from) {
            continue;
        }

        Pw[v.first][0] = v.second;
        dfs(u, v.first, dep + 1);
    }
}

void setup_lca() {
    for (int i = 1; i <= log2(n); i++) {
        for (int j = 1; j <= n; j++) {
            if (P[j][i - 1] == -1) {
                continue;
            }

            int last = P[j][i - 1];
            Pw[j][i] = std::max(Pw[j][i - 1], Pw[last][i - 1]);
            P[j][i] = P[last][i - 1];
        }
    }
}

int lca_query(int p, int q) {
    if (level[p] < level[q]) {
        std::swap(p, q);
    }

    ll ret = 0;
    int dist = level[p] - level[q];

    while (dist > 0) {
        int i = log2(dist);
        ret = std::max(ret, Pw[p][i]);
        p = P[p][i];

        dist -= (1 << i);
    }

    if (p == q) {
        return ret;
    }

    for (int i = log2(n); i >= 0; i--) {
        if (P[q][i] == -1 || P[p][i] == P[q][i]) {
            continue;
        }

        ret = std::max(ret, Pw[p][i]);
        ret = std::max(ret, Pw[q][i]);

        p = P[p][i];
        q = P[q][i];
    }

    ret = std::max(ret, Pw[p][0]);
    ret = std::max(ret, Pw[q][0]);

    return ret;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> m;
    std::vector<edge> edges;
    for (ll i = 1; i <= m; i++) {
        edge e;
        e.id = i;
        std::cin >> e.u >> e.v >> e.w;

        edges.push_back(e);
    }

    std::sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
        return a.w < b.w;
    });

    setup_dsu();

    ll totalCost = 0;
    for (int i = 0; i < m; i++) {
        edge& e = edges[i];

        if (find_set(e.u) == find_set(e.v)) {
            continue;
        }

        merge(e.u, e.v);

        totalCost = totalCost + e.w;

        adj_list[e.u].push_back({e.v, e.w});
        adj_list[e.v].push_back({e.u, e.w});
    }

    memset(P, -1, sizeof P);
    dfs(-1, 1, 1);

    setup_lca();

    std::sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
        return a.id < b.id;
    });

    for (int i = 0; i < m; i++) {
        std::cout << totalCost - lca_query(edges[i].u, edges[i].v) + edges[i].w << "\n";
    }

    return 0;
}
