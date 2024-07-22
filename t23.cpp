// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 206. 反转链表
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;
        ListNode *pre = head;
        ListNode *p = pre->next;
        pre->next = nullptr;
        while (p != nullptr) {
            ListNode *pnext = p->next;
            p->next = pre;
            pre = p;
            p = pnext;
        }
        return pre;
    }
};