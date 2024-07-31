#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

// 208. 实现 Trie (前缀树)
class Trie {
public:
    struct Node {
        char value;
        bool end;  // 用于判断当前字符是否是一个字符串的结束，例如，先插入 apple 再插入 app，若无 end 标记，则查询 app 不好判断
        vector<Node*> next_layer;
        Node(char ch) : value(ch), end(false), next_layer({}) {}
    };
    Node *dumppy_head = new Node('\0');
    Trie() {}
    void insert(string word) {
        Node *parent = dumppy_head;
        int length = word.length();
        int layer = 0;  // 逐层查找 word 中的字符，判断是否存在过
        for (; layer < length; layer++) {
            char ch = word[layer];  // 查找相应的元素节点
            auto iter = find_if(parent->next_layer.begin(), parent->next_layer.end(), [&ch](Node* node) {
                return node->value == ch;
            });
            if (iter == parent->next_layer.end()) break;  // 字符 ch 没找到，从该字符开始，将其插入
            parent = (*iter);  // 找到字符 ch，然后继续寻找后一个字符
        }
        if (layer == length) {
            parent->end = true;  // 查找完毕，已存在 word 字符
            return;
        }
        // 将剩余字符插入
        for (; layer < length; layer++) {
            char ch = word[layer];  // 相应的元素节点
            parent->next_layer.push_back(new Node(ch));
            parent = parent->next_layer.back();
        }
        parent->end = true;
    }
    bool search(string word) {
        Node *parent = dumppy_head;
        int length = word.length();
        int layer = 0;  // 逐层查找 word 中的字符，判断是否存在过
        for (; layer < length; layer++) {
            char ch = word[layer];  // 查找相应的元素节点
            auto iter = find_if(parent->next_layer.begin(), parent->next_layer.end(), [&ch](Node* node) {
                return node->value == ch;
            });
            if (iter == parent->next_layer.end()) break;  // 字符 ch 没找到，从该字符开始，将其插入
            parent = (*iter);  // 找到字符 ch，然后继续寻找后一个字符
        }
        if (layer == length) {
            return parent->end;
        }
        return false;
    }
    bool startsWith(string prefix) {
        Node *parent = dumppy_head;
        int length = prefix.length();
        int layer = 0;  // 逐层查找 prefix 中的字符，判断是否存在过
        for (; layer < length; layer++) {
            char ch = prefix[layer];  // 查找相应的元素节点
            auto iter = find_if(parent->next_layer.begin(), parent->next_layer.end(), [&ch](Node* node) {
                return node->value == ch;
            });
            if (iter == parent->next_layer.end()) break;  // 字符 ch 没找到，从该字符开始，将其插入
            parent = (*iter);  // 找到字符 ch，然后继续寻找后一个字符
        }
        if (layer == length) {
            return true;
        }
        return false;
    }
};
