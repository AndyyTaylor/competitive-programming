// http://poj.org/problem?id=1308

#include <iostream>
#include <vector>

#define ll long long

const int INF = 1e9;
const int MOD = 1e9 + 7;
const ll LINF = 1e18;

std::vector<bool> seen;
std::vector<bool> root;
std::vector<bool> exists;
std::vector<std::vector<int>> edges;


bool dfs(int node) {
    if (seen[node]) {
        return false;
    }

    seen[node] = true;
    for (int i = 0; i < edges[node].size(); i++) {
        if (!dfs(edges[node][i])) {
            return false;
        }
    }

    return true;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    int k = 0;
    while (1) {
        k++;

        int e1, e2;
        std::cin >> e1 >> e2;

        if (e1 == -1 && e2 == -1) {
            break;
        }

        if (e1 == 0 && e2 == 0) {
            std::cout << "Case " << k << " is a tree.\n";
            continue;
        }

        edges.clear();
        root.clear();
        exists.clear();
        while (e1 != 0 || e2 != 0) {
            while (std::max(e1, e2) >= edges.size()) edges.push_back(std::vector<int>());
            while (std::max(e1, e2) >= root.size()) root.push_back(true);
            while (std::max(e1, e2) >= exists.size()) exists.push_back(false);

            edges[e1].push_back(e2);
            // edges[e2].push_back(e1);

            root[e2] = false;
            exists[e1] = true;
            exists[e2] = true;

            std::cin >> e1 >> e2;
        }

        int rootNode = -1;
        for (int i = 0; i < root.size(); i++) {
            if (!exists[i]) continue;

            if (root[i]) {
                if (rootNode == -1) {
                    rootNode = i;
                } else {
                    rootNode = -1;
                    break;
                }
            }
        }

        if (rootNode == -1) {
            std::cout << "Case " << k << " is not a tree.\n";
            continue;
        }

        seen = std::vector<bool>(edges.size(), false);
        if (!dfs(rootNode)) {
            std::cout << "Case " << k << " is not a tree.\n";
            continue;
        }

        bool isTree = true;
        for (int i = 0; i < seen.size(); i++) {
            if (!seen[i] && exists[i]) {
                isTree = false;
                break;
            }
        }

        if (isTree) {
            std::cout << "Case " << k << " is a tree.\n";
        } else {
            std::cout << "Case " << k << " is not a tree.\n";
        }
    }

    return 0;
}
