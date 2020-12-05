// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2175

#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

int main() {
    int N;
    std::cin >> N;

    for (int case_num = 0; case_num < N; ++case_num) {
        std::string eqn;
        std::cin >> eqn;

        std::stack<int> s;
        std::map<int, std::pair<int, int>> operands;
        for (int i = 0; i < eqn.size(); i++) {
            auto c = eqn[i];
            if (!isupper(c)) {
                s.push(i);
            } else {
                auto l = s.top();
                s.pop();
                auto r = s.top();
                s.pop();

                operands[i] = std::pair<int, int>{l, r};
                s.push(i);
            }
        }

        std::string res;
        std::queue<int> q;
        q.push(s.top());
        while (!q.empty()) {
            auto i = q.front();
            q.pop();

            if (isupper(eqn[i])) {
                auto pair = operands[i];
                auto l = pair.first;
                auto r = pair.second;

                q.push(r);
                q.push(l);
                res += eqn[i];
            } else {
                res += eqn[i];
            }
        }

        std::reverse(res.begin(), res.end());
        std::cout << res << '\n';
    }
}
