#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
int base[] = { 2,3,5,7,11,13,17,19,23,29 };
int own[] = {
    0b0000000000,   //0
    0b0000000000,   //1
    0b0000000001,   //2
    0b0000000010,   //3
    0b0000000000,   //4
    0b0000000100,   //5
    0b0000000011,   //6
    0b0000001000,   //7
    0b0000000000,   //8
    0b0000000000,   //9
    0b0000000101,   //10
    0b0000010000,   //11
    0b0000000000,   //12
    0b0000100000,   //13
    0b0000001001,   //14
    0b0000000110,   //15
    0b0000000000,   //16
    0b0001000000,   //17
    0b0000000000,   //18
    0b0010000000,   //19
    0b0000000000,   //20
    0b0000001010,   //21
    0b0000010001,   //22
    0b0100000000,   //23
    0b0000000000,   //24
    0b0000000000,   //25
    0b0000100001,   //26
    0b0000000000,   //27
    0b0000000000,   //28
    0b1000000000,   //29
    0b0000000111,   //30
};
ll qpow(int n)
{
    ll a = 2;
    ll ans = 1;
    while (n)
    {
        if (n & 1)
        {
            ans *= a;
            ans %= MOD;
        }
        a *= a;
        a %= MOD;
        n = n >> 1;
    }
    return ans;
}
class Solution {
public:
    vector<int> cnt;
    //dp[i][s]表示当前来到数字i，要达成的状态为s的方案总数
    vector<vector<ll>> dp;
    ll dfs(int i, int s)
    {
        if (dp[i][s] != -1) return dp[i][s];
        //base case
        //当来到1的时候，没得选了
        ll ans = 0;
        if (i == 1)
        {
            if (s == 0)
            {
                //如果满足了所有状态
                ans = qpow(cnt[1]);
            }
        }
        else {
            //根据我们预处理出来的表，来进行枚举
            //选择1：不要位置i的数字
            ans = dfs(i - 1, s) % MOD;
            //选择2：要i位置的数字
            //检查是否满足要求：要有状态s需要的质因数及个数，还要个数大于0
            int cur = own[i];
            int t = cnt[i];
            if (cur != 0 && t > 0 && (s & cur) == cur)
            {
                ans = (ans + dfs(i - 1, s ^ cur) * t % MOD) % MOD;
            }
        }
        dp[i][s] = ans;
        return ans;
    }
    int numberOfGoodSubsets(vector<int>& nums) {
        int n = nums.size();
        //10以内的质数一共10个，最多2^10-1个不同的数字(满足要求的乘积)
        //能否跟据因数来分类
        //也就是说，我们处理出来的10个因数
        //1很特殊，1不能单独拿出来，假设一共x个1，最后方案数量还要乘(1<<x)
        cnt.assign(31, 0);
        for (int i = 0; i < n; i++)
        {
            //我们统计每个数字出现的次数即可
            cnt[nums[i]]++;
        }
        //在数组cnt中找方案数即可
        int n1 = cnt.size();
        //一共10个质数，状态有2^10个
        int s0 = (1 << 10);
        dp.assign(31, vector<ll>(s0, -1));
        ll ans = 0;
        for (int s = 1; s < s0; s++)
        {
            //s表示状态，每一个状态都要尝试一边
            ans = (ans + dfs(30, s)) % MOD;
        }
        return ans;
    }
};