#include<vector>
#include <string>
using namespace std;
class Solution {
public:
    int longestCommonSubsequence1(string text1, string text2) {
        //尝试暴力递归展开
        //首先我们要定义状态，来确定如何递归，常用的一个思考方式是从结尾位置考虑
        //考察字符串s1以位置i1结尾和字符串s2以位置i2结尾的最长公共子序列的长度
        //不过我们为了避免对-1位置的越界处理，我们考虑s1以len1的前缀长度与s2以len2的前缀长度的最长公共序列
        int n1 = text1.size(), n2 = text2.size();
        return f1(text1, text2, n1, n2);
    }
    int f1(string& s1, string& s2, int len1, int len2)
    {
        //base case
        if (len1 == 0 || len2 == 0)
        {
            //前缀长度为0，显然无公共部分
            return 0;
        }
        //考察四种情况，展开一共只有4种情况
        //(1)s1,s2再这个状态下s1[len1]!=s2[len2]
        //1.s1长度-1，s2长度-1，找最长公共子序列
        //2.s1长度-1，s2长度不变，找最长公共子序列
        //3.s1长度不变，s2长度-1，找最长公共子序列
        //(2)s1,s2再这个状态下s1[len1]==s2[len2]
        //那么我们选取这个位置作为最长公共子序列的一个元素，再考察s1长度-1，s2长度-1
        //根据贪心，我们知道如果对应的len1,len2越大，答案一定越优
        int ans;
        //注意长度对应的下标是长度-1
        if (s1[len1 - 1] == s2[len2 - 1])
        {
            //根据贪心，选择这个位置做答案一定是不劣的
            ans = 1 + f1(s1, s2, len1 - 1, len2 - 1);
        }
        else {
            //根据贪心，选择情况(1)的2.或3。情况一定不劣于1.
            ans = max(f1(s1, s2, len1 - 1, len2), f1(s1, s2, len1, len2 - 1));
        }
        return ans;
    }
    //缓存表，尝试记忆化搜索
    int dp[1005][1005];
    int longestCommonSubsequence2(string text1, string text2) {
        memset(dp, -1, sizeof(dp));
        int n1 = text1.size(), n2 = text2.size();
        return f2(text1, text2, n1, n2);
    }
    int f2(string& s1, string& s2, int len1, int len2)
    {
        if (len1 == 0 || len2 == 0)
        {
            return 0;
        }
        if (dp[len1][len2] != -1)
        {
            return dp[len1][len2];
        }
        int ans;
        if (s1[len1 - 1] == s2[len2 - 1])
        {
            ans = 1 + f2(s1, s2, len1 - 1, len2 - 1);
        }
        else {
            ans = max(f2(s1, s2, len1 - 1, len2), f2(s1, s2, len1, len2 - 1));
        }
        dp[len1][len2] = ans;
        return ans;
    }
    //严格位置依赖的动态规划
    int longestCommonSubsequence3(string text1, string text2) {
        memset(dp, -1, sizeof(dp));
        int n1 = text1.size(), n2 = text2.size();
        return f3(text1, text2, n1, n2);
    }
    int f3(string& s1, string& s2, int len1, int len2)
    {
        for (int j = 0; j <= len2; j++)
        {
            dp[0][j] = 0;
        }
        for (int i = 0; i <= len1; i++)
        {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= len1; i++)
        {
            for (int j = 1; j <= len2; j++)
            {
                //注意判断字符相等时，下标是长度-1
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[len1][len2];
    }
    //压缩空间
    int dp1[1005];
    int longestCommonSubsequence(string text1, string text2) {
        memset(dp1, 0, sizeof(dp1));
        int n1 = text1.size(), n2 = text2.size();
        return f4(text1, text2, n1, n2);
    }
    int f4(string& s1, string& s2, int len1, int len2)
    {
        //使用一个数组加一个变量记录左上位置来实现滚动更新
        for (int i = 1; i <= len1; i++)
        {
            int leu = 0;
            for (int j = 1; j <= len2; j++)
            {
                int tmp = dp1[j];
                if (s1[i - 1] == s2[j - 1])
                {
                    dp1[j] = 1 + leu;
                }
                else dp1[j] = max(dp1[j], dp1[j - 1]);
                leu = tmp;
            }
        }
        return dp1[len2];
    }
};