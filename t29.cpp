// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 19. 删除链表的倒数第 N 个结点
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *fast = head;
        for (int i = 0; i < n; i++) {
            if (fast == nullptr) return head;  // n 超过链表长度
            fast = fast->next;
        }
        if (fast == nullptr) {
            // 正好删除第一个节点
            ListNode *tmp = head;
            head = head->next;
            tmp->next = nullptr;
            delete tmp;
            return head;
        }
        fast = fast->next;
        ListNode *pre = head;
        while (fast != nullptr) {
            fast = fast->next;
            pre = pre->next;
        }
        ListNode *tmp = pre->next;
        pre->next = tmp->next;
        tmp->next = nullptr;
        delete tmp;
        return head;
    }
};