// https://open.kattis.com/problems/classrooms

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::pair<int, int>> a;
    for (int i = 0; i < n; i++) {
        int si, fi;
        std::cin >> si >> fi;

        a.push_back(std::pair<int, int>{si, fi});
    }

    std::sort(a.begin(), a.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) -> bool {
        return a.second < b.second;
    });

    int taken = 0;
    std::multiset<int, std::greater<int>> c;
    for (auto activity : a) {
        auto lb = c.upper_bound(activity.first);

        if (lb != c.end()) {
            c.erase(lb);
            taken++;
            c.emplace(activity.second);
        } else if (c.size() < k) {
            taken++;
            c.emplace(activity.second);
        }

        // std::cout << activity.second << " - " << *c.lower_bound(activity.second) << (c.lower_bound(activity.second) == c.end()) << '\n';
    }

    std::cout << taken;

    return 0;
}