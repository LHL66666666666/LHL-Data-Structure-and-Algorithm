#include <vector>
using namespace std;
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        //最多进行k次交易
        //显然要寻找上升段，但是不能简单的使用贪心
        //我们考虑dp[j][i]表示来到i位置，已经完成j次交易的最大收入
        //状态转移方程:dp[j][i] = max(dp[j][i-1] , max(dp[j-1][x] - prices[x]) + prices[i] )
        //分类：
        //1.第j次交易一定在i位置卖出,为 max(dp[j-1][x] - prices[x]) + prices[i]
        //2.第j次交易不在i位置卖出，为dp[j][i-1]
        //二者取最大值
        vector<vector<int>> dp(k + 1, vector<int>(n + 1));
        //base case : dp[j][0]都是0
        //为了方便位置依赖是行的关系，我们调换了两维的位置
        for (int j = 1; j <= k; j++)
        {
            int pre = dp[j - 1][0] - prices[0];
            for (int i = 1; i < n; i++)
            {
                dp[j][i] = max(dp[j][i - 1], pre + prices[i]);
                pre = max(pre, dp[j - 1][i] - prices[i]);
            }
        }
        return dp[k][n - 1];
    }
};