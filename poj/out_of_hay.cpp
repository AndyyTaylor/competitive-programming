// http://poj.org/problem?id=2395

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

int N, M;

// below sourced from the lecture slides
struct edge {
    int u, v, w;
};

bool operator< (const edge& a, const edge& b) {
    return a.w < b.w;
}

edge edges[10005];
int p[2005];
int size[2005];
int root(int u) {
    if (u == p[u]) {
        return u;
    }

    return p[u] = root(p[u]);
} // union - find root with path compression

void join(int u, int v) {
    u = root(u);
    v = root(v);
    if (size[u] > size[v]) {
        std::swap(u, v);
    }

    size[u] += size[v];
    p[v] = u;
} // union - find join with size heuristic

int mst() {
    std::sort(edges, edges+M); // sort by increasing weight
    int max_len = 0;

    for (int i = 0; i < M; i++) {
        edge& e = edges[i];

        // if the endpoints are in different trees , join them
        if (root(e.u) != root(e.v)) {
            if (e.w > max_len) {
                max_len = e.w;
            }

            join(e.u, e.v);
        }
    }

    return max_len;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int a, b, l;
        std::cin >> a >> b >> l;

        edges[i].u = a;
        edges[i].v = b;
        edges[i].w = l;
    }

    for (int i = 1; i <= N; i++) {
        p[i] = i;
        size[i] = 1;
    }

    std::cout << mst() << "\n";

    return 0;
}
