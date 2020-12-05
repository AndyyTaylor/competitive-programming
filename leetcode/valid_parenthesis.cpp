
#include <stack>

class Solution {
public:
    bool isValid(string s) {
        stack <string> stack;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                string z(1, ')');
                stack.push(z);
            } else if (s[i] == '[') {
                string z(1, ']');
                stack.push(z);
            } else if (s[i] == '{') {
                string z(1, '}');
                stack.push(z);
            } else {
                string z(1, s[i]);
                if (stack.empty() || stack.top().compare(z) != 0) {
                    return false;
                }
                stack.pop();
            }
        }

        return stack.empty();
    }
};
