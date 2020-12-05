class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> charIndex;
        for (int i = 0; i < s.size(); i++) {
            if (charIndex.find(s[i]) == charIndex.end()) {
                charIndex[s[i]] = i;
            } else {
                charIndex[s[i]] = -1;
            }
        }

        char bestChar = ' ';
        for (const auto& kv : charIndex) {
            if (kv.second == -1) {
                continue;
            }

            if (bestChar == ' ' || kv.second < charIndex[bestChar]) {
                bestChar = kv.first;
            }
        }

        if (bestChar == ' ') {
            return -1;
        } else {
            return charIndex[bestChar];
        }
    }
};
