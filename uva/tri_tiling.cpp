// https://vjudge.net/problem/UVA-10918/origin
// (couldn't resolve actual address)

#include <iostream>
#include <map>

std::map<std::tuple<int, int, int, int>, long long> dp;

long long place(int c, int r1, int r2, int r3) {
    if (c < 1) {
        if ((r1 == 0 && r2 == 0 && r3 == 1) || (r1 == 1 && r2 == 0 && r3 == 0) || (r1 == 1 && r2 == 1 && r3 == 1)) {
            return 1;
        } else {
            return 0;
        }
    }

    if (dp.find({c, r1, r2, r3}) != dp.end()) {
        return dp[{c, r1, r2, r3}];
    }

    long long val;
    if (r1 == 0 && r2 == 1 && r3 == 0) {
        val = place(c - 1, 1, 0, 1);
    } else if (r1 == 1 && r2 == 1 && r3 == 0) {
        val = place(c - 1, 0, 0, 1);
    } else if (r1 == 0 && r2 == 1 && r3 == 1) {
        val = place(c - 1, 1, 0, 0);
    } else if (r1 == 0 && r2 == 0 && r3 == 1) {
        val = place(c - 1, 0, 0, 0) + place(c - 1, 1, 1, 0);
    } else if (r1 == 1 && r2 == 0 && r3 == 0) {
        val = place(c - 1, 0, 1, 1) + place(c - 1, 0, 0, 0);
    } else if (r1 == 0 && r2 == 0 && r3 == 0) {
        val = place(c - 1, 0, 0, 1) + place(c - 1, 1, 0, 0) + place(c - 1, 1, 1, 1);
    } else if (r1 == 1 && r2 == 1 && r3 == 1) {
        val = place(c - 1, 0, 0, 0);
    } else {
        std::cout << r1 << r2 << r3 << '\n';
        exit(1);
    }

    dp[{c, r1, r2, r3}] = val;
    return val;
}

int main() {
    int n;
    std::cin >> n;

    while (n != -1) {
        if (n == 0) {
            std::cout << 1 << '\n';
        } else {
            std::cout << place(n - 1, 0, 0, 0) << '\n';
        }

        std::cin >> n;
    }

    return 0;
}