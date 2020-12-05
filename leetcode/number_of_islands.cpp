class Solution {
public:
    vector<vector<int>> colors;

    void dfsColor(vector<vector<char>>& grid, int row, int column, int color) {
        colors[row][column] = color;

        if (row > 0 && grid[row - 1 ][column] != '0' && colors[row - 1][column] == -1) {
            dfsColor(grid, row - 1, column, color);
        }

        if (row < grid.size() - 1 && grid[row + 1 ][column] != '0' && colors[row + 1][column] == -1) {
            dfsColor(grid, row + 1, column, color);
        }

        if (column > 0 && grid[row][column - 1] != '0' && colors[row][column - 1] == -1) {
            dfsColor(grid, row, column - 1, color);
        }

        if (column < grid[0].size() - 1 && grid[row][column + 1] != '0' && colors[row][column + 1] == -1) {
            dfsColor(grid, row, column + 1, color);
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        if (grid.size() < 1) {
            return 0;
        }

        colors = vector<vector<int>>(grid.size(), vector<int>(grid[0].size(), -1));

        int color = 0;
        for (int row = 0; row < grid.size(); row++) {
            for (int column = 0; column < grid[row].size(); column++) {
                if (grid[row][column] == '0' || colors[row][column] != -1) {
                    continue;
                }

                dfsColor(grid, row, column, color);
                color++;
            }
        }

        return color;
    }
};
