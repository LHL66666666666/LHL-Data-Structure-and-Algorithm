/*
给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
整数除法仅保留整数部分。
你可以假设给定的表达式总是有效的。所有中间结果将在 [-231, 231 - 1] 的范围内。
注意：不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。


示例 1：
输入：s = "3+2*2"
输出：7

示例 2：
输入：s = " 3/2 "
输出：1

示例 3：
输入：s = " 3+5 / 2 "
输出：5

提示：
1 <= s.length <= 3 * 105
s 由整数和算符 ('+', '-', '*', '/') 组成，中间由一些空格隔开
s 表示一个 有效表达式
表达式中的所有整数都是非负整数，且在范围 [0, 231 - 1] 内
题目数据保证答案是一个 32-bit 整数
*/
#include <stack>
#include <string>
using namespace std;
class Solution {
public:
    int calculate(string s) {
        //单栈实现
        stack<int> stk;
        int n = s.size();
        int cur = 0;
        //相当于记录每一个数字之前的符号位
        char preSign = '+';
        for (int i = 0; i < n; i++)
        {
            //将元素处理进栈
            if (s[i] >= '0' && s[i] <= '9')
            {
                //记录数字
                cur = s[i] - '0' + cur * 10;
            }
            if (!isdigit(s[i]) && s[i] != ' ' || i == n - 1)
            {
                if (preSign == '+')
                {
                    stk.push(cur);
                }
                else if (preSign == '-')
                {
                    stk.push(-cur);
                }
                else if (preSign == '*')
                {
                    int num = stk.top();
                    stk.pop();
                    num *= cur;
                    stk.push(num);
                }
                else if (preSign == '/')
                {
                    int num = stk.top();
                    stk.pop();
                    num /= cur;
                    stk.push(num);
                }
                preSign = s[i];
                cur = 0;
            }
            
        }
        int ans = 0;
        while (!stk.empty())
        {
            ans += stk.top();
            stk.pop();
        }
        return ans;
        
    }
};