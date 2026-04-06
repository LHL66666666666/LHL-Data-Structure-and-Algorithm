#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    int numDecodings1(string s) {
        //暴力递归尝试
        return f1(s, 0);
    }
    int f1(string& s, int i)
    {
        //参数i表示从i位置开始(到字符串末尾位置)的划分数
        //base case
        if (i == s.size())
        {
            //到越界位置,表明收集到了一个答案
            return 1;
        }
        int ans;
        if (s[i] == '0')
        {
            //无法展开的情况，有0种方法，这种情况直接否掉
            ans = 0;
        }
        else {
            //展开，分两种情况
            //自己位置(前面已经判断了自己这个位置不是0)
            ans = f1(s, i + 1);
            //两个位置
            if (i + 1 < s.size())
            {
                int tmp = 10 * (s[i] - '0') + s[i + 1] - '0';
                if (tmp >= 1 && tmp <= 26)
                {
                    ans += f1(s, i + 2);
                }
            }
        }
        return ans;
    }
    //优化成记忆化搜索
    int dp[105];
    int numDecodings2(string s) {
        memset(dp, -1, sizeof(dp));
        return f2(s, 0);
    }
    int f2(string& s, int i)
    {
        if (dp[i] != -1) return dp[i];
        //参数i表示从i位置开始(到字符串末尾位置)的划分数
        //base case
        if (i == s.size())
        {
            //到越界位置,表明收集到了一个答案
            return 1;
        }
        int ans;
        if (s[i] == '0')
        {
            //无法展开的情况，有0种方法，这种情况直接否掉
            ans = 0;
        }
        else {
            //展开，分两种情况
            //自己位置(前面已经判断了自己这个位置不是0)
            ans = f2(s, i + 1);
            //两个位置
            if (i + 1 < s.size())
            {
                int tmp = 10 * (s[i] - '0') + s[i + 1] - '0';
                if (tmp >= 1 && tmp <= 26)
                {
                    ans+= f2(s, i + 2);
                }
            }
        }
        dp[i] = ans;
        return ans;
    }
    //严格位置依赖的动态规划
    int numDecodings3(string s) {
        memset(dp, -1, sizeof(dp));
        //前面的答案依赖于后面的答案的计算
        //从后向前dp
        return f3(s);
    }
    int f3(string& s)
    {
        int n = s.size();
        dp[n] = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            int ans;
            if (s[i] == '0')
            {
                ans = 0;
            }
            else {
                ans = dp[i + 1];
                //两个位置
                if (i + 1 < n)
                {
                    int tmp = 10 * (s[i] - '0') + s[i + 1] - '0';
                    if (tmp >= 1 && tmp <= 26)
                    {
                        ans += dp[i + 2];
                    }
                }
            }
            dp[i] = ans;
        }
        return dp[0];
    }
    //还能优化，状态压缩
    //由于i位置只依赖i+1和i+2位置,可以使用滚动数组
};