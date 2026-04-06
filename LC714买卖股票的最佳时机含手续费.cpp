#include <vector>
using namespace std;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    vector<vector<int>> dp;
    int dfs(int i, int f, vector<int>& a, int fee)
    {
        if (i < 0)
        {
            if (f == 0) return 0;
            else return -INF;
        }
        if (dp[i][f] != -INF*2) return dp[i][f];
        int ans = 0;
        //因为最终手上一定是没有股票的，不然买了就是白白浪费钱
        //那么有买入就必定有卖出，在买入/卖出其一减去手续费就行。
        if (f == 0)
        {
            ans = max(dfs(i - 1, 1, a, fee) + a[i] - fee, dfs(i - 1, 0, a, fee));
        }
        else {
            ans = max(dfs(i - 1, 1, a, fee), dfs(i - 1, 0, a, fee) - a[i]);

        }
        dp[i][f] = ans;
        return ans;
    }
    int maxProfit(vector<int>& prices,int fee) {
        int n = prices.size();
        //状态机dp
        //我们考虑两个参数:时间(第i天)，当前是否持有股票
        //入手点：最后一天发生了什么：
        //最后一天可以什么也不做，可以卖出股票，可以买入股票
        //如果第i天对应状态为0(未持有股票)
        //两种情况：
        //在第i天卖出股票，由i-1天持股的状态转移而来
        //在第i天什么也不干，由i-1天不持股的状态转移而来
        //如果第i天对应状态为1(持有股票)
        //两种情况：
        //在第i天买入股票，由i-1天未持股的状态转移而来
        //在第i天什么也不干，由i-1天持股的状态转移而来
        dp.assign(n + 1, vector<int>(2, -INF*2));
        return dfs(n - 1, 0, prices, fee);
    }
};
