// https://www.spoj.com/problems/ADABERRY/en/

#include <iostream>
#include <vector>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, std::less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 1 << 18;

int n, q;

int range_idx = 1;
int start_range[N];
int end_range[N];

std::vector<int> adj[N];
ordered_set t[2*N];

void dfs(int u, int from) {
    start_range[u] = range_idx++;
    for (auto v : adj[u]) {
        if (v == from) continue;

        dfs(v, u);
    }
    end_range[u] = range_idx;  // inclusive
}

void add_fruit(int i, int fruit) {
    for (i = start_range[i] + N; i; i /= 2) {
        // std::cout << i << " + " << fruit << "\n";
        t[i].insert(fruit);
    }
}

int l, r;
int query(int v, int node=1, int i=0, int j=N) {
    int mid = (i + j) / 2;

    if (i >= l && j <= r) {
        return t[node].order_of_key(v);
    } else if (j <= l || i >= r) {
        return 0;
    } else {
        return query(v, node*2, i, mid) + query(v, node*2+1, mid, j);
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> q;
    int fruits[n+5];
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;

        fruits[i] = a;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        add_fruit(i, fruits[i]);
    }

    // for (int i = 0; i < n; i++) {
    //     std::cout << start_range[i] << " - " << end_range[i] << '\n';
    // }

    // std::cout << query(start_range[3], end_range[3], 100) << "\n";

    // for (int i = 1; i <= n; i++) {
    //     add_fruit(i, fruits[i]);
    // }

    for (int qi = 0; qi < q; qi++) {
        int a, s;
        std::cin >> a >> s;

        l = start_range[a];
        r = end_range[a];
        std::cout << query(s) << "\n";
        add_fruit(a, s);
    }

    // for (int i = 0; i < n; i++) {
    //     std::cout << node_idx[i] << " ";
    // }

    return 0;
}
