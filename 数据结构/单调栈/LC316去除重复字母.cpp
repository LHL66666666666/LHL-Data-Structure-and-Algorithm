/*
给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。
需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
*/
#include <string>
#include <vector>
#include <stack>
#include <set>
using namespace std;
class Solution {
public:
    int h[26];
    bool in[26];
    string removeDuplicateLetters(string s) {
        //思考问题的方向：每个字符可能出现多次，先用一个哈希表存储出现次数
        //我们要找字典序最小，我们就从答案的第一个位置开始构建
        //贪心来想，对于每一个位置，我们都希望找尽可能最小的，
        //我们讨论如何删除，就可以转换为讨论如何保留字符串
        //因此我们可以维护一个单调栈来维护：保留字符最小的字典序的可能性
        //具体来说需要大压小，从底部到顶部就是答案的顺序
        //维护大压小，如果出现更小的，我们希望更小的向栈底走，
        //此时讨论比它大的能不能弹出栈，如果比它大的元素后面还有(查询哈希表)，就弹出
        //否则保留
        memset(h, 0, sizeof(h));
        string ans;
        for (auto c : s)
        {
            h[c - 'a']++;
        }
        //需要开一个数组记录字符在不在栈中
        //如果在的话直接跳过,不在的话再进行一系列操作,因为栈里只能存储一个同种字符
        //维护单调栈
        stack<char> stk;
        for (int i = 0; i < s.size(); i++)
        {
            if (in[s[i] - 'a'] == 0)
            {
                while (!stk.empty() && s[i] <= stk.top() && h[stk.top() - 'a'] > 0)
                {
                    char tmp = stk.top();
                    stk.pop();
                    in[tmp - 'a'] = 0;
                }
            }
            if (in[s[i] - 'a'] == 0)
            {
                stk.push(s[i]);
                in[s[i] - 'a'] = 1;
            }
            h[s[i] - 'a']--;
        }
        while (!stk.empty())
        {
            ans += stk.top();
            stk.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};