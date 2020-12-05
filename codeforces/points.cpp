// https://codeforces.com/problemset/problem/19/D

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;
const int MAXX = 2e5+10;

const int N = 1 << 19;

int n;
int range_idx = 0;
int start_range[MAXX];
int end_range[MAXX];

struct node {
    int l, r, max;

    std::set<int> ys;
};

int foundX = 0;
node t[2*N];

void recalculate(int i) {
    t[i].max = std::max(t[i*2].max, t[i*2+1].max);
}

void setup_range(int i, int l, int r) {
    t[i].l = l;
    t[i].r = r;
    t[i].max = -1;
    t[i].ys.clear();

    if (l == r) {
        // don't continue to children of leaves
        return;
    }

    int mid = (l + r) / 2;
    setup_range(i * 2, l, mid);
    setup_range(i * 2 + 1, mid + 1, r);

    recalculate(i);
}

typedef std::pair<int, int> pii;
void add_y(int u, int y, int i=1) {
    if (t[i].l == t[i].r) {
        t[i].ys.insert(y);
        t[i].max = *t[i].ys.rbegin();

        return;
    }

    int mid = (t[i].l + t[i].r) / 2;
    if (u <= mid) {
        add_y(u, y, i*2);
    } else {
        add_y(u, y, i*2+1);
    }

    recalculate(i);
}

void remove_y(int u, int y, int i=1) {
    if (t[i].l == t[i].r) {
        t[i].ys.erase(y);
        if (t[i].ys.empty()) {
            t[i].max = -1;
        } else {
            t[i].max = *t[i].ys.rbegin();
        }

        return;
    }

    int mid = (t[i].l + t[i].r) / 2;
    if (u <= mid) {
        remove_y(u, y, i*2);
    } else {
        remove_y(u, y, i*2+1);
    }

    recalculate(i);
}

pii query_x(int u, int val, int i=1) {
    // std::cout << t[i].max << "\n";
    if (t[i].max <= val) {
        return pii{INF, INF};
    }

    if (t[i].l > u) {
        if (t[i].l == t[i].r) {
            return pii{t[i].l, *t[i].ys.upper_bound(val)};
        }

        auto ans = query_x(u, val, i*2);
        if (ans.first == INF) {
            ans = query_x(u, val, i*2+1);
        }

        return ans;
    } else {
        int mid = (t[i].l + t[i].r) / 2;
        auto ans = pii{INF, INF};
        if (u < mid) {
            ans = query_x(u, val, 2*i);
        }

        if (ans.first == INF) {
            ans = query_x(u, val, 2*i+1);
        }

        return ans;
    }
}

std::string cmds[MAXX];
int cX[MAXX];
int cY[MAXX];
std::vector<int> xs;

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> cmds[i] >> cX[i] >> cY[i];

        xs.push_back(cX[i]);
    }

    std::sort(xs.begin(), xs.end());

    xs.resize(std::unique(xs.begin(), xs.end()) - xs.begin());

    for (int i = 0; i < n; i++) {
        int lx = std::lower_bound(xs.begin(), xs.end(), cX[i]) - xs.begin();
        cX[i] = lx + 1;
    }

    setup_range(1, 1, xs.size());
    for (int i = 0; i < n; i++) {
        std::string cmd = cmds[i];
        int x = cX[i], y = cY[i];

        if (cmd == "add") {
            add_y(x, y);
        } else if (cmd == "remove") {
            remove_y(x, y);
        } else {
            pii best = query_x(x, y);

            if (best.first == INF || best.second == INF) {
                std::cout << "-1\n";
            } else {
                std::cout << xs[best.first-1] << " " << best.second << '\n';
            }
        }
    }

    // for (int i = 0; i <= MAXX; i++) {
    //     std::cout << start_range[i] << " - " << end_range[i] << "\n";
    // }

    return 0;
}
