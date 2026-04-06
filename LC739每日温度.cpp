/*
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，
下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。
*/
#include <vector>
#include <stack>
using namespace std;
class Solution {
public:
    struct node {
        int l, r;
    }b[100005];
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> ans;
        stack<int> stk;
        int n = temperatures.size();
        //此时要维护的单调性是小压大
        for (int i = 0; i < n; i++)
        {
            while (!stk.empty() && temperatures[stk.top()] <= temperatures[i])
            {
                //结算答案
                int tmp = stk.top();
                stk.pop();
                b[tmp].r = i;
                if (!stk.empty())
                {
                    b[tmp].l = stk.top();
                }
                else b[tmp].l = -1;
            }
            //入栈
            stk.push(i);
        }
        //结算阶段
        while (!stk.empty())
        {
            int tmp = stk.top();
            stk.pop();
            b[tmp].r = -1;
            if (!stk.empty())
            {
                b[tmp].l = stk.top();
            }
            else b[tmp].l = -1;
        }
        //修正阶段
        for (int i = n - 1; i >= 0; i--)
        {
            if (b[i].r != -1 && temperatures[i] == temperatures[b[i].r])
            {
                b[i].r = b[b[i].r].r;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (b[i].r != -1)
            {
                ans.emplace_back(b[i].r - i);
            }
            else ans.emplace_back(0);
        }
        return ans;
    }
};

//这道题目可以对经典模板进行一定的优化
//因为只需要右面的数字，所以可以相等时也压入栈
//之前要求严格大于是因为需要研究左侧的答案
//这样只研究右侧可以进行改进
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> st; // todolist
        for (int i = 0; i < n; i++) {
            int t = temperatures[i];
            while (!st.empty() && t > temperatures[st.top()]) {
                int j = st.top();
                st.pop();
                ans[j] = i - j;
            }
            st.push(i);
        }
        return ans;
    }
};