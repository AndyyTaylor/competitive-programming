class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        vector<vector<int>> adjList;
        vector<int> answer;
        for (int i = 0; i < N; i++) {
            adjList.push_back(vector<int>());
            answer.push_back(-1);
        }

        for (const auto& path : paths) {
            adjList[path[0] - 1].push_back(path[1] - 1);
            adjList[path[1] - 1].push_back(path[0] - 1);
        }

        for (int i = 0; i < N; i++) {
            bool possible[] = {true, true, true, true};

            for (const auto& neighbour : adjList[i]) {
                if (answer[neighbour] != -1) {
                    possible[answer[neighbour] - 1] = false;
                }
            }

            for (int j = 0; j < 4; j++) {
                if (possible[j]) {
                    answer[i] = j + 1;
                    break;
                }
            }
        }

        return answer;
    }
};
