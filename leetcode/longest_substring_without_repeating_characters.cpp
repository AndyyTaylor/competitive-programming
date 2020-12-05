class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int longest = 0;
        unordered_set<char> subString;
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (subString.find(c) == subString.end()) {
                subString.insert(c);
            } else {
                i -= subString.size();
                if (subString.size() > longest) {
                    longest = subString.size();
                }

                subString.clear();
            }
        }

        if (subString.size() > longest) {
            longest = subString.size();
        }

        return longest;
    }
};
