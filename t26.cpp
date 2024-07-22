// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 142. 环形链表 II
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) break;
        }
        if (fast == nullptr || fast->next == nullptr) return nullptr;  // 不存在环
        ListNode *ptr = head;
        while (ptr != slow) {
            ptr = ptr->next;
            slow = slow->next;
        }
        return ptr;
    }
};