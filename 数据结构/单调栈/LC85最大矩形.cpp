#include <vector>
#include <stack>
using namespace std;
class Solution {
public:
    int ans;
    pair<int, int> b;
    void solve(vector<int>& pre,int n)
    {
        stack<int> stk;
        for (int i = 0; i < n; i++)
        {
            while (!stk.empty() && pre[i] <= pre[stk.top()])
            {
                int tmp = stk.top();
                stk.pop();
                b.second = i;
                if (!stk.empty())
                {
                    b.first = stk.top();
                }
                else b.first = -1;
                //算答案
                ans = max(ans, (b.second - b.first - 1) * pre[tmp]);
            }
            stk.push(i);
        }
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
            //算答案
            ans = max(ans, (b.second - b.first - 1) * pre[tmp]);
        }
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        ans = 0;
        //重点是数组压缩的技巧
        //自己也想到了，考虑以每一行作为底，分解为n个子问题，就转化为了n个直方图问题
        //问题是如何维护每一行作为底时，连续的1的信息
        //答案是维护前缀和数组
        //矩阵为m行n列
        int m = matrix.size();
        int n = matrix[0].size();
        //维护一个前缀和数组，代表每一列到这个位置的连续的1的个数，注意每次遇到0就需要截断
        vector<int> pre(n);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] == '1')
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