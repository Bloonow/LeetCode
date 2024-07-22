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

// 148. 排序链表
// 要求 O(nlogn) 时间复杂度，O(1) 空间复杂度，需要自底向上的归并，从 subLength = 1 开始归并，长度逐渐翻倍
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
    ListNode* find_last(ListNode *ptr, int number) {
        for (int i = 1; i < number; i++) {
            if (ptr == nullptr) break;
            ptr = ptr->next;
        }
        return ptr;
    }
    // 返回两个链表合并之后的链表 [first1, last1] + [first2, last2] --> [first, last]
    pair<ListNode*, ListNode*> merge_sort(ListNode* first1, ListNode *last1, ListNode* first2, ListNode* last2) {
        if (first2 == nullptr) return make_pair(first1, last1);
        if (first1 == nullptr) return make_pair(first2, last2);
        ListNode *merge = new ListNode(-1);
        ListNode *pre = merge;
        ListNode *end1 = (last1 == nullptr) ? nullptr : last1->next;
        ListNode *end2 = (last2 == nullptr) ? nullptr : last2->next;
        while (first1 != end1 && first2 != end2) {
            if (first1->val < first2->val) {
                pre->next = first1;
                pre = first1;
                first1 = first1->next;
            } else {
                pre->next = first2;
                pre = first2;
                first2 = first2->next;
            }
        }
        ListNode *first = merge->next;
        ListNode *last = nullptr;
        if (first1 != end1) {
            pre->next = first1;
            pre = first1;
            last = last1;
        }
        if (first2 != end2) {
            pre->next = first2;
            pre = first2;
            last = last2;
        }
        merge->next = nullptr;
        delete merge;
        return make_pair(first, last);
    }
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        int all_length = list_length(head);
        ListNode *dumppy = new ListNode(0xFF, head);
        for (int sub_length = 1; sub_length < all_length; sub_length *= 2) {
            ListNode *iter = dumppy;
            while (iter != nullptr && iter->next != nullptr) {
                ListNode *first1 = iter->next;
                ListNode *last1 = find_last(first1, sub_length);
                ListNode *first2 = (last1 == nullptr) ? nullptr : last1->next;
                ListNode *last2 = find_last(first2, sub_length);
                ListNode *next_iter = (last2 == nullptr) ? nullptr : last2->next;
                auto range = merge_sort(first1, last1, first2, last2);
                iter->next = range.first;
                iter = range.second;
                if (iter != nullptr) {
                    iter->next = next_iter;
                }
            }
        }
        head = dumppy->next;
        dumppy->next = nullptr;
        delete dumppy;
        return head;
    }
};
