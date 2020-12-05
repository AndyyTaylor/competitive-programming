class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        vector<int> trustsCount;
        vector<int> trustedCount;
        for (int i = 0; i < N; i++) {
            trustsCount.push_back(0);
            trustedCount.push_back(0);
        }

        for (const auto& pairs : trust) {
            trustsCount[pairs[0] - 1]++;
            trustedCount[pairs[1] - 1]++;
        }

        for (int i = 0; i < N; i++) {
            if (trustsCount[i] == 0 && trustedCount[i] == N - 1) {
                return i + 1;
            }
        }

        return -1;
    }
};
