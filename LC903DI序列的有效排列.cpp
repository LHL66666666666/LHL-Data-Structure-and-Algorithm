#include <vector>
#include <string>
using namespace std;
typedef long long ll;
class Solution {
public:
    int n;
    const int MOD = 1e9 + 7;
    vector<vector<ll>> dp;
    //表示来到i位置的数字，这表明已经使用了i个数字(0到i-1)
    //比前一个数字小的还有less个，可以推出比前一个数字大的还有n+1-i-less个
    //i位置对应的大小关系要求是s[i-1]
    ll dfs(int i, int less, string& s)
    {
        if (i == n)
        {
            //最后一个数字，没得选了
            if (s[n - 1] == 'D')
            {
                if (less == 1) return 1;
                else return 0;
            }
            else {
                if (1 - less == 1) return 1;
                else return 0;
            }
        }
        if (dp[i][less] != -1) return dp[i][less];
        //枚举
        ll ans = 0;
        if (s[i - 1] == 'D')
        {
            //i位置要从less里面选择
            for (int j = 0; j <= less - 1; j++)
            {
                ans = (ans + dfs(i + 1, j, s)) % MOD;
            }
        }
        else {
            //i位置要从n+1-i-less里面选择
            for (int j = less; j <= n - i; j++)
            {
                ans = (ans + dfs(i + 1, j, s)) % MOD;
            }
        }
        dp[i][less] = ans;
        return ans;
    }
    int numPermsDISequence(string s) {
        n = s.size();
        if (n == 1) return 1;
        //最原初的想法：好想但是时间复杂度爆炸
        //dfs(i,p,status)表示来到第i个位置，前一个数字为p，已经使用过的数字的状态储存在status中
        //dfs(i,p,status)表示当前状态下的总方案数
        //实际上，我们并不需要知道每个位置的数字到底是多少，只需要知道相邻数字之间的大小关系即可
        //因此在设计状态时，我们来到当前位置，因为D,I只对前一个数字有要求，
        //因此我们需要知道在没使用过的数字中，比前一个数字小的还有几个，比前一个数字大的还有几个
        //然后枚举各种可能性
        dp.assign(n + 1, vector<ll>(n + 1, -1));
        ll ans = 0;
        //不管新数字的数值大小，只关心数字之间的大小关系
        for (int i = 0; i <= n; i++)
        {
            ans = (ans + dfs(1, i, s)) % MOD;
        }
        return ans;
    }
};

//dp版本，方便观察和优化枚举
class Solution {
public:
    int n;
    const int MOD = 1e9 + 7;
    vector<vector<ll>> dp;
    int numPermsDISequence(string s) {
        n = s.size();
        dp.assign(n + 1, vector<ll>(n + 1, 0));
        //base case
        if (s[n - 1] == 'D')
        {
            dp[n][1] = 1;
        }
        else {
            dp[n][0] = 1;
        }
        //递推
        for (int i = n - 1; i >= 1; i--)
        {
            for (int j = 0; j <= n; j++)
            {
                if (s[i - 1] == 'D')
                {
                    for (int k = 0; k <= j - 1; k++)
                    {
                        dp[i][j] = (dp[i][j] + dp[i + 1][k]) % MOD;
                    }
                }
                else {
                    for (int k = j; k <= n - i; k++)
                    {
                        dp[i][j] = (dp[i][j] + dp[i + 1][k]) % MOD;
                    }
                }
            }
        }
        ll ans = 0;
        for (int i = 0; i <= n; i++)
        {
            ans = (ans + dp[1][i]) % MOD;
        }
        return ans;
    }
};

//优化枚举：我们不难发现第三层循环可以使用前缀和优化
class Solution {
public:
    int n;
    const int MOD = 1e9 + 7;
    vector<vector<ll>> dp;
    int numPermsDISequence(string s) {
        n = s.size();
        dp.assign(n + 1, vector<ll>(n + 1, 0));
        //base case
        if (s[n - 1] == 'D')
        {
            dp[n][1] = 1;
        }
        else {
            dp[n][0] = 1;
        }
        //递推
        for (int i = n - 1; i >= 1; i--)
        {
            //前缀和数组
            vector<ll> pre(n+1);
            pre[0] = dp[i + 1][0];
            for (int j = 1; j <= n; j++)
            {
                pre[j] = (pre[j - 1] + dp[i + 1][j]) % MOD;
            }
            //前缀和构建完成之后我们直接查询即可
            for (int j = 0; j <= n; j++)
            {
                if (s[i - 1] == 'D')
                {
                    if (j == 0) dp[i][j] = 0;
                    else {
                        dp[i][j] = pre[j - 1] % MOD;
                    }
                }
                else {
                    if (j == 0) dp[i][j] = pre[n - i] % MOD;
                    else {
                        dp[i][j] = ((pre[n - i] - pre[j - 1]) % MOD + MOD) % MOD;
                    }
                }
            }
        }
        ll ans = 0;
        for (int i = 0; i <= n; i++)
        {
            ans = (ans + dp[1][i]) % MOD;
        }
        return ans;
    }
};