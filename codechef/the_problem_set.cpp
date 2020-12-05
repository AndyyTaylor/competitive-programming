// https://www.codechef.com/problems/ACM14KN4https://www.codechef.com/problems/ACM14KN4

#include <iostream>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 20e5;

struct node {
    ll sum;
    int max;

    int rv, lv;
    int length;

    bool increasing, decreasing;
};

int n, m;
node tree[N * 2];

node merge(node left, node right) {
    node n;

    n.sum = left.sum + right.sum;
    n.max = std::max(left.max, right.max);

    n.lv = left.lv;
    n.rv = right.rv;

    if (left.increasing && right.increasing && left.rv <= right.lv) {
        n.increasing = true;
    } else {
        n.increasing = false;
    }

    if (left.decreasing && right.decreasing && left.rv >= right.lv) {
        n.decreasing = true;
    } else {
        n.decreasing = false;
    }

    return n;
}

void recalculate(int i) {
    auto left = tree[i*2];
    auto right = tree[i*2+1];

    tree[i] = merge(left, right);
}

void setup_range(int i, int l, int r) {
    if (l == r) {
        return;
    }

    int mid = (l + r) / 2;
    setup_range(i * 2, l, mid);
    setup_range(i * 2 + 1, mid + 1, r);

    recalculate(i);
}

void point_update(int u, int v, int i=1, int l=1, int r=n) {
    if (l >= u && r <= u) {
        tree[i].sum = v;
        tree[i].max = v;

        tree[i].lv = v;
        tree[i].rv = v;
        tree[i].length = 1;

        tree[i].decreasing = true;
        tree[i].increasing = true;

        return;
    }

    int mid = (l + r) / 2;
    if (u <= mid) {
        point_update(u, v, i*2, l, mid);
    } else {
        point_update(u, v, i*2+1, mid+1, r);
    }

    recalculate(i);
}

node query(int l, int r, int node=1, int i=1, int j=n) {
    if (i >= l && j <= r) {
        // std::cout << "found at " << node << "\n";
        return tree[node];
    }

    int mid = (i + j) / 2;
    if (l <= mid && r > mid) {
        return merge(query(l, r, node*2, i, mid), query(l, r, node*2+1, mid+1, j));
    } else if (l <= mid) {
        return query(l, r, node*2, i, mid);
    } else {
        return query(l, r, node*2+1, mid+1, j);
    }
}

// int sum_query(int l, int r, int node=1, int i=1, int j=n) {
//     if (i >= l && j <= r) {
//         return tree[node].sum;
//     }

//     int mid = (i + j) / 2;
//     int ret = 0;
//     if (l <= mid) {
//         ret += sum_query(l, r, node*2, i, mid);
//     }

//     if (r > mid) {
//         ret += sum_query(l, r, node*2+1, mid+1, j);
//     }

//     return ret;
// }

// node increasing_query(int l, int r, int node=1, int i=1, int j=n) {
//     if (i >= l && j <= r) {
//         return tree[node];
//     }

//     int mid = (i + j) / 2;
//     std::pair<int, int> ret;
//     if (l <= mid) {
//         ret = increasing_query(l, r, node*2, i, mid);

//         if (r > mid) {
//             auto ret2 = increasing_query(l, r, node*2+1, mid+1, j);

//             if (ret.second > ret2.first) {
//                 return std::pair<int, int>{INF, 0};
//             } else {
//                 ret.second = ret2.second;
//             }
//         }
//     } else if (r > mid) {
//         ret = increasing_query(l, r, node*2+1, mid+1, j);
//     }

//     return ret;
// }

// std::pair<int, int> decreasing_query(int l, int r, int node=1, int i=1, int j=n) {
//     if (i >= l && j <= r) {
//         if (tree[node].decreasing) {
//             return std::pair<int, int>{tree[node].lv, tree[node].rv};
//         } else {
//             return std::pair<int, int>{0, INF};
//         }
//     }

//     int mid = (i + j) / 2;
//     std::pair<int, int> ret;
//     if (l <= mid) {
//         ret = decreasing_query(l, r, node*2, i, mid);

//         if (r > mid) {
//             auto ret2 = decreasing_query(l, r, node*2+1, mid+1, j);

//             if (ret.second < ret2.first) {
//                 return std::pair<int, int>{0, INF};
//             } else {
//                 ret.second = ret2.second;
//             }
//         }
//     } else if (r > mid) {
//         ret = decreasing_query(l, r, node*2+1, mid+1, j);
//     }

//     return ret;
// }

// std::pair<int, int> rsorted_query(int l, int r, int node=1, int i=1, int j=n) {
//     if (i >= l && j <= r) {
//         return std::pair<int, int>{node, tree[node].lcni};
//     }

//     int mid = (i + j) / 2;
//     int lcni = 0;
//     if (l <= mid) {
//         auto lnode = tree[rsorted_query(l, r, node*2, i, mid).first];
//         lcni = rsorted_query(l, r, node*2, i, mid).second;

//         if (r > mid) {
//             auto rnode = tree[rsorted_query(l, r, node*2+1, mid+1, j).first];
//             lcni = std::max(lcni, rsorted_query(l, r, node*2, i, mid).second);

//             if (lnode.rv <= rnode.lv) {
//                 lcni = std::max(lcni, lnode.lcni_r + rnode.lcni_l);
//             }
//         }
//     } else if (r > mid) {
//         lcni = rsorted_query(l, r, node*2+1, mid+1, j).second;
//     }

//     return std::pair<int, int>{node, lcni};
// }

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> m;

    setup_range(1, 1, n);

    for (int i = 1; i <= n; i++) {
        int d;
        std::cin >> d;

        point_update(i, d);
    }

    // point_update(2, 6);

    // std::cout << lsorted_query(2, 4);

    for (int q = 0; q < m; q++) {
        char c;
        int x, y;

        std::cin >> c >> x >> y;
        if (c == 'U') {
            point_update(x, y);
        } else if (c == 'M') {
            std::cout << query(x, y).max << "\n";
        } else if (c == 'S') {
            std::cout << query(x, y).sum << "\n";
        } else if (c == 'I') {
            std::cout << query(x, y).increasing << "\n";
        } else if (c == 'D') {
            std::cout << query(x, y).decreasing << "\n";
        }

        // else if (c == 'D') {
        //     std::cout << (lsorted_query(x, y).second > (y - x)) << "\n";
        // }
    }

    return 0;
}
