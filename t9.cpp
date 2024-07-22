#include <string>
#include <vector>
using namespace std;

namespace S1 {
// 438. 找到字符串中所有字母异位词
class Solution {
public:
    bool check_same(int num1[26], int num2[26]) {
        for (int i = 0; i < 26; i++) {
            if (num1[i] != num2[i]) return false;
        }
        return true;
    }
    vector<int> findAnagrams(string s, string p) {
        vector<int> rets = {};
        if (p.length() > s.length()) return rets;
        int plen = p.length();
        int pnum[26] = { 0 };  // 用于标识字符串p的组成，从'a'到'z'
        for (int i = 0; i < plen; pnum[p[i++] - 'a']++);
        int snum[26] = { 0 };  // 用于标识字符串s的组成，从'a'到'z'
        for (int i = 0; i < plen; snum[s[i++] - 'a']++);

        bool same = check_same(pnum, snum);
        if (same) rets.push_back(0);

        int left = 0;
        for (int right = plen; right < s.length(); right++) {
            if (s[left] == s[right]) {
                // 左移窗口，滑入的字符，与滑出的字符相同
                if (same) rets.push_back(right - plen + 1);
            } else {
                // 左移窗口，滑出的字符，与滑入的字符不同
                snum[s[left] - 'a']--;
                snum[s[right] - 'a']++;
                if (same) {
                    same = false;
                } else {
                    same = check_same(pnum, snum);
                    if (same) rets.push_back(right - plen + 1);
                }
            }
            left++;
        }
        return rets;
    }
};
}

namespace S2 {
// 438. 找到字符串中所有字母异位词
class Solution {
public:
    bool check_same(int num1[26], int num2[26]) {
        for (int i = 0; i < 26; i++) {
            if (num1[i] != num2[i]) return false;
        }
        return true;
    }
    vector<int> findAnagrams(string s, string p) {
        vector<int> rets = {};
        if (p.length() > s.length()) return rets;
        // 用于标识字符串的组成，从'a'到'z'
        int pNum[26] = { 0 }, sNum[26] = { 0 };
        for (int i = 0; i < p.length(); i++) {
            pNum[p[i] - 'a']++;
            sNum[s[i] - 'a']++;
        }
        bool same = check_same(pNum, sNum);
        if (same) rets.push_back(0);
        int outIdx = 0;
        for (int inIdx = p.length(); inIdx < s.length(); inIdx++) {
            if (s[outIdx] != s[inIdx]) {
                sNum[s[inIdx] - 'a']++;   // 滑入
                sNum[s[outIdx] - 'a']--;  // 滑出
                same = check_same(pNum, sNum);
            }
            outIdx++;
            if (same) rets.push_back(outIdx);
        }
        return rets;
    }
};
}