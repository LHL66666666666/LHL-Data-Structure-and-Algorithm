#include <vector>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        //计算前缀最小值，后缀最大值
        //如果是两次交易，枚举分割点
        //这和那个背包中每种物品要或不要很像
        //前缀跑一遍dp,后缀跑一遍dp
        vector<int> dp(n + 1);
        vector<int> dp2(n + 1);
        //前缀dp
        dp[0] = 0;
        int pre = prices[0];
        for (int i = 1; i < n; i++)
        {
            dp[i] = max(dp[i - 1], prices[i] - pre);
            pre = min(pre, prices[i]);
        }
        //后缀dp
        dp2[n-1] = 0;
        int suf = prices[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            dp2[i] = max(dp2[i + 1], suf - prices[i]);
            suf = max(suf, prices[i]);
        }
        //枚举分割点
        int ans = dp[n - 1];
        for (int i = 0; i < n-1; i++)
        {
            ans = max(ans, dp[i] + dp2[i + 1]);
        }
        return ans;
    }
};
//另一种定义的方式：
//dp[i]表示来到i位置，进行一次操作的最大利润
//dp2[i]表示来到i位置，已经进行了2次操作且在i位置卖出第二支股票的的最大利润
//状态转移：我们枚举第二次买入股票的时间x
// max(dp[x]-prices[x]) +prices[i]即为答案，但是我们不能枚举x
//考虑预处理出数组a[i]=dp[i]-prices[i]的前缀最大值
//即可做到O(n)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> dp(n + 1);
        vector<int> dp2(n + 1);
        dp[0] = 0;
        int pre = prices[0];
        for (int i = 1; i < n; i++)
        {
            dp[i] = max(dp[i - 1], prices[i] - pre);
            pre = min(pre, prices[i]);
        }
        vector<int> a(n + 1);
        a[0] = dp[0] - prices[0];
        for (int i = 1; i < n; i++)
        {
            a[i] = max(a[i - 1], dp[i] - prices[i]);
        }
        dp2[0] = 0;
        for (int i = 1; i < n; i++)
        {
            dp2[i] = max(dp2[i - 1], a[i] + prices[i]);
        }
        return dp2[n - 1];

    }
};