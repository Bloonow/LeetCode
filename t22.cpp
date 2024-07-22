// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

namespace S1 {
// 160. 相交链表
class Solution {
public:
    int length(ListNode *head) {
        int length = 0;
        while (head != nullptr) {
            length++;
            head = head->next;
        }
        return length;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int length_A = length(headA);
        int length_B = length(headB);
        if (length_A < length_B) {
            // B 向后滑动一些
            for (int i = 0; i < length_B - length_A; i++) {
                headB = headB->next;
            }
        }
        if (length_A > length_B) {
            // A 向后滑动一些
            for (int i = 0; i < length_A - length_B; i++) {
                headA = headA->next;
            }
        }
        // 判断是否存在公共交点
        while (headA != nullptr && headB != nullptr) {
            if (headA == headB) return headA;
            headA = headA->next;
            headB = headB->next;
        }
        return nullptr;
    }
};
}

namespace S2 {
// 160. 相交链表
// 使用 ptrA 遍历链表 headA，当 ptrA 访问到 A 的尾部 nullptr 时，令其指向 headB；
// 使用 ptrB 遍历链表 headB，当 ptrB 访问到 B 的尾部 nullptr 时，令其指向 headA；
// 最终情况下，ptrA 和 ptrB 都遍历了完整的 A、B 列表，且长度都为 A_length + B_length，
// 所以它们最终一定会同时在 A、B 尾部的 nullptr 处重逢，在这个过程中，若存在公共相交的节点，则一定会同时访问到
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *ptrA = headA, *ptrB = headB;
        if (ptrA == nullptr || ptrB == nullptr) return nullptr;
        while (ptrA != ptrB) {
            ptrA = (ptrA == nullptr) ? headB : ptrA->next;
            ptrB = (ptrB == nullptr) ? headA : ptrB->next;
        }
        return ptrA;
    }
};
}