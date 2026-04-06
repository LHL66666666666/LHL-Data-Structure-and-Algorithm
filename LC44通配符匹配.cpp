#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    bool isMatch1(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        dp[n][m] = 1;
        return f1(s, p, 0, 0, dp);
    }
    //记忆化搜索
    //f1(i,j)表示字符串s以i开始的后缀 和 字符串p以j开始的后缀是否可以匹配
    int f1(string& s, string& p, int i, int j, vector<vector<int>>& dp)
    {
        int n = s.size(), m = p.size();
        if (dp[i][j] != -1) return dp[i][j];
        if (i == n)
        {
            //s到底了，也就是说p要匹配空串
            if (j == m)
            {
                return 1;
            }
            else {
                dp[i][j] = p[j] == '*' && f1(s, p, i, j + 1, dp);
                return dp[i][j];
            }
        }
        else if (j == m)
        {
            //如果p到底了但s还有字符，直接false
            dp[i][j] = 0;
            return 0;
        }
        else {
            //二者都还有后缀
            //情况1:p[j]不是*
            if (p[j] != '*')
            {
                //那么要求该位置必须完全匹配
                dp[i][j] = (s[i] == p[j] || p[j] == '?') && f1(s, p, i + 1, j + 1, dp);
                return dp[i][j];
            }
            else {
                //如果是*，就是完全背包，可以不匹配或匹配无限个
                //情况1：不匹配
                int ans1 = f1(s, p, i, j + 1, dp);
                //情况2：匹配
                int ans2 = f1(s, p, i + 1, j, dp);
                dp[i][j] = ans1 || ans2;
                return dp[i][j];
            }
        }

    }
};

//严格位置依赖的dp
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        dp[n][m] = 1;
        //填base case
        //i==n时
        for (int j = m - 1; j >= 0; j--)
        {
            dp[n][j] = p[j] == '*' && dp[n][j + 1];
        }
        //j==m时
        for (int i = n - 1; i >= 0; i--)
        {
            dp[i][m] = 0;
        }
        //填dp表
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                if (p[j] != '*')
                {
                    dp[i][j] = (s[i] == p[j] || p[j] == '?') && dp[i + 1][j + 1];
                }
                else {
                    dp[i][j] = dp[i][j + 1] || dp[i + 1][j];
                }
            }
        }
        return dp[0][0];
    }
};