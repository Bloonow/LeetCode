#include <stack>
#include <set>
#include <cstdint>
using namespace std;

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

namespace S1 {
// 155. 最小栈
class MinStack {
public:
    stack<int> s;
    multiset<int> must;
    MinStack() {}
    void push(int val) {
        s.push(val);
        must.insert(val);
    }
    void pop() {
        int val = s.top();
        s.pop();
        // 直接调用 erase 或删除所有值为 val 的元素，可使用迭代器只删除一个
        // must.erase(val);
        must.erase(must.find(val));
    }
    int top() {
        return s.top();
    }
    int getMin() {
        return *must.begin();
    }
};
}

namespace S2 {
// 155. 最小栈
// 不使用集合，而是用辅助栈
// 对于元素 a 而言，如果在 a 入栈时，栈中已经存在 b,c,d 元素，则在 a 出栈之前，b,c,d 一定在栈中
// 于是，对于一个特定的元素，只要它还在栈中，则它之下的栈的所有元素所有状态便是确定的，
// 因而可以使用一个辅助栈，表示一个元素入栈后，当前状态下的最小值
class MinStack {
public:
    stack<int> num_st;
    stack<int> min_st;
    MinStack() {
        min_st.push(INT32_MAX);
    }
    void push(int val) {
        num_st.push(val);
        min_st.push(min(min_st.top(), val));
    }
    void pop() {
        num_st.pop();
        min_st.pop();
    }
    int top() {
        return num_st.top();
    }
    int getMin() {
        return min_st.top();
    }
};
}

namespace S3 {
// 155. 最小栈
// 若要求额外的空间开销为 O(1) 呢？
// 答案是，使用一个额外的变量存储当前状态的最小值，考虑在 pop 退栈时，如何获得上一状态的最小值？
// 我们按照栈中每一段元素所使用的最小值，将栈划分为若干段，例如 | i,...,j | k,...,l | m,...n |
// 其中每一段都使用同一个最小值，这表示，后一段的最小值，小于前一段的，
// 更进一步分析，即每一段的第一个数，其值小于前一段的最小值，才能新起一段，并且，直到该段结束，第一个数都一直是该段的最小值
// 我们实际上存储的是，一段中的真实值，与该段最小值的差值 diff = val - min，这样，取栈顶元素时，返回 diff + min
// 而弹出栈顶时，如果 diff >= 0，则表示仍然还是这一段，min 无需变化；而 diff < 0 则表明，当前栈顶是新一段的第一个元素，
// 于是，top = pop = min，更新 min = top - diff
class MinStack {
public:
    // 使用 int64_t 防止越界
    stack<int64_t> stack;
    int64_t min;
    MinStack() {}
    void push(int value) {
        if (stack.size() == 0) {
            stack.push(0);
            min = value;
        } else {
            stack.push(value - min);
            if (value < min) min = value;
        }
    }
    void pop() {
        int64_t diff = stack.top(); stack.pop();
        if (diff < 0) {
            int64_t top = min;
            min = top - diff;
        }
    }
    int top() {
        int64_t diff = stack.top();
        if (diff < 0) {
            return min;
        } else {
            return diff + min;
        }
    }
    int getMin() {
        return min;
    }
};
}