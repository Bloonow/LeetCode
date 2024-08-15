#include <vector>
#include <queue>
using namespace std;

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

// 295. 数据流的中位数
class MedianFinder {
public:
    priority_queue<int, vector<int>, less<int>> left;      // 左侧大根堆
    priority_queue<int, vector<int>, greater<int>> right;  // 右侧小根堆
    int count = 0;
    MedianFinder() {}
    void addNum(int num) {
        if (count == 0) {
            left.push(num);  // 初始情况，两侧都为空
            count++;
        } else {
            if (count % 2 == 1) {
                // 奇数个数据，则必须要让一个数据从左侧到右侧
                if (num > left.top()) {
                    right.push(num);
                } else {
                    right.push(left.top());
                    left.pop();
                    left.push(num);
                }
            } else {
                // 偶数个数据，则插入新数据后，应确保左侧比右侧多一个
                if (num < right.top()) {
                    left.push(num);
                } else {
                    left.push(right.top());
                    right.pop();
                    right.push(num);
                }
            }
            count++;
        }
    }
    double findMedian() {
        if (count % 2 == 1) {
            return left.top();
        } else {
            return static_cast<double>(left.top() + right.top()) / 2;
        }
    }
};
