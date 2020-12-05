class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> order_ind;
        for (int i = 0; i < order.size(); i++) {
            order_ind[order[i]] = i + 1;  // + 1 to allow empty = 0
        }

        int maxLen = 0;
        for (const string& word : words) {
            if (word.size() > maxLen) {
                maxLen = word.size();
            }
        }


        for (int w = 0; w < words.size() - 1; w++) {
            string word1 = words[w];
            string word2 = words[w + 1];

            for (int i = 0; i < max(word1.size(), word2.size()); i++) {
                int ind1 = 0;
                int ind2 = 0;
                if (i < word1.size()) {
                    ind1 = order_ind[word1[i]];
                }
                if (i < word2.size()) {
                    ind2 = order_ind[word2[i]];
                }

                if (ind1 < ind2) {
                    break;
                } else if (ind1 > ind2) {
                    return false;
                }
            }
        }

        return true;
    }
};