// https://codeforces.com/problemset/problem/651/E

#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int MAX = 1000050;

int n, m;

using pii = std::pair<int, int>;
std::vector<int> adj[MAX];

struct cell{
    int idx, val;
};

int seen[MAX];
void dfs(int u, std::vector<int>& postorder) {
    if (seen[u]) return;
    seen[u] = 1;

    for (int v : adj[u]) {
        dfs(v, postorder);
    }

    postorder.push_back(u);
}

std::vector<int> topsort() {
    std::vector<int> res;
    for (int i = 0; i < n * m; i++) {
        dfs(i, res);
    }

    // std::reverse(res.begin(), res.end());

    return res;
}

int parent[MAX];
int size[MAX];

void setup_dsu() {
    for (int i = 1; i <= n * m; i++) {
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

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> m;

    int num_lines = n + m;
    std::vector<cell> lines[num_lines];
    for (int i = 0; i < n; i++) {
        std::vector<cell> row;
        for (int j = 0; j < m; j++) {
            int v;
            std::cin >> v;

            row.push_back({i * m + j, v});
            lines[j].push_back({i * m + j, v});
        }

        lines[m + i] = row;
    }

    setup_dsu();

    for (int i = 0; i < num_lines; i++) {
        auto& line = lines[i];

        std::sort(line.begin(), line.end(), [](auto& c1, auto& c2) {
            return c1.val < c2.val;
        });

        for (int j = 1; j < line.size(); j++) {
            if (line[j].val == line[j - 1].val) {
                merge(line[j].idx, line[j - 1].idx);
            }
        }
    }

    std::vector<pii> edges;
    for (int i = 0; i < num_lines; i++) {
        auto& line = lines[i];

        std::sort(line.begin(), line.end(), [](auto& c1, auto& c2) {
            return c1.val < c2.val;
        });

        for (int j = 1; j < line.size(); j++) {
            if (line[j].val > line[j - 1].val) {
                edges.push_back({find_set(line[j].idx), find_set(line[j - 1].idx)});
                adj[find_set(line[j].idx)].push_back(find_set(line[j - 1].idx));
            }
        }
    }

    // for (auto p : edges) {
    //     std::cout << p.first << " - " << p.second << '\n';
    // }

    int dp[n * m];
    for (int i = 0; i < n * m; i++) dp[i] = 1;

    std::vector<int> postorder = topsort();
    for (auto u : postorder) {
        for (auto v : adj[u]) {
            dp[find_set(u)] = std::max(dp[find_set(u)], dp[find_set(v)] + 1);
            // std::cout << u << "\n";
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << dp[find_set(i * m + j)] << " ";
        }

        std::cout << "\n";
    }

    return 0;
}
