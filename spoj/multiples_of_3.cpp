// https://www.spoj.com/problems/MULTQ3/en/

#include <iostream>
#include <bits/stdc++.h>
#include <cmath>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

const int N = 200010;

struct node {
    int lz;

    int d1, d2, d3;
};

int n, q;
node tree[N * 2];

void recalculate(int i) {
    tree[i].d1 = tree[i*2].d1 + tree[i*2+1].d1;
    tree[i].d2 = tree[i*2].d2 + tree[i*2+1].d2;
    tree[i].d3 = tree[i*2].d3 + tree[i*2+1].d3;
}

void setup_range(int i, int l, int r) {
    if (l == r) {
        // std::cout << i << '\n';
        tree[i].d1 = 0;
        tree[i].d2 = 0;
        tree[i].d3 = 1;
        tree[i].lz = 0;

        return;
    }

    int mid = (l + r) / 2;
    setup_range(i * 2, l, mid);
    setup_range(i * 2 + 1, mid + 1, r);

    recalculate(i);
}

void rotate(int i) {
    int tmp = tree[i].d3;
    tree[i].d3 = tree[i].d2;
    tree[i].d2 = tree[i].d1;
    tree[i].d1 = tmp;
}

void propogate(int i) {
    if (tree[i].lz == 0) {
        return;
    }

    for (int j = 0; j < (tree[i].lz % 3); j++) {
        rotate(i*2);
        rotate(i*2+1);
    }

    tree[i*2].lz = (tree[i*2].lz + tree[i].lz) % 3;
    tree[i*2+1].lz = (tree[i*2+1].lz + tree[i].lz) % 3;
    tree[i].lz = 0;
}

void update_range(int uL, int uR, int i=1, int cL=1, int cR=n) {
    if (cL > cR || cL > uR || cR < uL) return;

    if (cL >= uL && cR <= uR) {
        rotate(i);

        tree[i].lz = (tree[i].lz + 1) % 3;
        return;
    }

    propogate(i);

    int mid = (cL + cR) / 2;
    update_range(uL, uR, i*2, cL, mid);
    update_range(uL, uR, i*2+1, mid+1, cR);

    recalculate(i);
}

int query_range(int qL, int qR, int i=1, int cL=1, int cR=n) {
    if (cL > cR || cL > qR || cR < qL) return 0;

    if (cL >= qL && cR <= qR) {
        return tree[i].d3;
    }

    propogate(i);

    int mid = (cL + cR) / 2;
    int ans = 0;
    if (qR <= mid) {
        return query_range(qL, qR, i * 2, cL, mid);
    }

    if (mid < qL) {
        return query_range(qL, qR, i*2+1, mid+1, cR);
    }

    return query_range(qL, qR, 2*i, cL, mid) + query_range(qL, qR, i*2+1, mid+1, cR);
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n >> q;

    setup_range(1, 1, n);
    for (int k = 0; k < q; k++) {
        int c, a, b;
        std::cin >> c >> a >> b;
        a++;
        b++;

        if (c == 0) {
            update_range(a, b);
        } else if (c == 1) {
            std::cout << query_range(a, b) << "\n";
        }
        // for (int i = 1; i <= n; i++) {
        //     std::cout << query_range(i, i) << " ";
            // std::cout << i << ": " << tree[i].d1 << " " << tree[i].d2 << " " << tree[i].d3 << " (" << tree[i].lz << ")" << "\n";
        // }

        // std::cout << "\n-------\n";
    }

    return 0;
}
