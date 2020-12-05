#include <string>

class Solution {
public:
    string decodeString(string s) {
        string r = "";
        int count = 0;
        int startInd = -1;
        string repititions = "";
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '[') {
                count++;

                if (startInd == -1) {
                    startInd = i;
                }
            } else if (s[i] == ']'){
                count--;

                if (count == 0) {
                    int c = std::stoi(repititions);
                    string subs = decodeString(s.substr(startInd + 1, i - startInd - 1));

                    for (int j = 0; j < c; j++) {
                        r += subs;
                    }

                    startInd = -1;
                    repititions = "";
                }
            } else if (count == 0) {
                if (s[i] - '0' <= 9) {
                    repititions += s[i];
                } else {
                    r += s[i];
                }
            }
        }

        return r;
    }
};
