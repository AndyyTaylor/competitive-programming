// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1381

#include <iostream>
#include <vector>

// c = next car to carry
int n, t, m;

std::pair<int, int> dp(int c, int cur_time, const std::vector<int>& arrival_times, int trips) {
    if (c >= m) {
        return std::pair<int, int>(cur_time - t, trips);
    }

    int next = arrival_times[c];
    if (cur_time < next) {
        cur_time = next;
    }

    int applicable = 1;
    int nextnext = -1;
    for (int i = c + 1; i < arrival_times.size(); i++) {
        if (applicable >= n) {
            break;
        }

        if (arrival_times[i] <= cur_time) {
            applicable++;
        } else {
            if (nextnext == -1) {
                nextnext = arrival_times[i];
            } else {
                break;
            }
        }
    }

    if (applicable >= n || c + applicable >= m) {
        return dp(c + applicable, cur_time + t * 2, arrival_times, trips + 1);
    } else {
        std::pair<int, int> info1 = dp(c + applicable, cur_time + t * 2, arrival_times, trips + 1);
        std::pair<int, int> info2 = dp(c, nextnext, arrival_times, trips);

        if (info1.second < info2.second) {
            return info1;
        } else if (info1.second == info2.second) {
            if (info1.first < info2.first) {
                return info1;
            } else {
                return info2;
            }
        } else {
            return info2;
        }
    }
}

int main() {
    int num_cases;
    std::cin >> num_cases;

    for (int casenum = 0; casenum < num_cases; casenum++) {
        std::cin >> n;
        std::cin >> t;
        std::cin >> m;

        std::vector<int> arrival_times;
        for (int i = 0; i < m; i++) {
            int a;
            std::cin >> a;
            arrival_times.push_back(a);
        }

        std::pair<int, int> info = dp(0, 0, arrival_times, 0);

        std::cout << info.first << " " << info.second << '\n';
    }
}
