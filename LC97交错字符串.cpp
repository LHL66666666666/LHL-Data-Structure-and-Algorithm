#include<string>
using namespace std;
class Solution {
public:
    int dp[105][105];
    //定义容易误导，实际上不严格限制交错，能组成即可
    bool isInterleave(string s1, string s2, string s3) {
        //关键是状态定义：假设dp[i][j]表示s1前长度为i个字符加上s2前长度为j个字符能否组成s3前i+j长度的串
        //0:不能，1:能
        int n = s1.size(), m = s2.size();
        int p = s3.size();
        if (p != n + m) return false;
        //基础情况：i==0或j==0
        int flagi = 1, flagj = 1;
        dp[0][0] = 1;
        for (int j = 1; j <= m; j++)
        {
            if (s2[j - 1] != s3[j - 1]) flagj = 0;
            dp[0][j] = flagj;
        }
        for (int i = 1; i <= n; i++)
        {
            if (s1[i - 1] != s3[i - 1]) flagi = 0;
            dp[i][0] = flagi;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                //判断i+j-1位置的字符由谁而来
                if (s1[i - 1] == s3[i + j - 1])
                {
                    dp[i][j] |= dp[i - 1][j];
                }
                if (s2[j - 1] == s3[i + j - 1])
                {
                    dp[i][j] |= dp[i][j - 1];
                }
            }
        }
        return dp[n][m];
    }
};