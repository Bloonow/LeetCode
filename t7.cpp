#include <vector>
using namespace std;

namespace S1 {
// 42. 接雨水
class Solution {
public:
    int trap(vector<int>& height) {
        int lB = 0, rB = height.size() - 1;
        while (height[lB] == 0 && lB < rB) lB++;
        while (height[rB] == 0 && rB > lB) rB--;
        int factWater = 0;
        int noWater = 0;
        while (lB < rB - 1) {
            if (height[lB] <= height[rB]) {
                int i = lB + 1;
                while (height[i] < height[lB]) {
                    noWater += height[i];
                    i++;
                }
                factWater += ((i - lB - 1) * height[lB] - noWater);
                noWater = 0;
                lB = i;
            } else {
                int j = rB - 1;
                while (height[j] < height[rB]) {
                    noWater += height[j];
                    j--;
                }
                factWater += ((rB - j - 1) * height[rB] - noWater);
                noWater = 0;
                rB = j;
            }
        }
        return factWater;
    }
};
}

namespace S2 {
// 42. 接雨水
class Solution {
public:
    int trap(vector<int>& height) {
        int length = height.size();
        int left = 0, right = length - 1;
        int lMaxH = 0, rMaxH = 0;
        int water = 0;
        while (left < right) {
            lMaxH = max(lMaxH, height[left]);
            rMaxH = max(rMaxH, height[right]);
            if (height[left] < height[right]) {
                water += lMaxH - height[left];
                left++;
            } else {
                water += rMaxH - height[right];
                right--;
            }
        }
        return water;
    }
};
}