/*
给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
注意:不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。
*/
/*
示例 1：

输入：s = "1 + 1"
输出：2
示例 2：

输入：s = " 2-1 + 2 "
输出：3
示例 3：

输入：s = "(1+(4+5+2)-3)+(6+8)"
输出：23


提示：

1 <= s.length <= 3 * 105
s 由数字、'+'、'-'、'('、')'、和 ' ' 组成
s 表示一个有效的表达式
'+' 不能用作一元运算(例如， "+1" 和 "+(2 + 3)" 无效)
'-' 可以用作一元运算(即 "-1" 和 "-(2 + 3)" 是有效的)
输入中不存在两个连续的操作符
每个数字和运行的计算将适合于一个有符号的 32位 整数
*/
//我们已经实现了没有括号的表达式计算
//我们只需要一旦遇到左括号就进行递归计算
//进入递归计算括号中的一层
//遇到右括号就退出递归，就可以实现
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    int where;

    void push(stack<int>& nums, stack<char>& ops, int cur, char op) {
        if (ops.empty() || ops.top() == '+' || ops.top() == '-') {
            nums.push(cur);
            ops.push(op);
        }
        else {
            // 乘除法立即计算
            int tmp = nums.top();
            nums.pop();
            char op1 = ops.top();
            ops.pop();

            if (op1 == '*') {
                tmp *= cur;
            }
            else if (op1 == '/') {
                tmp /= cur;
            }
            nums.push(tmp);
            ops.push(op);
        }
    }

    int compute(stack<int>& nums, stack<char>& ops) {
        // 将栈转换为向量来保持顺序
        vector<int> numVec;
        vector<char> opVec;

        // 将栈内容转移到向量中（顺序是反的）
        while (!nums.empty()) {
            numVec.push_back(nums.top());
            nums.pop();
        }
        while (!ops.empty()) {
            opVec.push_back(ops.top());
            ops.pop();
        }

        // 反转向量得到正确顺序
        reverse(numVec.begin(), numVec.end());
        reverse(opVec.begin(), opVec.end());

        // 从左往右计算
        int result = numVec[0];
        for (int i = 0; i < opVec.size(); i++) {
            if (opVec[i] == '+') {
                result += numVec[i + 1];
            }
            else {
                result -= numVec[i + 1];
            }
        }

        return result;
    }

    int f(string& s, int idx) {
        stack<int> nums;
        stack<char> ops;
        int cur = 0;
        bool hasNum = false;

        while (idx < s.size() && s[idx] != ')') {
            if (s[idx] >= '0' && s[idx] <= '9') {
                cur = cur * 10 + (s[idx] - '0');
                hasNum = true;
                idx++;
            }
            else if (s[idx] == ' ') {
                idx++;
            }
            else if (s[idx] == '(') {
                cur = f(s, idx + 1);
                hasNum = true;
                idx = where + 1;
            }
            else {
                // 遇到操作符
                if (hasNum) {
                    push(nums, ops, cur, s[idx]);
                    cur = 0;
                    hasNum = false;
                }
                else {
                    // 处理一元负号
                    if (s[idx] == '-') {
                        nums.push(0);
                        ops.push('-');
                    }
                }
                idx++;
            }
        }

        // 处理最后一个数字 - 关键修改：不使用虚拟加号
        if (hasNum) {
            // 如果前面有乘除号，先计算
            if (!ops.empty() && (ops.top() == '*' || ops.top() == '/')) {
                int prev = nums.top();
                nums.pop();
                char op = ops.top();
                ops.pop();
                cur = (op == '*') ? prev * cur : prev / cur;
            }
            nums.push(cur);
        }

        where = idx;
        return compute(nums, ops);
    }

    int calculate(string s) {
        return f(s, 0);
    }
};
/*
双栈解法
我们可以使用两个栈 nums 和 ops 。

nums ： 存放所有的数字
ops ：存放所有的数字以外的操作，+/- 也看做是一种操作
然后从前往后做，对遍历到的字符做分情况讨论：

空格 : 跳过
( : 直接加入 ops 中，等待与之匹配的 )
) : 使用现有的 nums 和 ops 进行计算，直到遇到左边最近的一个左括号为止，计算结果放到 nums
数字 : 从当前位置开始继续往后取，将整一个连续数字整体取出，加入 nums
+/- : 需要将操作放入 ops 中。在放入之前先把栈内可以算的都算掉，使用现有的 nums 和 ops 进行计算，直到没有操作或者遇到左括号，计算结果放到 nums
一些细节：

由于第一个数可能是负数，为了减少边界判断。一个小技巧是先往 nums 添加一个 0
为防止 () 内出现的首个字符为运算符，将所有的空格去掉，并将 (- 替换为 (0-，(+ 替换为 (0+（当然也可以不进行这样的预处理，将这个处理逻辑放到循环里去做）
*/