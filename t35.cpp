#include <cstdint>
#include <unordered_map>
using namespace std;

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

namespace S1 {
// 146. LRU 缓存
class LRUCache {
private:
    int m_capacity;
    int m_count;
    int cur_time = 0;
    unordered_map<int, pair<int, int>> m_map;  // key, <value, access_time>
    void remove_lru() {
        int min_time = INT32_MAX;
        std::unordered_map<int, pair<int, int>>::iterator min_iter = m_map.end();
        for (auto it = m_map.begin(); it != m_map.end(); it++) {
            if (it->second.second < min_time) {
                min_time = it->second.second;
                min_iter = it;
            }
        }
        m_map.erase(min_iter);
        m_count--;
    }
public:
    LRUCache(int capacity) : m_capacity(capacity), m_count(0) {}
    int get(int key) {
        auto it = m_map.find(key);
        if (it == m_map.end()) return -1;
        it->second.second = cur_time++;
        return it->second.first;
    }
    void put(int key, int value) {
        auto it = m_map.find(key);
        if (it == m_map.end()) {
            // 新项加入
            while (m_count >= m_capacity) remove_lru();
            m_count++;
        }
        // 旧项更新，或新项加入
        m_map[key] = make_pair(value, cur_time++);
    }
};
}

namespace S2 {
// 146. LRU 缓存
// 如何将 remove_lru() 操作降低到 O(1) 时间复杂度呢？
// 可以使用 unordered_map<key, DoubleLinkNode*> 数据结构，其中 DoubleLinkNode 是一个双向链表的节点，
// 节点头是最近访问的，节点尾是最不访问的，由此在插入删除时，即可做到 O(1) 的时间复杂度，这是以空间换时间的策略
class LRUCache {
private:
    struct DNode {
        int key, value;
        DNode *prev, *next;
        DNode(int key_ = 0, int value_ = 0, DNode *prev_ = nullptr, DNode *next_ = nullptr)
            : key(key_), value(value_), prev(prev_), next(next_) {}
    };
    int m_capacity;
    int m_count;
    DNode *m_head, *m_tail;
    unordered_map<int, DNode*> m_map;
    void remove_lru() {
        if (m_tail->prev != m_head) {
            DNode *temp = m_tail->prev;
            m_map.erase(temp->key);  // 从哈希表中释放
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            temp->prev = nullptr;
            temp->next = nullptr;
            delete temp;
        }
    }
public:
    LRUCache(int capacity) : m_capacity(capacity), m_count(0) {
        m_head = new DNode(0, 0, nullptr, nullptr);
        m_tail = new DNode(0, 0, nullptr, nullptr);
        m_head->next = m_tail;
        m_tail->prev = m_head;
    }
    ~LRUCache() {
        DNode *p = m_head;
        while (p != nullptr) {
            DNode *temp = p->next;
            p->prev = nullptr;
            p->next = nullptr;
            delete p;
            p = temp;
        }
    }
    int get(int key) {
        auto it = m_map.find(key);
        if (it == m_map.end()) return -1;
        // 将对应节点移动至链表头部，因为存在 m_head 与 m_tail，故无需判断两侧节点是否存在
        DNode *p = it->second;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        p->prev = m_head;
        p->next = m_head->next;
        p->prev->next = p;
        p->next->prev = p;
        return p->value;
    }
    void put(int key, int value) {
        auto it = m_map.find(key);
        if (it == m_map.end()) {
            // 加入新项，先判断是否超出容量
            while (m_count >= m_capacity) {
                remove_lru();
                m_count--;
            }
            DNode *p = new DNode(key, value, m_head, m_head->next);
            p->prev->next = p;
            p->next->prev = p;
            m_map[p->key] = p;  // 插入到哈希表中
            m_count++;
        } else {
            // 更新旧项，并将之移动到链表头部
            DNode *p = it->second;
            p->value = value;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            p->prev = m_head;
            p->next = m_head->next;
            p->prev->next = p;
            p->next->prev = p;
            m_map[p->key] = p;
        }
    }
};
}


