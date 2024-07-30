#include <vector>
#include <queue>
using namespace std;

// 994. 腐烂的橘子
// 逐圈，多源，广度优先遍历
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();
        int blank = 0, good = 0, bad = 0;
        queue<pair<int, int>> bad_queue;  // <i,j> of bad orange
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) {
                    blank++;
                } else if (grid[i][j] == 1) {
                    good++;
                } else {
                    // grid[i][j] == 2
                    bad++;
                    bad_queue.push({ i, j });
                }
            }
        }
        int time_step = 0;
        while (good > 0 && !bad_queue.empty()) {
            int new_bad_num = bad_queue.size();
            int elapse = 0;
            while (new_bad_num > 0) {
                pair<int, int> loc = bad_queue.front(); bad_queue.pop();
                int i = loc.first, j = loc.second;
                if (i - 1 >= 0 && grid[i - 1][j] == 1) {
                    grid[i - 1][j] = 2; bad_queue.push({ i - 1, j }); good--; elapse = 1;
                }
                if (i + 1 < M && grid[i + 1][j] == 1) {
                    grid[i + 1][j] = 2; bad_queue.push({ i + 1, j }); good--; elapse = 1;
                }
                if (j - 1 >= 0 && grid[i][j - 1] == 1) {
                    grid[i][j - 1] = 2; bad_queue.push({ i, j - 1 }); good--; elapse = 1;
                }
                if (j + 1 < N && grid[i][j + 1] == 1) {
                    grid[i][j + 1] = 2; bad_queue.push({ i, j + 1 }); good--; elapse = 1;
                }
                new_bad_num--;
            }
            time_step += elapse;
        }
        if (good > 0) return -1;
        return time_step;
    }
};