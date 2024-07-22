#include <vector>
#include <unordered_map>
using namespace std;

// 1. 两数之和
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int length = nums.size();
        unordered_map<int, int> hmap;  // <value, index>
        for (int i = 0; i < length; i++) {
            int need = target - nums[i];
            unordered_map<int, int>::iterator it = hmap.find(need);
            if (it != hmap.end()) {
                return {it->second, i};
            }
            hmap[nums[i]] = i;
        }
        return {};
    }
};