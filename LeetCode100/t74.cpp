#include <vector>
#include <cstdint>
using namespace std;

// 215. 数组中的第K个最大元素
// 小根堆，其中存储 K 个最大的元素，堆顶是这 K 个元素的最小值，
// 考察新元素，若新元素大于堆顶，则替换之，然后筛之
class Solution {
public:
    void sift(vector<int>& heap) {
        int i = 0, child = i * 2 + 1;  // 索引从零开始，所以找左孩子时需要加一
        int temp = heap[i];
        while (child < heap.size()) {
            if (child + 1 < heap.size() && heap[child] > heap[child + 1]) {
                child += 1;  // 右孩子存在，且更小
            }
            if (temp > heap[child]) {
                // 孩子节点的值更小，向下筛
                heap[i] = heap[child];
                i = child;
                child = i * 2 + 1;
            } else {
                break;
            }
        }
        heap[i] = temp;
    }
    int findKthLargest(vector<int>& nums, int k) {
        vector<int> heap(k, INT32_MIN);
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > heap.front()) {
                heap[0] = nums[i];
                sift(heap);
            }
        }
        return heap.front();
    }
};