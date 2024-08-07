#include <vector>
#include <map>
#include <cmath>
#include <cstdint>
using namespace std;

namespace S1 {
// 279. 完全平方数
// 备忘录法，超时
class Solution {
public:
    bool is_square(int target) {
        int root = sqrt(target);
        return target - root * root == 0;
    }
    int min_number(map<int, int>& mp, int target) {
        if (target <= 3) {
            mp[target] = target;
            return target;
        }
        if (is_square(target)) {
            mp[target] = 1;
            return 1;
        }
        int min_number_of_target = INT32_MAX;
        for (int i = sqrt(target); i >= 1; i--) {
            int smaller_target = target - i * i;
            if (mp.find(smaller_target) == mp.end()) {
                // 子问题的解不存在
                min_number_of_target = min(min_number_of_target, min_number(mp, smaller_target) + 1);
            } else {
                // 子问题的解存在
                min_number_of_target = min(min_number_of_target, mp[smaller_target] + 1);
            }
        }
        mp[target] = min_number_of_target;
        return min_number_of_target;
    }
    int numSquares(int n) {
        map<int, int> mp;  // 一个数，所需的最少的完全平方数的数量
        return min_number(mp, n);
    }
};
}

namespace S2 {
// 279. 完全平方数
// 就直接采用动态规划，使用 dp[i] 表示目标为 i 时，所需的最少的完全平方数的数目；设置虚拟边界 dp[0] = 0
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp = { 0 };
        for (int target = 1; target <= n; target++) {
            int min_number = INT32_MAX;
            for (int j = 1; j * j <= target; j++) {
                min_number = min(min_number, dp[target - j * j] + 1);
            }
            dp.push_back(min_number);
        }
        return dp[n];
    }
};
}

namespace S3 {
// 279. 完全平方数
// 四平方和定理证明了任意一个正整数都可以被表示为至多四个正整数的平方和。
class Solution {
public:
    // 判断是否为完全平方数
    bool isPerfectSquare(int x) {
        int y = sqrt(x);
        return y * y == x;
    }
    // 判断是否能表示为 4^k*(8m+7)
    bool checkAnswer4(int x) {
        while (x % 4 == 0) {
            x /= 4;
        }
        return x % 8 == 7;
    }
    int numSquares(int n) {
        if (isPerfectSquare(n)) {
            return 1;
        }
        if (checkAnswer4(n)) {
            return 4;
        }
        for (int i = 1; i * i <= n; i++) {
            int j = n - i * i;
            if (isPerfectSquare(j)) {
                return 2;
            }
        }
        return 3;
    }
};
}