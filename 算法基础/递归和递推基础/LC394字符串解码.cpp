/*
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

测试用例保证输出的长度不会超过 10^5。

示例 1：

输入：s = "3[a]2[bc]"
输出："aaabcbc"
示例 2：

输入：s = "3[a2[c]]"
输出："accaccacc"
示例 3：

输入：s = "2[abc]3[cd]ef"
输出："abcabccdcdcdef"
示例 4：

输入：s = "abc3[cd]xyz"
输出："abccdcdcdxyz"


提示：

1 <= s.length <= 30
s 由小写英文字母、数字和方括号 '[]' 组成
s 保证是一个 有效 的输入。
s 中所有整数的取值范围为 [1, 300]
*/
#include <string>
using namespace std;
class Solution {
public:
    int where;  // 记录递归结束时的位置

    string build(string& s, int idx) {
        string result;
        int n = s.size();

        while (idx < n && s[idx] != ']') {
            if (isalpha(s[idx])) {
                // 直接添加字母
                result += s[idx];
                idx++;
            }
            else if (isdigit(s[idx])) {
                // 解析数字（可能有多位）
                int times = 0;
                while (idx < n && isdigit(s[idx])) {
                    times = times * 10 + (s[idx] - '0');
                    idx++;
                }

                // 跳过 '['
                idx++;

                // 递归解析括号内的内容
                string inner = build(s, idx);

                // 更新索引到递归结束的位置
                idx = where;

                // 重复添加
                for (int i = 0; i < times; i++) {
                    result += inner;
                }
            }
        }

        // 记录当前位置，如果是遇到 ']' 退出，需要跳过它
        where = idx + 1;  // 这里很关键：跳过 ']'

        return result;
    }

    string decodeString(string s) {
        where = 0;
        return build(s, 0);
    }
};

//另一写法
class Solution {
public:
    int where;
    //从s[i]开始计算，遇到]就停止，返回本段的结果
    //返回之前更新全局变量where，表明下一个从哪里开始继续
    string build(string& s, int idx)
    {
        string path;
        int cnt = 0;
        while (idx < s.size() && s[idx] != ']')
        {
            if (s[idx] >= 'a' && s[idx] <= 'z')
            {
                path += s[idx];
                idx++;
            }
            else if (s[idx] >= '0' && s[idx] <= '9')
            {
                cnt = cnt * 10 + s[idx] - '0';
                idx++;
            }
            else
            {
                //左括号
                for (int i = 0; i < cnt; i++)
                {
                    path += build(s, idx + 1);
                }
                //记得更新idx，这里where在递归中已经被更新
                idx = where + 1;
                cnt = 0;
            }
        }
        where = idx;
        return path;
    }
    string decodeString(string s) {
        return build(s, 0);
    }
};

/*
嵌套类问题的解题套路
大概过程:
定义全局变量 int where
递归函数f(i) : s[i..]，从i位置出发开始解析，遇到 字符串终止 或 嵌套条件终止 就返回
返回值是f(i)负责这一段的结果
f(i)在返回前更新全局变量where，让上级函数通过where知道解析到了什么位置，进而继续

执行细节:
如果f(i)遇到 嵌套条件开始，就调用下级递归去处理嵌套，下级会负责嵌套部分的计算结果
f(i)下级处理完成后，f(i)可以根据下级更新的全局变量where，知道该从什么位置继续解析
*/