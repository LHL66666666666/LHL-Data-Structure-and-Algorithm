#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    //注意*的用处，*可以让前面的字符变成0个或多个
    bool isMatch1(string s, string p) {
        //先从递归入手
        return f1(s, p, 0, 0);
    }
    //递归版本，考虑两个字符串从i,j开始的后缀
    //f1表示s从i到结束位置，p从j到结束位置，是否可以完全匹配
    //我们保证p[j]一定不是*，因为任意字符串以*开头都是无意义的
    bool f1(string& s, string& p, int i, int j)
    {
        //base case
        if (i == s.size())
        {
            //越界位置，表示以空字符串进行匹配
            //情况1:p也来到越界位置，空字符串匹配空字符串，可以成功匹配
            if (j == p.size())
            {
                return true;
            }
            //情况2:p还没有来到越界位置
            //如果后面是类似a*b*c*这样的字符串(注意.*也是可以的)，那么我们可以使用*将所有前面的字符都消去
            else {
                return (j + 1 < p.size()) && (p[j + 1] == '*') && f1(s, p, i, j + 2);
            }
        }
        //如果j来到结束位置
        else if (j == p.size())
        {
            //可行情况在上面判断过，来到这个分支说明i没到结束位置，但是j到了结束位置
            return false;
        }
        else {
            //两个都不是结束位置，考虑匹配
            //跟据j+1位置是不是*来分类
            //如果不是*，那么要求这个位置s[i]和p[j]必须完全匹配
            //然后再去找后面的
            //特别地，我们将j+1越界也称为不是*
            if ((j + 1 >= p.size()) || (j + 1 < p.size() && p[j + 1] != '*'))
            {
                //后面也要匹配
                return (s[i] == p[j] || p[j] == '.') && f1(s, p, i + 1, j + 1);
            }
            //如果是*
            else {
                //那么就变成完全背包，可以使用*将这个位置字符删掉，也可以复制出来无穷多个
                //根据完全背包，不用(删掉)始终是一种选择
                //如果这个位置的原本字符是可匹配的
                int choose1 = f1(s, p, i, j + 2);
                //如果要用这个位置的，是有条件的，即这个位置两个字符匹配上了
                int choose2 = (s[i] == p[j] || p[j] == '.') && f1(s, p, i + 1, j);
                return choose1 || choose2;
            }
        }
    }
    //记忆化搜索
    bool isMatch2(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<vector<int>> dp(n + 5, vector<int>(m + 5, -1));
        return f2(s, p, 0, 0, dp);
    }
    int f2(string& s, string& p, int i, int j, vector<vector<int>>& dp)
    {
        if (i == s.size())
        {
            if (j == p.size())
            {
                return 1;
            }
            else {
                if (dp[i][j] != -1) return dp[i][j];
                int ans = (j + 1 < p.size()) && (p[j + 1] == '*') && f2(s, p, i, j + 2, dp);
                dp[i][j] = ans;
                return ans;
            }
        }
        else if (j == p.size())
        {
            return 0;
        }
        else {
            if ((j + 1 >= p.size()) || (j + 1 < p.size() && p[j + 1] != '*'))
            {
                if (dp[i][j] != -1) return dp[i][j];
                int ans = (s[i] == p[j] || p[j] == '.') && f2(s, p, i + 1, j + 1, dp);
                dp[i][j] = ans;
                return ans;
            }
            else {
                if (dp[i][j] != -1) return dp[i][j];
                int choose1 = f2(s, p, i, j + 2, dp);
                int choose2 = (s[i] == p[j] || p[j] == '.') && f2(s, p, i + 1, j, dp);
                int ans = (choose1 || choose2);
                dp[i][j] = ans;
                return ans;
            }
        }
    }
};

class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        //base case
        dp[n][m] = 1;
        for (int j = m - 1; j >= 0; j--)
        {
            dp[n][j] = (j + 1 < m) && (p[j + 1] == '*') && (dp[n][j + 2]);
        }
        for (int i = 0; i < n; i++)
        {
            dp[i][m] = 0;
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                if (j + 1 >= m || (j + 1 < m && p[j + 1] != '*')) {
                    dp[i][j] = (s[i] == p[j] || p[j] == '.') && dp[i + 1][j + 1];
                }
                else {
                    dp[i][j] = dp[i][j + 2] || (s[i] == p[j] || p[j] == '.') && dp[i + 1][j];
                }
            }
        }
        return dp[0][0];
    }
};