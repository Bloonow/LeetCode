#include <vector>
#include <queue>
using namespace std;

namespace S1 {
// 239. 滑动窗口最大值
// 使用优先队列存储前 TOP-K 个最大值元素
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> rets;
        priority_queue<pair<int, int>> queue;  // value, index
        for (int i = 0; i < k; i++) {
            queue.emplace(nums[i], i);
        }
        rets.push_back(queue.top().first);
        for (int i = k; i < nums.size(); i++) {
            queue.emplace(nums[i], i);
            // 若当前最大值位于将要被移除的窗口的左边界位置
            while (queue.top().second <= i - k) {
                queue.pop();
            }
            rets.push_back(queue.top().first);
        }
        return rets;
    }
};
}

namespace S1 {
// 239. 滑动窗口最大值
// 当窗口 Window 向右滑动一个元素时，需要更新 maxValue = max{ inEle, max{Window.remove(outEle)} }
// 最重要的是，当窗口右移滑出一个元素时，如何获取 Window.remove(outEle) 状态时的最大值
// 假设，使用 curMax 存储当前窗口的最大值，当右移窗口时，若滑出的元素就是当前最大值，则更新 curMax = Second，
// 但问题是，在更新后，还需要更新 Second = Third, Third = Fourth, ...，即需要依次更新下去
// 于是，可以使用队列结构，保持队列中 front -> rear 元素逐个减小，即队列中元素值逐个减小
// 那么，如何判断滑出的元素是否是当前最大元素呢？即判断滑出元素的索引是否超过当前队首元素的索引即可
// 在滑入新元素时，将滑入元素与队尾元素比较，若滑入元素更大，则可以依次弹出队尾元素，
// 因为滑入元素总是比队列中所有元素要新（靠右），既然滑入元素更大了，那么队列中比滑入元素更小的，就永远不会成为窗口的最大值
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> rets;
        deque<int> q;  // 双端队列，存储元素的 index 索引
        for (int i = 0; i < k; i++) {
            // 向队尾压入新的滑入元素
            while (!q.empty() && nums[q.back()] <= nums[i]) {
                q.pop_back();
            }
            q.push_back(i);
        }
        rets.push_back(nums[q.front()]);  // 第一个窗口的最大值

        for (int i = k; i < nums.size(); i++) {
            // 向队尾压入新的滑入元素
            while (!q.empty() && nums[q.back()] <= nums[i]) {
                q.pop_back();
            }
            q.push_back(i);
            // 判断滑出元素是否为当前最大值
            while (i - k >= q.front()) {
                q.pop_front();
            }
            // 记录当前窗口的最大值
            rets.push_back(nums[q.front()]);
        }
        return rets;
    }
};
}