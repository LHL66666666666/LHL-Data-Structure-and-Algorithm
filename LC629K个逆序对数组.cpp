#include <vector>
using namespace std;
typedef long long ll;
class Solution {
public:
    const int MOD = 1e9 + 7;
    int kInversePairs(int n, int k) {
        //逆序对最少0个，最多n*(n-1)/2个
        //定义dp[i][j]表示[1...i]这些数字，形成j个逆序对的个数
        //我们从插入新元素的角度来推转移方程
        //假设目前来到数字i，前面形成了i-1个数字的某种排列
        //因为i比前面i-1个数字都要大，因此我们考虑i插入原排列的位置
        //假设原排列为p[1],p[2],p[3]..p[i-2],p[i-1]
        //p[1],p[2],p[3]..p[i-2],p[i-1],p[i]这样插入新形成0对逆序对
        //p[1],p[2],p[3]..p[i-2],p[i],p[i-1]这样插入新形成1对逆序对
        //以此类推
        //p[i],p[1],p[2],p[3]..p[i-2],p[i-1]这样插入新形成i-1对逆序对
        //也就是说，可以新形成0到(i-1)个新的逆序对
        //因此得出转移方程
        vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, 0));
        //base case dp[1][0]是1,dp[1][j](j>0)均为0
        dp[1][0] = 1;
        for (int i = 2; i <= n; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                //根据分析，i位置的数字插入时，能形成0到i-1个新逆序对
                int l = max(0, j - i + 1), r = j;
                for (int k = l; k <= r; k++)
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
                }
            }
        }
        return dp[n][k];
    }
};
//前缀和优化即可
class Solution {
public:
    const int MOD = 1e9 + 7;
    int kInversePairs(int n, int k) {
        vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, 0));
        dp[1][0] = 1;
        for (int i = 2; i <= n; i++)
        {
            //前缀和
            vector<ll> pre(k + 1);
            pre[0] = dp[i - 1][0];
            for (int m = 1; m <= k; m++)
            {
                pre[m] = (pre[m - 1] + dp[i - 1][m]) % MOD;
            }
            for (int j = 0; j <= k; j++)
            {
                int l = max(0, j - i + 1), r = j;
                if (l == 0)
                {
                    dp[i][j] = pre[r] % MOD;
                }
                else {
                    dp[i][j] = ((pre[r] - pre[l - 1]) % MOD + MOD) % MOD;
                }
            }
        }
        return dp[n][k];
    }
};