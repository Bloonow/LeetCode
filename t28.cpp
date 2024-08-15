// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 2. 两数相加
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int in = 0, val = 0;
        ListNode *head = new ListNode;
        ListNode *rear = head;
        while (l1 != nullptr && l2 != nullptr) {
            val = l1->val + l2->val + in;
            in = val / 10;
            val = val % 10;
            rear->next = new ListNode(val);
            rear = rear->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        while (l1 != nullptr) {
            val = l1->val + in;
            in = val / 10;
            val = val % 10;
            rear->next = new ListNode(val);
            rear = rear->next;
            l1 = l1->next;
        }
        while (l2 != nullptr) {
            val = l2->val + in;
            in = val / 10;
            val = val % 10;
            rear->next = new ListNode(val);
            rear = rear->next;
            l2 = l2->next;
        }
        if (in != 0) {
            rear->next = new ListNode(in);
            rear = rear->next;
        }
        rear = head;
        head = head->next;
        rear->next = nullptr;
        delete rear;
        return head;
    }
};