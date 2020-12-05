// https://codeforces.com/problemset/problem/339/D

#include <iostream>
#include <cmath>

int main() {
    int n, m;
    std::cin >> n >> m;
    auto n2 = 1 << n;

    int tree[n2 * 2 - 1];
    for (int i = n2 - 1; i < n2 * 2 - 1; ++i) {
        std::cin >> tree[i];

        // std::cout << tree[i] << " ";
    }

    // std::cout << '\n';
    for (int nn = n; nn >= 0; --nn) {
        for (int i = (1 << nn) * 2 - 2; i >= (1 << nn) - 1 && i > 0; i-=2) {
            if ((nn - n) % 2 == 0) {
                // std::cout << (i - 2) / 2 << " = " << i << " | " << i - 1 << '\n';
                tree[(i - 2) / 2] = tree[i] | tree[i - 1];
            } else {
                // std::cout << (i - 2) / 2 << " = " << i << " ^ " << i - 1 << '\n';
                tree[(i - 2) / 2] = tree[i] ^ tree[i - 1];
            }
        }
    }

    for (int mm = 0; mm < m; ++mm) {
        int p, b;
        std::cin >> p >> b;

        auto i = n2 - 1 + p - 1;
        tree[i] = b;

        int count = 0;
        while (1) {
            if ((i - 2) % 2 != 0) i++;

            if (count % 2 == 0) {
                // std::cout << (i - 2) / 2 << " = " << i << " | " << i - 1 << '\n';
                tree[(i - 2) / 2] = tree[i] | tree[i - 1];
            } else {
                // std::cout << (i - 2) / 2 << " = " << i << " ^ " << i - 1 << '\n';
                tree[(i - 2) / 2] = tree[i] ^ tree[i - 1];
            }

            i = (i - 2) / 2;
            if (i == 0) break;
            count++;
        }

        std::cout << tree[0] << '\n';
    }

    return 0;
}
