#include <vector>
using namespace std;
class Solution {
public:
    int d[3] = { 1,7,30 };
    int mincostTickets1(vector<int>& days, vector<int>& costs) {
        //第一种尝试：暴力递归展开，一定超时，计算了太多重复状态
        return f1(0, days, costs);
    }
    int f1(int i, vector<int>& days, vector<int>& costs)
    {
        //base case
        if (i == days.size())
        {
            return 0;
        }
        //每次尝试3个方案全展开
        int tmp = i;
        int ans = INT_MAX;
        for (int j = 0; j < 3; j++)
        {
            while (i<days.size() && d[j] + days[tmp] - 1 >= days[i])
            {
                ++i;
            }
            ans = min(ans, costs[j] + f1(i, days, costs));
        }
        return ans;
    }
    int dp[400];
    int mincostTickets2(vector<int>& days, vector<int>& costs) {
        //第二种尝试，记忆化搜索
        memset(dp, 0, sizeof(dp));
        return f2(0, days, costs);
    }
    int f2(int i, vector<int>& days, vector<int>& costs)
    {
        if (i == days.size())
        {
            return 0;
        }
        //如果之前计算过，那么返回计算过的数值
        if (dp[i] != 0)
        {
            return dp[i];
        }
        //如果没计算过则展开
        int tmp = i;
        int ans = INT_MAX;
        for (int j = 0; j < 3; j++)
        {
            while (tmp < days.size() && d[j] + days[i] - 1 >= days[tmp])
            {
                ++tmp;
            }
            ans = min(ans, costs[j] + f2(tmp, days, costs));
        }
        dp[i] = ans;
        return ans;
    }
    //动态规划
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        //每个值依赖于它后面的值得出答案，所以先算后面的值，再逐渐更新前面的值
        memset(dp, 0, sizeof(dp));
        int n = days.size();
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            //枚举三种策略
            int tmp = i;
            int ans = INT_MAX;
            for (int j = 0; j < 3; j++)
            {
                while (tmp < days.size() && d[j] + days[i] - 1 >= days[tmp])
                {
                    ++tmp;
                }
                ans = min(ans, costs[j] + dp[tmp]);
            }
            dp[i] = ans;
        }
        return dp[0];
    }
};