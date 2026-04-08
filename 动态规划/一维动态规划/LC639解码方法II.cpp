#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    const int MOD = 1e9 + 7;
    int numDecodings1(string s) {
        //尝试暴力递归展开
        return f1(s, 0);
    }
    long long f1(string& s, int i)
    {
        if (i == s.size())
        {
            return 1;
        }
        long long ans = 0;
        if (s[i] == '0')
        {
            ans = 0;
        }
        else {
            //使用一位
            if (s[i] == '*')
            {
                ans = (9 % MOD * f1(s, i + 1) % MOD) % MOD;
            }
            else ans = f1(s, i + 1);
            ans %= MOD;
            //使用两位
            if (i + 1 < s.size())
            {
                if (s[i] == '1')
                {
                    if (s[i + 1] >= '0' && s[i + 1] <= '9')
                    {
                        ans += f1(s, i + 2);
                    }
                    else if (s[i + 1] == '*')
                    {
                        ans += 9 * f1(s, i + 2);
                    }
                }
                else if (s[i] == '2')
                {
                    if (s[i + 1] >= '0' && s[i + 1] <= '6')
                    {
                        ans += f1(s, i + 2);
                    }
                    else if (s[i + 1] == '*')
                    {
                        ans += 6 * f1(s, i + 2);
                    }
                }
                else if (s[i] == '*')
                {
                    if (s[i + 1] == '*')
                    {
                        ans += 15 * f1(s, i + 2);
                    }
                    else if (s[i + 1] >= '0' && s[i + 1] <= '6')
                    {
                        ans += 2 * f1(s, i + 2);
                    }
                    else if (s[i + 1] >= '7' && s[i + 1] <= '9')
                    {
                        ans += f1(s, i + 2);
                    }
                }
            }
        }
        ans %= MOD;
        return ans;
    }
    //尝试记忆化搜索
    long long dp[100005];
    int numDecodings2(string s) {
        //记忆化搜索，开缓存表
        memset(dp, -1, sizeof(dp));
        return f2(s, 0);
    }
    long long f2(string& s, int i)
    {
        if (i == s.size())
        {
            return 1;
        }
        if (dp[i] != -1)
        {
            return dp[i];
        }
        long long ans = 0;
        if (s[i] == '0')
        {
            ans = 0;
        }
        else {
            //使用一位
            if (s[i] == '*')
            {
                ans = (9 % MOD * f2(s, i + 1) % MOD) % MOD;
            }
            else ans = f2(s, i + 1);
            ans %= MOD;
            //使用两位
            if (i + 1 < s.size())
            {
                if (s[i] == '1')
                {
                    if (s[i + 1] >= '0' && s[i + 1] <= '9')
                    {
                        ans += f2(s, i + 2);
                    }
                    else if (s[i + 1] == '*')
                    {
                        ans += 9 * f2(s, i + 2);
                    }
                }
                else if (s[i] == '2')
                {
                    if (s[i + 1] >= '0' && s[i + 1] <= '6')
                    {
                        ans += f2(s, i + 2);
                    }
                    else if (s[i + 1] == '*')
                    {
                        ans += 6 * f2(s, i + 2);
                    }
                }
                else if (s[i] == '*')
                {
                    if (s[i + 1] == '*')
                    {
                        ans += 15 * f2(s, i + 2);
                    }
                    else if (s[i + 1] >= '0' && s[i + 1] <= '6')
                    {
                        ans += 2 * f2(s, i + 2);
                    }
                    else if (s[i + 1] >= '7' && s[i + 1] <= '9')
                    {
                        ans += f2(s, i + 2);
                    }
                }
            }
        }
        ans %= MOD;
        dp[i] = ans;
        return ans;
    }
    //严格位置依赖的动态规划
    int numDecodings(string s) {
        memset(dp, -1, sizeof(dp));
        int n = s.size();
        dp[n] = 1;
        return f3(s, 0);
    }
    long long f3(string& s, int i)
    {
        int n = s.size();
        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] == '0')
            {
                dp[i] = 0;
            }
            else {
                //使用一位
                if (s[i] == '*')
                {
                    dp[i] = (9 % MOD * dp[i + 1] % MOD) % MOD;
                }
                else dp[i] = dp[i + 1];
                dp[i] %= MOD;
                //使用两位
                if (i + 1 < s.size())
                {
                    if (s[i] == '1')
                    {
                        if (s[i + 1] >= '0' && s[i + 1] <= '9')
                        {
                            dp[i] += dp[i + 2];
                        }
                        else if (s[i + 1] == '*')
                        {
                            dp[i] += 9 * dp[i + 2];
                        }
                    }
                    else if (s[i] == '2')
                    {
                        if (s[i + 1] >= '0' && s[i + 1] <= '6')
                        {
                            dp[i] += dp[i + 2];
                        }
                        else if (s[i + 1] == '*')
                        {
                            dp[i] += 6 * dp[i + 2];
                        }
                    }
                    else if (s[i] == '*')
                    {
                        if (s[i + 1] == '*')
                        {
                            dp[i] += 15 * dp[i + 2];
                        }
                        else if (s[i + 1] >= '0' && s[i + 1] <= '6')
                        {
                            dp[i] += 2 * dp[i + 2];
                        }
                        else if (s[i + 1] >= '7' && s[i + 1] <= '9')
                        {
                            dp[i] += dp[i+2];
                        }
                    }
                }
            }
            dp[i] %= MOD;
        }
        return dp[0];
    }
};