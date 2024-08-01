#include <vector>
#include <string>
using namespace std;

namespace S1 {
// 51. N 皇后
// 每一行、每一列、每一斜线，有且只有一个皇后
// 可以逐行判断第 i 个皇后可以放置的第 i 行中的位置
class Solution {
public:
    void backtrack(vector<vector<int>>& rets, vector<int>& location, int n, int row) {
        if (row >= n) {
            rets.push_back(location);
            return;
        }
        // 放置第 row 行的皇后，要判断 location[0: row] 行中的皇后位置
        vector<bool> can_place(n, true);  // 假设该行的所有列都可以放置
        vector<int> place;                // 实际可放置的列位置
        for (int i = 0; i < row; i++) {
            can_place[location[i]] = false;
            if (location[i] + (row - i) < n)  can_place[location[i] + (row - i)] = false;
            if (location[i] - (row - i) >= 0) can_place[location[i] - (row - i)] = false;
        }
        for (int i = 0; i < n; i++) {
            if (can_place[i] == true) place.push_back(i);
        }
        for (int i = 0; i < place.size(); i++) {
            location[row] = place[i];  // 第 row 行的皇后放在 place[i] 位置的列
            backtrack(rets, location, n, row + 1);
            location[row] = -1;        // 取消原先 place[i] 位置的列
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<int>> rets;
        vector<int> location(n, -1);  // location[i] 表示第 i 行的皇后所放置的列数
        backtrack(rets, location, n, 0);
        vector<vector<string>> str_rets;
        for (const vector<int>& resol : rets) {
            vector<string> resol_str;
            for (int row = 0; row < n; row++) {
                string sss;
                sss.assign(n, '.');
                sss[resol[row]] = 'Q';
                resol_str.push_back(sss);
            }
            str_rets.push_back(resol_str);
        }
        return str_rets;
    }
};
}

namespace S2 {
// 51. N 皇后
// 去掉一些冗余
class Solution {
public:
    bool check_location(vector<string>& board, int row, int col, int n) {
        for (int r = 0; r < row; r++) {
            if (board[r][col] == 'Q') return false;  // 若所在列已存在皇后，则该列无法再放置
        }
        for (int delta = 0 - col; delta < 0; delta++) {
            if (row + delta < 0) continue;
            if (board[row + delta][col + delta] == 'Q') return false;  // 若向左上方向已存在皇后，则无法再放置
        }
        for (int delta = n - 1 - col; delta > 0; delta--) {
            if (row - delta < 0) continue;
            if (board[row - delta][col + delta] == 'Q') return false;  // 若向右上方向已存在皇后，则无法再放置
        }
        return true;
    }
    void backtrack(vector<vector<string>>& rets, vector<string>& resol, int row, int n) {
        if (row >= n) {
            rets.push_back(resol);
            return;
        }
        for (int col = 0; col < n; col++) {
            // 依次尝试，第 col 列是否可以进行放置
            if (check_location(resol, row, col, n)) {
                resol[row][col] = 'Q';
                backtrack(rets, resol, row + 1, n);
                resol[row][col] = '.';
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> rets;
        vector<string> resol;  // 一个可能的解
        for (int row = 0; row < n; row++) {
            string row_status;
            row_status.assign(n, '.');
            resol.push_back(row_status);
        }
        backtrack(rets, resol, 0, n);
        return rets;
    }
};
}