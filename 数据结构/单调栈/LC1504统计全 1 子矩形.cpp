/*
给你一个 m x n 的二进制矩阵 mat ，请你返回有多少个 子矩形 的元素全部都是 1 。
*/
#include <vector>
#include <stack>
using namespace std;
class Solution {
public:
    long long ans = 0;
    pair<int, int> b;
    void solve(vector<int>& pre,int n)
    {
        //做法类似直方图，维护单调栈求两侧距离最近的严格比自己小的元素
        //注意如果是因为相等而出栈的，不结算答案
        //维护大压小的单调栈
        stack<int> stk;
        for (int i = 0; i < n; i++)
        {
            while (!stk.empty() && pre[i] <= pre[stk.top()])
            {
                int tmp = stk.top();
                stk.pop();
                //如果不是相同的元素则结算答案
                if (pre[tmp] > pre[i])
                {
                    b.second = i;
                    if (!stk.empty())
                    {
                        b.first = stk.top();
                    }
                    else b.first = -1;
                    //每个元素要考虑的是比自己两个边界大，且小于等于自身高度的所有数字
                    int x = (b.first == -1 ? 0 : pre[b.first]);
                    int y = (b.second == -1 ? 0 : pre[b.second]);
                    int r = pre[tmp] - max(x,y);
                    ans += (long long)r*(b.second - b.first - 1) * (b.second - b.first) / 2;
                }
            }
            stk.push(i);
        }
        //清算阶段
        while (!stk.empty())
        {
            int tmp = stk.top();
            stk.pop();
            b.second = n;
            if (!stk.empty())
            {
                b.first = stk.top();
            }
            else b.first = -1;
            int x = (b.first == -1 ? 0 : pre[b.first]);
            int y = (b.second == -1 ? 0 : pre[b.second]);
            int r = pre[tmp] - max(x, y);
            ans += (long long)r * (b.second - b.first - 1) * (b.second - b.first) / 2;
        }
    }
    int numSubmat(vector<vector<int>>& mat) {
        ans = 0;
        //m*n矩阵
        int m = mat.size();
        int n = mat[0].size();
        //我们由直方图问题的思路，考虑以每一行为底的矩形的个数
        //维护每一列上的前缀和数组来进行压缩
        vector<int> pre(n + 1);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] != 0)
                {
                    pre[j]++;
                }
                else pre[j] = 0;
            }
            solve(pre, n);
        }
        return ans;
    }
};