#include <vector>
using namespace std;

// 200. 岛屿数量
class Solution {
public:
    void DFS(vector<vector<char>>& grid, int M, int N, int r, int c) {
        if (grid[r][c] == '0' || grid[r][c] == '2') return;
        // grid[r][c] == '1'
        grid[r][c] = '2';
        if (r - 1 >= 0) DFS(grid, M, N, r - 1, c);
        if (r + 1 < M)  DFS(grid, M, N, r + 1, c);
        if (c - 1 >= 0) DFS(grid, M, N, r, c - 1);
        if (c + 1 < N)  DFS(grid, M, N, r, c + 1);
    }
    int numIslands(vector<vector<char>>& grid) {
        int M = grid.size(), N = grid[0].size();
        int count = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == '1') {
                    // 按照深度优先遍历的方式，将该陆地标记为已访问
                    DFS(grid, M, N, i, j);
                    count++;
                }
            }
        }
        return count;
    }
};