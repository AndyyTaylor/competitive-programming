// https://codeforces.com/problemset/problem/1217/D

#include <iostream>
#include <vector>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 5010;
const int M = 5010;

int n, m;
int c[M];
bool seen[N];
bool active[N];

int numColors = 1;

int edgeColors[N][N];
std::vector<std::vector<int>> edges;

bool hasCycleUtil(int u, int color) {
    if (seen[u]) return false;

    seen[u] = true;
    active[u] = true;
    for (int v : edges[u]) {
        if (edgeColors[u][v] != color) {
            continue;
        }

        if (active[v] || hasCycleUtil(v, color)) {
            return true;
        }
    }

    active[u] = false;
    return false;
}

bool hasCycle(int color) {
    for (int i = 1; i <= n; i++) {
        seen[i] = false;
        active[i] = false;
    }

    for (int i = 1; i <= n; i++) {
        if (hasCycleUtil(i, color)) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        c[i] = -1;
    }

    edges = std::vector<std::vector<int>>(n+1, std::vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;

        edges[u].push_back(v);

        int color = 1;
        c[i] = color;
        edgeColors[u][v] = color;
        while (hasCycle(color)) {
            color++;
            c[i] = color;
            edgeColors[u][v] = color;
        }

        numColors = std::max(numColors, color);
    }

    std::cout << numColors << "\n";

    for (int i = 0; i < m; i++) {
        std::cout << c[i] << " ";
    }

    return 0;
}
