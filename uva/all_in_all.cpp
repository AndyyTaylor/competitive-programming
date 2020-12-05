// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1281

#include <iostream>

int main() {
    std::string s, t;

    while (!std::cin.eof()) {
        std::cin >> s;
        std::cin >> t;

        int i = 0;
        int j = 0;
        while (i < s.length() && j < t.length()) {
            if (s[i] == t[j]) {
                i++;
            }

            j++;
        }

        if (i >= s.length()) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }

    return 0;
}
