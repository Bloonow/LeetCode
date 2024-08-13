#include <vector>
using namespace std;

namespace S1 {
// 70. 爬楼梯
class Solution {
public:
    int climbStairs(int n) {
        if (n == 1) return 1;
        vector<int> kinds(n);  // 长度为 n 的数组，其中，kinds[i] 表示可以到达索引为 i 的楼梯的情况数目
        kinds[0] = 1;
        kinds[1] = 2;
        for (int i = 2; i < n; i++) {
            kinds[i] = kinds[i - 1] + kinds[i - 2];
        }
        return kinds[n - 1];
    }
};
}

namespace S2 {
// 70. 爬楼梯
// 无需记录之前的状态
class Solution {
public:
    int climbStairs(int n) {
        if (n == 1) return 1;
        if (n == 2) return 2;
        int pre1 = 1, pre2 = 2, the = 0;
        for (int i = 2; i < n; i++) {
            the = pre1 + pre2;
            pre1 = pre2;
            pre2 = the;
        }
        return the;
    }
};
}

namespace S3 {
// 70. 爬楼梯
// 根据 f(n) = f(n - 1) + f(n - 2) 递推公式，求得 [f(n+1), f(n)] = [[1, 1], [1, 0]] ^ n @ [f(1), f(0)]
// 应用矩阵的快速幂，将时间复杂度降低至 O(log(N))
class Solution {
public:
    void matrix_power(unsigned long long mat[2][2], int pow) {
        unsigned long long tmp1[2][2];
        unsigned long long tmp2[2][2];
        tmp1[0][0] = mat[0][0]; tmp1[0][1] = mat[0][1];
        tmp1[1][0] = mat[1][0]; tmp1[1][1] = mat[1][1];
        mat[0][0] = 1; mat[0][1] = 0;
        mat[1][0] = 0; mat[1][1] = 1;
        while (pow > 0) {
            if ((pow & 1) == 1) {
                tmp2[0][0] = mat[0][0] * tmp1[0][0] + mat[0][1] * tmp1[1][0];
                tmp2[0][1] = mat[0][0] * tmp1[1][0] + mat[0][1] * tmp1[1][1];
                tmp2[1][0] = mat[1][0] * tmp1[0][0] + mat[1][1] * tmp1[1][0];
                tmp2[1][1] = mat[1][0] * tmp1[0][1] + mat[1][1] * tmp1[1][1];
                mat[0][0] = tmp2[0][0]; mat[0][1] = tmp2[0][1];
                mat[1][0] = tmp2[1][0]; mat[1][1] = tmp2[1][1];
            }
            tmp2[0][0] = tmp1[0][0] * tmp1[0][0] + tmp1[0][1] * tmp1[1][0];
            tmp2[0][1] = tmp1[0][0] * tmp1[1][0] + tmp1[0][1] * tmp1[1][1];
            tmp2[1][0] = tmp1[1][0] * tmp1[0][0] + tmp1[1][1] * tmp1[1][0];
            tmp2[1][1] = tmp1[1][0] * tmp1[0][1] + tmp1[1][1] * tmp1[1][1];
            tmp1[0][0] = tmp2[0][0]; tmp1[0][1] = tmp2[0][1];
            tmp1[1][0] = tmp2[1][0]; tmp1[1][1] = tmp2[1][1];
            pow >>= 1;
        }
    }
    int climbStairs(int n) {
        if (n == 1 || n == 2) return n;
        unsigned long long mat[2][2];
        mat[0][0] = 1; mat[0][1] = 1;
        mat[1][0] = 1; mat[1][1] = 0;
        matrix_power(mat, n);
        return mat[0][0];
    }
};
}