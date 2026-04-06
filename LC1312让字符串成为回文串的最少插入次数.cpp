#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    //实际上，就是要找到最长回文子序列，其余的字母都是需要被补上的
    //假设最长回文子序列长度为x，答案即为n-x
    int f1(string& s,int i,int j,vector<vector<int>>& dp)
    {
        if (dp[i][j] != -1) return dp[i][j];
        if (i == j)
        {
            return 1;
        }
        if (i > j)
        {
            return 0;
        }
        int ret = 0;
        if (s[i] == s[j])
        {
            ret = 2 + f1(s, i + 1, j - 1, dp);
        }
        else {
            ret = max(f1(s, i + 1, j, dp), f1(s, i, j - 1, dp));
        }
        dp[i][j] = ret;
        return ret;
    }
    int minInsertions(string s) {
        int n = s.size();
        if (n == 1) return 0;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return n - f1(s, 0, n - 1, dp);
    }
};

class Solution {
public:
    //区间dp的写法，实际上和最长回文子序列异曲同工
    //dp[i][j]表示在下标l到r的范围上，要使得区间[l...r]变为回文，最少插入次数
    int f1(string& s, int l, int r, vector<vector<int>>& dp)
    {
        if (dp[l][r] != -1) return dp[l][r];
        if (l == r)
        {
            return 0;
        }
        if (l + 1 == r)
        {
            if (s[l] == s[r]) return 0;
            else return 1;
        }
        int ret = 0;
        if (s[l] == s[r])
        {
            ret = f1(s, l + 1, r - 1, dp);
        }
        else {
            ret = min(f1(s, l + 1, r, dp), f1(s, l, r - 1, dp)) + 1;
        }
        dp[l][r] = ret;
        return ret;

    }
    int minInsertions(string s) {
        int n = s.size();
        if (n == 1) return 0;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return f1(s, 0, n - 1, dp);
    }
};

class Solution {
public:
    //严格位置依赖的dp
    int minInsertions(string s) {
        int n = s.size();
        if (n == 1) return 0;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        for (int i = 0; i < n; i++)
        {
            dp[i][i] = 0;
        }
        for (int i = 0; i < n; i++)
        {
            int j = i + 1;
            if (j < n)
            {
                if (s[i] == s[j]) dp[i][j] = 0;
                else dp[i][j] = 1;
            }
        }
        for (int i = n-1; i >=0 ; i--)
        {
            for (int j = i + 2; j < n; j++)
            {
                if (s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1];
                else {
                    dp[i][j] = min(dp[i][j - 1], dp[i + 1][j]) + 1;
                }
            }
        }
        return dp[0][n - 1];
    }
};