/*
给你一个整数数组 nums。
请你统计所有满足以下条件的 非空 子序列 对 (seq1, seq2) 的数量：
子序列 seq1 和 seq2 不相交，意味着 nums 中 不存在 同时出现在两个序列中的下标。
seq1 元素的 GCD 等于 seq2 元素的 GCD。
返回满足条件的子序列对的总数。
由于答案可能非常大，请返回其对 109 + 7 取余 的结果
*/
#include<vector>
using namespace std;
typedef long long ll;
constexpr ll MOD = 1e9 + 7;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
ll dp[205][205][205];
ll gcd(ll a, ll b)
{
    while (b)
    {
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}
class Solution {
public:
    int subsequencePairCount1(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= 200; j++)
            {
                for (int k = 0; k <= 200; k++)
                {
                    dp[i][j][k] = -1;
                }
            }
        }
        return f1(nums, 0, 0, 0);
    }
    ll f1(vector<int>& nums, int g1, int g2, int i) {
        int n = nums.size();
        if (i == n) {
            if (g1 != 0 && g2 != 0 && g1 == g2) return 1;
            else return 0;
        }
        if (dp[i][g1][g2] != -1) return dp[i][g1][g2];
        ll ans = 0;
        //不选
        ans += f1(nums, g1, g2, i + 1);
        ans %= MOD;
        //选进1
        int ng1 = gcd(nums[i], g1);
        ans += f1(nums, ng1, g2, i + 1);
        ans %= MOD;
        //选进2
        int ng2 = gcd(nums[i], g2);
        ans += f1(nums, g1, ng2, i + 1);
        ans %= MOD;
        dp[i][g1][g2] = ans;
        return ans;
    }
};
int subsequencePairCount2(vector<int>& nums) {
    int n = nums.size();
    //首先我们知道GCD的一个性质：数字的数量越多，GCD一定是不增的
    //维护两个子序列的gcd，来到每个位置讨论这个位置不选、选入子序列1、选入子序列2
    ll g1 = INF, g2 = INF;
    //我们不妨始终令seq1的gcd >= seq2的gcd
    //状态定义：dp[i][j][k]表示来到前i个数字,seq1的gcd为j，seq2的gcd为k
    //seq1元素的GCD等于seq2元素的GCD的数量
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(205, vector<ll>(205)));
    //转移方程：dp[i][j][k]=dp[i-1]
    //base case为j==k时，且j,k不为0时，数量为1
    for (int j = 1; j <= 200; j++)
    {
        dp[n][j][j] = 1;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 200; j >= 0; j--)
        {
            for (int k = 200; k >= 0; k--)
            {
                dp[i][j][k] = dp[i + 1][j][k] + dp[i + 1][gcd(nums[i], j)][k] + dp[i + 1][j][gcd(nums[i], k)];
                dp[i][j][k] %= MOD;
            }
        }
    }
    return dp[0][0][0];
}