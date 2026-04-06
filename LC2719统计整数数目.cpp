#include <vector>
#include <string>
using namespace std;
using ll = long long;
/*
把问题拆分成：计算 ≤num2 的好整数个数，记作 a。
计算 ≤num1−1 的好整数个数，记作 b。
那么答案就是 a−b
考虑到 num1是个字符串，不方便减一，可以改为计算 ≤num 1
的合法数字个数，再单独判断 num1这个数是否合法
*/
int dp[25][410][2][2];
class Solution {
public:
    //每次只判断1个字符串
    int l, r;
    const int MOD = 1e9 + 7;
    ll dfs(string& s, int id, int sum, int islim, int isnum)
    {
        if (id == s.size())
        {
            return (isnum && sum >= l && sum <= r);
        }
        if (sum > r) return 0;
        if (dp[id][sum][islim][isnum] != -1) return dp[id][sum][islim][isnum];
        ll ans = 0;
        //如果之前还没选过数字，这一位也可以不选
        if (isnum == 0)
        {
            ans += dfs(s, id + 1, sum, 0, 0);
        }
        //如果这一位要选
        //如果被限制
        if (islim)
        {
            //如果被限制，看前面是否选过，决定首位能否选0
            if (isnum)
            {
                for (int i = 0; i < 10; i++)
                {
                    if ('0' + i == s[id])
                    {
                        ans += dfs(s, id + 1, sum + i, 1, 1);
                    }
                    if ('0' + i < s[id])
                    {
                        ans += dfs(s, id + 1, sum + i, 0, 1);
                    }
                    
                }
            }
            else {
                for (int i = 1; i < 10; i++)
                {
                    if ('0' + i == s[id])
                    {
                        ans += dfs(s, id + 1, sum + i, 1, 1);
                    }
                    if ('0' + i < s[id])
                    {
                        ans += dfs(s, id + 1, sum + i, 0, 1);
                    }
                }
            }
        }
        //不被限制
        else {
            //看前面是否选过数字
            if (isnum)
            {
                for (int i = 0; i < 10; i++)
                {
                    ans += dfs(s, id + 1, sum + i, 0, 1);
                }
            }
            else {
                for (int i = 1; i < 10; i++)
                {
                    ans += dfs(s, id + 1, sum + i, 0, 1);
                }
            }
        }
        ans %= MOD;
        dp[id][sum][islim][isnum] = ans;
        return ans;
    }
    int count(string num1, string num2, int min_sum, int max_sum) {
        l = min_sum, r = max_sum;
        for (int i = 0; i <= 23; i++)
        {
            for (int j = 0; j < 410; j++)
            {
                for (int k = 0; k < 2; k++) {
                    dp[i][j][k][0] = -1;
                    dp[i][j][k][1] = -1;
                }
            }
        }
        ll ans1 = dfs(num1, 0, 0, 1, 0);
        for (int i = 0; i <= 23; i++)
        {
            for (int j = 0; j < 410; j++)
            {
                for (int k = 0; k < 2; k++) {
                    dp[i][j][k][0] = -1;
                    dp[i][j][k][1] = -1;
                }
            }
        }
        ll ans2 = dfs(num2, 0, 0, 1, 0);
        //特判num1
        int sum = 0;
        for (int i = 0; i < num1.size(); i++) sum += num1[i] - '0';
        if (sum >= l && sum <= r) return (ans2 - ans1 + 1 + MOD) % MOD;
        else return (ans2 - ans1 + MOD) % MOD;
    }
};