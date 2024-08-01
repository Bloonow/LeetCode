#include <vector>
#include <string>
using namespace std;

// 79. 单词搜索
// 深搜
class Solution {
public:
    bool search(
        vector<vector<char>>& board, vector<vector<bool>>& visited, int r, int c, int M, int N,
        string& word, int index
    ) {
        if (index >= word.size()) return true;  // 遍历结束字符串，成功找到
        char ch = word[index];
        if (r - 1 >= 0 && visited[r - 1][c] == false && board[r - 1][c] == ch) {
            visited[r - 1][c] = true;
            bool ret = search(board, visited, r - 1, c, M, N, word, index + 1);  // 往上找到匹配
            if (ret == true) return true;
            visited[r - 1][c] = false;
        }
        if (r + 1 < M && visited[r + 1][c] == false && board[r + 1][c] == ch) {
            visited[r + 1][c] = true;
            bool ret = search(board, visited, r + 1, c, M, N, word, index + 1);  // 往下找到匹配
            if (ret == true) return true;
            visited[r + 1][c] = false;
        }
        if (c - 1 >= 0 && visited[r][c - 1] == false && board[r][c - 1] == ch) {
            visited[r][c - 1] = true;
            bool ret = search(board, visited, r, c - 1, M, N, word, index + 1);  // 往左找到匹配
            if (ret == true) return true;
            visited[r][c - 1] = false;
        }
        if (c + 1 < N && visited[r][c + 1] == false && board[r][c + 1] == ch) {
            visited[r][c + 1] = true;
            bool ret = search(board, visited, r, c + 1, M, N, word, index + 1);  // 往右找到匹配
            if (ret == true) return true;
            visited[r][c + 1] = false;
        }
        return false;  // 未找到匹配
    }
    bool exist(vector<vector<char>>& board, string word) {
        const int M = board.size(), N = board[0].size();
        vector<vector<bool>> visited;
        for (int i = 0; i < M; i++) {
            visited.push_back({});
            for (int j = 0; j < N; j++) {
                visited[i].push_back(false);
            }
        }
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                // 找到第一个匹配的字符，开始深搜
                if (board[i][j] == word[0]) {
                    visited[i][j] = true;
                    bool ret = search(board, visited, i, j, M, N, word, 1);
                    if (ret == true) return true;
                    visited[i][j] = false;
                }
            }
        }
        return false;
    }
};