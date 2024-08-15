// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 24. 两两交换链表中的节点
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *dummpy = new ListNode(0, head);
        ListNode *pre = dummpy, *first = head, *second = head->next;
        while (first != nullptr && second != nullptr) {
            first->next = second->next;
            second->next = first;
            pre->next = second;
            pre = first;
            if (pre->next == nullptr || pre->next->next == nullptr) break;
            first = pre->next;
            second = pre->next->next;
        }
        head = dummpy->next;
        dummpy->next = nullptr;
        delete dummpy;
        return head;
    }
};