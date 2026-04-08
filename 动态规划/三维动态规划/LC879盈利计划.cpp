#include <vector>
#include <string>
using namespace std; 
class Solution {
public:
    const int MOD = 1e9 + 7;
    //dp数组存储的状态：来到i号工作，剩余员工还有r人，剩余达标金额还有s
    //数值表示方案数量
    long long dp[105][105][105];
    int profitableSchemes1(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        memset(dp, -1, sizeof(dp));
        return f2(group, profit, n, 0, minProfit);
    }
    long long f2(vector<int>& g, vector<int>& p, int r, int id, int s)
    {
        //对于要求方案数的，我们在末尾位置结算，算作一种方案
        int n1 = p.size();
        if (id == n1)
        {
            if (s <= 0)
            {
                return 1;
            }
            else return 0;
        }
        if (dp[id][r][s] != -1) return dp[id][r][s];
        //枚举每一种工作要不要做
        long long p1 = 0, p2 = 0;
        //不选择
        p1 = f2(g, p, r, id + 1, s);
        //选择
        if (r >= g[id])
        {
            if (s - p[id] <= 0)
            {
                p2 = f2(g, p, r - g[id], id + 1, 0);
            }
            else p2 = f2(g, p, r - g[id], id + 1, s - p[id]);
        }
        //方案数是要相加的
        dp[id][r][s] = (p1 + p2) % MOD;
        return dp[id][r][s];
    }
    //dp
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        return f3(group, profit, n, minProfit);
    }
    long long f3(vector<int>& g, vector<int>& p, int r, int s)
    {
        int n = g.size();
        //先填最上面一层，跟据base case
        //只要距离达标差的钱数为0，方案都有效，其余的都无效
        for (int i = 0; i <= r; i++)
        {
            dp[n][i][0] = 1;
        }
        //逐层填写
        for (int k = n - 1; k >= 0; k--)
        {
            for (int i = 0; i <= r; i++)
            {
                for (int j = 0; j <= s; j++)
                {
                    long long p1 = dp[k + 1][i][j], p2 = 0;
                    if (i - g[k] >= 0)
                    {
                        if (j - p[k] <= 0)
                        {
                            p2 = dp[k + 1][i - g[k]][0];
                        }
                        else p2 = dp[k + 1][i - g[k]][j - p[k]];
                    }
                    dp[k][i][j] = (p1 + p2) % MOD;
                }
            }
        }
        return dp[0][r][s];
    }
};