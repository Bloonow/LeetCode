#include <string>
using namespace std;

// 394. 字符串解码
// 递归 或 栈
class Solution {
public:
    int idx = 0;  // 用来标识字符串中待处理的 idx 索引上的字符
    string str;   // 待处理字符串
    bool is_alphabet() {
        return idx < str.length() && 'a' <= str[idx] && str[idx] <= 'z';
    }
    bool is_number() {
        return idx < str.length() && '0' <= str[idx] && str[idx] <= '9';
    }
    int get_number() {
        if (!is_number()) return 1;
        int num = 0;
        while (is_number()) {
            num = num * 10 + (str[idx] - '0');
            idx++;
        }
        return num;
    }
    string get_string() {
        string ret_str = "";
        while (is_alphabet()) {
            ret_str += str[idx];
            idx++;
        }
        return ret_str;
    }
    string constructString() {
        int times = get_number();
        if (str[idx] == '[') idx++;  // 左括号
        string my_str = get_string();
        while (str[idx] != ']') {
            // 下一个为数字，递归获取子部分
            if (is_number()) {
                my_str += constructString();
            } else if (is_alphabet()) {
                my_str += get_string();
            } else {
                break;
            }
        }
        if (str[idx] == ']') idx++;  // 右括号
        string ret_str = "";
        for (int i = 0; i < times; i++) ret_str += my_str;
        return ret_str;
    }
    string decodeString(string s) {
        str = s;
        string ret_str = "";
        while (idx < str.length()) {
            ret_str += constructString();
        }
        return ret_str;
    }
};