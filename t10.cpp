#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

namespace S1 {
// 560. 和为 K 的子数组
// 设 i <= j，且 j = 0 -> N-1 遍历数组，表示以 j 索引处结尾的子数组 [i, j]
// 由 i = j -> 0 依次遍历子数组 [i, j]，组成不同的子数组长度，判断其和是否为所求
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ok = 0;
        for (int j = 0; j < nums.size(); j++) {
            int sum = nums[j];
            if (sum == k) ok++;
            for (int i = j - 1; i >= 0; i--) {
                sum += nums[i];
                if (sum == k) ok++;
            }
        }
        return ok;
    }
};
}

namespace S2 {
// 560. 和为 K 的子数组
// 先做包含扫描，即求前缀和 prefix{N}，则任意子序列 sub[i,j] 之和可以由 prefix[j] - prefix[i-1] 求得
// 于是问题转换为：求满足 prefix[j] - prefix[i-1] == k 的子序列的个数，选取 j 索引作为外层循环的变量
// 则问题转换为：在数组 prefix{j} 中，寻找满足 prefix[j] - k == prefix[i-1] 的索引 i 的数目
// 使用哈希表来存储在遍历 prefix[j] 时，其所需要的 prefix[j] - k 是否存在过，以及存在多少个，
// 然后将当前的 prefix[j] 值在累计存入到哈希表中，以供右侧的 prefix 查找
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        int prefix = 0, need;
        unordered_map<int, int> mp;  // need, times
        mp[0] = 1;  // 处理 need = prefix - k == 0 也即 prefix == k 的情况
        for (int i = 0; i < nums.size(); i++) {
            prefix += nums[i];
            need = prefix - k;
            if (mp.find(need) != mp.end()) {
                count += mp[need];
            }
            mp[prefix]++;
        }
        return count;
    }
};
}