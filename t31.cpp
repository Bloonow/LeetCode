#include <utility>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 25. K 个一组翻转链表
class Solution {
public:
    pair<ListNode*, ListNode*> reverse(ListNode *first, ListNode *end = nullptr) {
        ListNode *rear = first;
        ListNode *pre = first;
        ListNode *p = first->next;
        while (p != nullptr && p != end) {
            ListNode *next = p->next;
            p->next = pre;
            pre = p;
            p = next;
        }
        ListNode *head = pre;
        rear->next = nullptr;
        return make_pair(head, rear);
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr) return nullptr;
        ListNode *dummpy = new ListNode(0, head);
        ListNode *rear = dummpy;
        ListNode *kptr = rear->next;
        ListNode *first = rear->next;
        while (true) {
            int count = 0;
            for (int i = 0; i < k; i++) {
                if (kptr != nullptr) {
                    kptr = kptr->next;
                    count++;
                }
            }
            if (count < k) break;  // 已经遍历结束
            auto ret = reverse(first, kptr);
            rear->next = ret.first;  // head
            rear = ret.second;       // rear
            rear->next = kptr;
            kptr = rear->next;
            first = rear->next;
        }
        head = dummpy->next;
        dummpy->next = nullptr;
        delete dummpy;
        return head;
    }
};