#include <unordered_map>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

namespace S1 {
// 138. 随机链表的复制
// next 指向的依次深复制的节点即可，而 random 指向的则需要判断之前是否创建过，使用哈希表 hash_map<source, copied> 存储
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;
        unordered_map<Node*, Node*> mp;
        Node *newHead = new Node(head->val);
        newHead->random = head->random;
        mp[head] = newHead;  // 头节点
        Node *newPre = newHead;
        Node *p = head->next;
        while (p != nullptr) {
            Node *newNode = new Node(p->val);
            newNode->random = p->random;
            newPre->next = newNode;
            newPre = newNode;
            mp[p] = newNode;
            p = p->next;
        }
        p = newHead;
        while (p != nullptr) {
            p->random = mp[p->random];  // 将原来指向原链表的 random 指向新链表中
            p = p->next;
        }
        return newHead;
    }
};
}

namespace S2 {
// 138. 随机链表的复制
// 如何避免使用哈希表？
// 问题的关键在于，新节点根据旧结点来创建，新节点的 random 指向的是旧节点，而最终需要将新节点的 random 指向新节点
// 如果旧节点能够指向新节点，那么新节点就可以根据 random 指向旧节点，然后再找到对应的新节点，首先，创建如下新建链表
// (1) A --> B --> C --> nullptr
// (2) A --> A' --> B --> B' --> C --> C' --> nullptr
// 其中，A.next = A', A'.next = B，这样，新节点可以通过 random 指向旧节点，然后再通过 next 找到新节点，最后再将两个链表断开
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;
        Node *p, *copy;
        // 构建混合链表
        p = head;
        while (p != nullptr) {
            Node *tmp = new Node(p->val);
            tmp->random = p->random;
            tmp->next = p->next;
            p->next = tmp;
            p = tmp->next;
        }
        // 新链表创建成功，下面设置新节点的 random 指针
        p = head;
        copy = head->next;
        while (p != nullptr && copy != nullptr) {
            if (copy->random != nullptr) {
                copy->random = copy->random->next;
            }
            p = copy->next;
            if (p != nullptr) {
                copy = p->next;
            }
        }
        // 将旧链表与新链表分离
        p = head;
        copy = head->next;
        Node *copyHead = head->next;
        while (p != nullptr && copy != nullptr) {
            p->next = copy->next;
            p = p->next;
            if (p != nullptr) {
                copy->next = p->next;
                copy = copy->next;
            }
        }
        return copyHead;
    }
};
}