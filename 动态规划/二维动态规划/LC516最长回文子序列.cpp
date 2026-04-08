#include <vector>
#include <string>
using namespace std;
//实际上可以转化为最长公共子序列问题
//将字符串反转，字符串和逆序字符串的最长公共子序列即为答案
class Solution {
public:
    int longestPalindromeSubseq1(string s) {
        //状态定义：下标i位置和下标j位置之间的最长回文子序列(i<j)
        int n = s.size();
        return f1(s, 0, n - 1);
    }
    int f1(string& s, int i, int j)
    {
        if (i == j)
        {
            return 1;
        }
        if (i > j)
        {
            return 0;
        }
        int ans = 0;
        if (s[i] == s[j])
        {
            ans = 2 + f1(s, i + 1, j - 1);
        }
        else {
            ans = max(f1(s, i + 1, j), f1(s, i, j - 1));
        }
        return ans;
    }
    //记忆化搜索
    int dp1[1005][1005];
    int longestPalindromeSubseq2(string s) {
        int n = s.size();
        memset(dp1, -1, sizeof(dp1));
        return f2(s, 0, n - 1);
    }
    int f2(string& s, int i, int j)
    {
        if (i == j)
        {
            return 1;
        }
        if (i > j)
        {
            return 0;
        }
        if (dp1[i][j] != -1)
        {
            return dp1[i][j];
        }
        int ans = 0;
        if (s[i] == s[j])
        {
            ans = 2 + f2(s, i + 1, j - 1);
        }
        else {
            ans = max(f2(s, i + 1, j), f2(s, i, j - 1));
        }
        dp1[i][j] = ans;
        return ans;
    }
    //dp
    int dp[1005][1005];
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        return f3(s, 0, n - 1);
    }
    int f3(string& s, int i, int j)
    {
        int n = s.size();
        //从左下往右上来填dp表
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j <= n - 1; j++)
            {
                if (i > j) {
                    dp[i][j] = 0;
                }
                else if (i == j)
                {
                    dp[i][j] = 1;
                }
                else {
                    if (s[i] == s[j])
                    {
                        dp[i][j] = 2 + dp[i + 1][j - 1];
                    }
                    else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
    //空间压缩
};