#include <vector>
#include <queue>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 23. 合并 K 个升序链表
// 使用优先级队列，存储每个链表的头
class Solution {
public:
    struct compare_t {
        bool operator()(ListNode* lv, ListNode* rv) {
            return lv->val > rv->val;
        }
    };
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 优先级队列，应该保证优先级越高，子段 val 越小
        priority_queue<ListNode*, vector<ListNode*>, compare_t> q;
        for (ListNode* &link : lists) {
            if (link != nullptr) q.push(link);
        }
        ListNode *dumppy = new ListNode(0x7fffffff);
        ListNode *rear = dumppy;
        while (!q.empty()) {
            rear->next = q.top();
            q.pop();
            rear = rear->next;
            if (rear->next != nullptr) q.push(rear->next);
        }
        ListNode *head = dumppy->next;
        dumppy->next = nullptr;
        delete dumppy;
        return head;
    }
};