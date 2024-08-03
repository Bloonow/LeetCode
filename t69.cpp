#include <stack>
#include <string>
using namespace std;

// 20. 有效的括号
class Solution {
public:
    bool isValid(string s) {
        stack<char> stack;
        int i = 0;
        while (i < s.length()) {
            char ch = s[i++];
            if (ch == '(' || ch == '[' || ch == '{') {
                stack.push(ch);
            } else {
                if (stack.empty()) return false;
                char left = stack.top();
                if (ch == ')' && left != '(') return false;
                if (ch == ']' && left != '[') return false;
                if (ch == '}' && left != '{') return false;
                stack.pop();
            }
        }
        return i == s.length() && stack.empty();
    }
};