#include <vector>
using namespace std;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    vector<vector<int>> dp;
    //dp[i][0],第i天结束时，未持股且不处于冷冻期
    //dp[i][1],第i天结束时，持股
    //dp[i][2],第i天结束时，未持股且处于冷冻期
    int dfs(int i,int f,vector<int>& a)
    {
        if (i < 0)
        {
            if (f == 0) return 0;
            else return -INF;
        }
        if (dp[i][f] != 2 * INF)
        {
            return dp[i][f];
        }
        int ans = 0;
        if (f == 0)
        {
            //注意：如果是0状态，不能今天卖出，因为如果今天卖出，今天也是冷冻期
            ans = max(dfs(i - 1, 0, a), dfs(i - 1, 2, a));
        }
        if (f == 1)
        {
            ans = max(dfs(i - 1, 1, a), dfs(i - 1, 0, a) - a[i]);
        }
        if (f == 2)
        {
            //代表第i-1天一定持股
            ans = dfs(i - 1, 1, a) + a[i];
    
        }
        dp[i][f] = ans;
        return ans;
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 1) return 0;
        //状态：持股状态，不持股状态，冷冻期状态
        dp.assign(n + 1, vector<int>(3, 2*INF));
        return max(dfs(n - 1, 0, prices), dfs(n - 1, 2, prices));
    }
};

//另一写法
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    vector<vector<int>> dp;
    int dfs(int i, int f, vector<int>& a)
    {
        if (i < 0)
        {
            if (f == 0) return 0;
            else return -INF;
        }
        if (dp[i][f] != -INF * 2) return dp[i][f];
        int ans = 0;
        if (f == 0)
        {
            ans = max(dfs(i - 1, 1, a) + a[i], dfs(i - 1, 0, a));
        }
        else {
            //前一天不能卖出，因此直接从i-2天转移而来
            ans = max(dfs(i - 1, 1, a), dfs(i - 2, 0, a) - a[i]);
        }
        dp[i][f] = ans;
        return ans;
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        dp.assign(n + 1, vector<int>(2, -INF * 2));
        return dfs(n - 1, 0, prices);
    }
};
