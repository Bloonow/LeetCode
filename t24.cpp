// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 234. 回文链表
class Solution {
public:
    int list_length(ListNode *head) {
        int length = 0;
        while (head != nullptr) {
            length++;
            head = head->next;
        }
        return length;
    }
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
    bool isPalindrome(ListNode* head) {
        int mid = list_length(head) / 2;
        ListNode *reverseHead = head;
        while (mid > 0) {
            reverseHead = reverseHead->next;
            mid--;
        }
        reverseHead = reverseList(reverseHead);
        while (head != nullptr && reverseHead != nullptr) {
            if (head->val != reverseHead->val) return false;
            head = head->next;
            reverseHead = reverseHead->next;
        }
        return true;
    }
};