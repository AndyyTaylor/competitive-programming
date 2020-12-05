// https://www.codechef.com/problems/ABROADS

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

// get excited for my 94th submission...
const int MAX = 5e5 + 5;
int parent[MAX];
int size[MAX];
long long cityPops[MAX];
long long regionPop[MAX];
std::set<std::pair<long long, int>> regionPops;

int find_set(int v) {
    if (v == parent[v]) {
        return v;
    }

    parent[v] = find_set(parent[v]);
    return parent[v];
}

void merge(int a, int b) {
    if (find_set(a) != find_set(b)) {
        a = find_set(a);
        b = find_set(b);

        if (size[a] < size[b]) {
            parent[a] = b;
            size[a] += size[b];
            regionPops.erase(std::pair<long long, int>{regionPop[a], a});
            regionPops.erase(std::pair<long long, int>{regionPop[b], b});

            regionPop[b] += regionPop[a];
            regionPops.emplace(std::pair<long long, int>{regionPop[b], b});
        } else {
            parent[b] = a;
            size[b] += size[a];
            regionPops.erase(std::pair<long long, int>{regionPop[a], a});
            regionPops.erase(std::pair<long long, int>{regionPop[b], b});

            regionPop[a] += regionPop[b];
            regionPops.emplace(std::pair<long long, int>{regionPop[a], a});
        }
    }
}

int N, M, Q;
int main() {
    std::cin >> N >> M >> Q;

    for (int i = 0; i < N; i++) {
        std::cin >> cityPops[i];
        parent[i] = i;
        size[i] = 1;

        regionPop[i] = cityPops[i];
        regionPops.emplace(std::pair<long long, int>(cityPops[i], i));
    }

    bool deletedRoads[M];
    std::vector<std::pair<int, int>> roads;
    for (int i = 0; i < M; i++) {
        int c1, c2;
        std::cin >> c1 >> c2;

        deletedRoads[i] = false;
        roads.push_back(std::pair<int, int>(--c1, --c2));
    }

    std::vector<std::pair<int, long long>> commands;
    for (int i = 0; i < Q; i++) {
        char type;
        std::cin >> type;

        if (type == 'P') {
            long long c, p;
            std::cin >> c >> p;

            c--;

            commands.push_back(std::pair<int, long long>(c, cityPops[c]));
            cityPops[c] = p;
            regionPop[c] = p;
        } else {
            int r;
            std::cin >> r;

            r--;

            deletedRoads[r] = true;
            commands.push_back(std::pair<int, long long>(-1, r));
        }
    }

    for (int i = 0; i < N; i++) {
        regionPops.emplace(std::pair<long long, int>(cityPops[i], i));
    }

    for (int i = 0; i < M; i++) {
        if (deletedRoads[i]) {
            continue;
        }

        merge(roads[i].first, roads[i].second);
    }

    std::vector<long long> popCounts;
    popCounts.push_back(regionPops.rbegin()->first);

    // for (int i = 0; i < N; i++) {
    //     std::cout << i << " in " << find_set(i) << " with pop " << regionPops[find_set(i)] << '\n';
    // }

    // think this is my first submission that i actually think this loop will run in O(nlogn)
    // which is what's required given 10^5 input size
    for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
        auto command = *it;

        if (command.first == -1) {
            merge(roads[command.second].first, roads[command.second].second);
        } else {
            regionPops.erase(std::pair<long long, int>(regionPop[find_set(command.first)], find_set(command.first)));
            regionPop[find_set(command.first)] += command.second - cityPops[command.first];
            regionPops.emplace(std::pair<long long, int>(regionPop[find_set(command.first)], find_set(command.first)));
            cityPops[command.first] = command.second;
        }

        popCounts.push_back(regionPops.rbegin()->first);

        // for (int i = 0; i < N; i++) {
        //     std::cout << i << " in " << find_set(i) << " with pop " << regionPops[find_set(i)] << '\n';
        // }
    }

    popCounts.pop_back();

    for (auto it = popCounts.rbegin(); it != popCounts.rend(); ++it) {
        std::cout << *it << '\n';
    }

    return 0;
}
