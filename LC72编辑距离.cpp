#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    int dp[505][505];
    int minDistance(string word1, string word2) {
        return editdistance(word1, word2, 1, 1, 1);
    }
    //推广：更加一般的编辑距离问题
    //插入一个字符：代价为a
    //删除一个字符：代价为b
    //替换一个字符：代价为c
    int editdistance(string& s1, string& s2, int a, int b, int c)
    {
        //定义状态：dp[i][j]表示s1前缀长度为i,s2前缀长度为j,转化所需的最小代价
        //分类：跟据s1[i-1]也就是长度为i的位置是否参与转化进行讨论、
        //情况1：s1[i-1]参与，继续分类：
        //a.s1[i-1]匹配s2[j-1]位置的字符：
        //(1)如果s1[i-1]==s2[j-1]那么直接匹配无需操作，结果为dp[i-1][j-1]
        //(2)s1[i-1]!=s2[j-1],将s1[i-1]替换为s2[j-1]，结果为替换代价c+dp[i-1][j-1]
        //b.s1[i-1]匹配前面的字符，对于s2[j-1]我们使用插入操作实现匹配，结果为a+dp[i][j-1]
        //情况2：s1[i-1]不参与，不参与直接删除即可，前面的继续匹配j个，结果为b+dp[i-1][j]
        //基本状态(0行和0列的状态)
        //考虑i=0,s1长度为0,转化为s2,全靠插入
        //j=0,s2长度为0,s1转化s2全靠删除
        //特别地,dp[0][0]=0;
        int n = s1.size();
        int m = s2.size();
        //dp表n*m
        for (int j = 0; j <= m; j++)
        {
            dp[0][j] = j * a;
        }
        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = i * b;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                //四个候选值
                int c1 = INT_MAX, c2 = INT_MAX, c3 = INT_MAX, c4 = INT_MAX;
                if (s1[i - 1] == s2[j - 1])
                {
                    c1 = dp[i - 1][j - 1];
                }
                else c2 = c + dp[i - 1][j - 1];
                c3 = b + dp[i][j - 1];
                c4 = b + dp[i - 1][j];
                dp[i][j] = min(min(c1, c2), min(c3, c4));
            }
        }
        return dp[n][m];
    }

};