#include <vector>
#include <stack>
using namespace std;

namespace S1 {
// 84. 柱状图中最大的矩形
// 新考虑一个高度，如果它比左侧要高，则它可以和左侧的边构成一个高度更低的矩阵
// 新考虑一个高度，如果它比左侧要低，则它右侧至多只能跟它（以及左侧比它还低的高度）构成矩形，而无法跟它左侧更高的高度构成矩形
// 也就是说，只有高度一致下降，新的高度才能够考虑和左边构成矩形；只要新高度一下降，则左侧所有高于这个新高度的都可以不用考虑了
// 最坏情况下，时间复杂度 O(N^2)
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<pair<int, int>> q;  // 一个高度，以及该高度的索引
        int zero_index = -1;
        int max_area = 0;
        int cur = 0;
        for (int cur = 0; cur < heights.size(); cur++) {
            int cur_height = heights[cur];
            if (cur_height == 0) {
                // 出现零，清空，并置左边界
                zero_index = cur;
                q.clear();
                continue;
            }
            // 如果新的高度更低，则调整 q 中的数据，使得 q 中的高度都低于新高度
            while (!q.empty() && q.back().first >= cur_height) {
                q.pop_back();  // 只要队列中存在零，则永远不会被清空
            }
            // 将当前的新高度加入
            q.push_back({ cur_height, cur });
            // 依次计算可能构成矩形的面积，尽可能减少该循环的次数
            for (int i = q.size() - 1; i >= 1; i--) {
                cur_height = q[i].first;
                max_area = max(max_area, cur_height * (cur - q[i - 1].second));
            }
            max_area = max(max_area, q[0].first * (cur - zero_index));
        }
        return max_area;
    }
};
}

namespace S2 {
// 84. 柱状图中最大的矩形
// 如何将时间复杂度降低到 O(N) 级别？
// 用空间换时间，如前所述，我们可以直接找到一个柱子左侧最近的高度小于该柱子的柱子，以及右侧最近的高度小于该柱子的柱子，
// 将这两个边界的柱子的索引存储起来，就可以得到以所有柱子的情况，即
// 以所考察的柱子作为最低的一个柱子，其左右两边可以构成的矩形边界，遍历所有柱子的情况，即可求得最大矩形面积
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> left(heights.size()), right(heights.size());  // 开边界
        stack<int> stack;
        for (int i = 0; i < heights.size(); i++) {
            while (!stack.empty() && heights[stack.top()] >= heights[i]) {
                stack.pop();
            }
            left[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        stack = std::stack<int>();
        for (int i = heights.size() - 1; i >= 0; i--) {
            while (!stack.empty() && heights[stack.top()] >= heights[i]) {
                stack.pop();
            }
            right[i] = stack.empty() ? heights.size() : stack.top();
            stack.push(i);
        }
        int max_area = 0;
        for (int i = 0; i < heights.size(); i++) {
            max_area = max(max_area, (right[i] - left[i] - 1) * heights[i]);
        }
        return max_area;
    }
};
}

namespace S3 {
// 84. 柱状图中最大的矩形
// 在从左向右遍历的过程中，在弹出 stack.top() 时，说明 i 位置的柱子比 stack.top() 位置柱子要低，
// 所以可以确定 stack.top() 的有边界为 i，从而减少相应的遍历次数
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> left(heights.size()), right(heights.size(), heights.size());  // 开边界
        stack<int> stack;
        for (int i = 0; i < heights.size(); i++) {
            while (!stack.empty() && heights[stack.top()] >= heights[i]) {
                right[stack.top()] = i;
                stack.pop();
            }
            left[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        int max_area = 0;
        for (int i = 0; i < heights.size(); i++) {
            max_area = max(max_area, (right[i] - left[i] - 1) * heights[i]);
        }
        return max_area;
    }
};
}