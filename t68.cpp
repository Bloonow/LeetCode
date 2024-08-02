#include <vector>
#include <algorithm>
using namespace std;

namespace S1 {
// 4. 寻找两个正序数组的中位数
// 直接合并，然后二分，O{ (M+N)·log(M+N) }
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> vec;
        vec.insert(vec.end(), nums1.begin(), nums1.end());
        vec.insert(vec.end(), nums2.begin(), nums2.end());
        sort(vec.begin(), vec.end());
        int length = vec.size();
        return static_cast<double>(vec[(length - 1) / 2] + vec[length / 2]) / 2;
    }
};
}

namespace S2 {
// 4. 寻找两个正序数组的中位数
// 设两个数组总长度为 LEN，则中位数位置在 k = (LEN - 1) / 2 处，奇数偶数再对应调整，
// 于是问题转换成，求两个数组合并排序后，第 k 小的数；然而，求第 k 小的数，可以不用合并数组来求
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

    }
};
}
