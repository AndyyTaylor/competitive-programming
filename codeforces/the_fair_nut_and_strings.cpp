// https://codeforces.com/problemset/problem/1084/E

#include <iostream>
#include <vector>
#include <set>
#include <string>

std::vector<std::string> strings;
int main() {
    long long n, k;
    std::cin >> n >> k;

    std::string s, t;
    std::cin >> s >> t;

    long long total = 0;
    long long dist = 1;
    long long inf = 1e15;
    for (long long i = 0; i < s.size(); i++) {
        dist *= 2;

        if (s[i] == 'b') {
            dist -= 1;
        }

        if (t[i] == 'a') {
            dist -= 1;
        }

        dist = std::min(dist, inf);
        total += std::min(dist, k);
    }

    // std::cout << dist << '\n';

    std::cout << total << '\n';

    return 0;
}
