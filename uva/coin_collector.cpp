// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2231

#include <iostream>
#include <vector>

bool go(int i, int total, int types, std::vector<int>& coin_types) {
    if (i == coin_types.size()) {
        std::cout << types << '\n';
        return true;
    }

    if (total >= coin_types[i]) {
        return false;
    }

    if (go(i + 1, total + coin_types[i], types + 1, coin_types)) {
        return true;
    } else {
        return go(i + 1, total, types, coin_types);
    }
}

int main() {
    int num_cases;
    std::cin >> num_cases;

    for (int case_num = 0; case_num < num_cases; case_num++) {
        int num_coin_types;
        std::cin >> num_coin_types;

        std::vector<int> coin_types;
        for (int i = 0; i < num_coin_types; i++) {
            int c;
            std::cin >> c;
            coin_types.push_back(c);
        }

        go(0, 0, 0, coin_types);
    }
}
