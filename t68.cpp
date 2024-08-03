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
// O{ (M+N) }
// 设两个数组总长度为 LEN，则中位数位置在 k = (LEN - 1) / 2 处，奇数偶数再对应调整，
// 于是问题转换成，求两个数组合并排序后，第 k 小的数；然而，求第 k 小的数，可以不用合并数组来求
// 其中 k 是索引，从 0 开始
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size(), len_total = len1 + len2;
        int target_k = (len_total - 1) / 2, k = -1, min_k, min_k_next = 0;
        int i1 = 0, i2 = 0;
        while (k != target_k && i1 < len1 && i2 < len2) {
            if (nums1[i1] < nums2[i2]) {
                k++;
                min_k = nums1[i1];
                i1++;
            } else /* nums1[i1] > nums2[i2] */ {
                k++;
                min_k = nums2[i2];
                i2++;
            }
        }
        if (k != target_k && i1 >= len1) {
            // nums1 遍历完毕，但仍未找到第 k 小的数，在 nums2 中继续查找
            i2 += target_k - k - 1;
            min_k = nums2[i2];
            i2++;
        } else if (k != target_k && i2 >= len2) {
            // nums2 遍历完毕，但仍未找到第 k 小的数，在 nums1 中继续查找
            i1 += target_k - k - 1;
            min_k = nums1[i1];
            i1++;
        }
        if (len_total % 2 == 0) {
            // 偶数个，需要找 min_k_next 的值
            if (i1 >= len1) {
                min_k_next = nums2[i2];
            } else if (i2 >= len2) {
                min_k_next = nums1[i1];
            } else {
                min_k_next = nums1[i1] < nums2[i2] ? nums1[i1] : nums2[i2];
            }
        } else {
            min_k_next = min_k;
        }
        return static_cast<double>(min_k + min_k_next) / 2;
    }
};
}

namespace S3 {
// 4. 寻找两个正序数组的中位数
// 如何将时间复杂度降低到 O{ log(M+N) } 级别呢？
class Solution {
public:
    int get_kth(const vector<int>& a1, const vector<int>& a2, int k) {
        // 从两个有序数列中找到全局第 k 小的元素，其中 k 为序号，从 1 开始
        // 动态考察 a1[k / 2 - 1] 和 a2[k / 2 - 1] 的元素，并选取 min_value = min{ a1[k / 2 - 1], a2[k / 2 - 1] }，
        // 于是两个数组中小于等于 min_value 的元素，其全局一共不会超过 (k / 2 - 1) + (k / 2 - 1) = k - 2 个
        // 这样，min_value 也只能是第 k - 1 小的元素
        // 如果 min_value == a1[k / 2]，则 a1[0 ... k / 2 - 1] 都不可能是 k 位置的元素，可全部删除
        // 如果 min_value == a2[k / 2]，则 a2[0 ... k / 2 - 1] 都不可能是 k 位置的元素，可全部删除
        // 删除后，修改相应序列的起始和终止位置，并更新 k 可以取的值
        int len1 = a1.size(), len2 = a2.size();
        int i1 = 0, i2 = 0;
        while (true) {
            // 考虑边界情况
            if (i1 == len1) {
                return a2[i2 + k - 1];
            }
            if (i2 == len2) {
                return a1[i1 + k - 1];
            }
            if (k == 1) {
                return min(a1[i1], a2[i2]);
            }
            // 正常情况
            int m1 = min(i1 + k / 2 - 1, len1 - 1);
            int m2 = min(i2 + k / 2 - 1, len2 - 1);
            int pivot1 = a1[m1], pivot2 = a2[m2];
            if (pivot1 <= pivot2) {
                k -= (m1 - i1 + 1);
                i1 = m1 + 1;
            } else /* pivot1 > pivot2 */ {
                k -= (m2 - i2 + 1);
                i2 = m2 + 1;
            }
        }
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len_total = nums1.size() + nums2.size();
        if (len_total % 2 == 1) {
            return get_kth(nums1, nums2, len_total / 2 + 1);
        } else {
            return static_cast<double>(
                get_kth(nums1, nums2, len_total / 2) + get_kth(nums1, nums2, len_total / 2 + 1)
            ) / 2;
        }
    }
};
}
