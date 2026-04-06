/*
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int dp[405];
    const int INF = 0x3f3f3f3f;
    int rob1(vector<int>& nums) {
        //不能选择相邻的元素
        //状态定义：dp[i]表示以位置i结尾的最大累加和(选择i位置的数)
        //我们发现，连续的三个元素，如果都不取，一定不是最优的
        int n = nums.size();
        dp[0] = nums[0];
        if (n == 1) return dp[0];
        dp[1] = nums[1];
        if (n == 2) return max(dp[0], dp[1]);
        dp[2] = dp[0] + nums[2];
        if (n == 3) return max(dp[1], dp[2]);
        for (int i = 3; i < n; i++)
        {
            dp[i] = max(nums[i] + dp[i - 2], nums[i] + dp[i - 3]);
        }
        int ans = -INF;
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, dp[i]);
        }
        return ans;
    }
    //另一种状态定义：dp[i]表示范围[0...i]上能取得的最大累加和
    //当然要求满足不选相邻的数字
    //状态转移：来到i位置时，我们考虑要不要选i位置的数字
    //如果选，那么不能选i-1位置的数字，答案即为dp[i-2]+nums[i]
    //如果不选，那么答案即为dp[i-1]
    int rob(vector<int>& nums) {
        int n = nums.size();
        memset(dp, 0, sizeof(dp));
        dp[0] = nums[0];
        if (n == 1) return dp[0];
        dp[1] = max(nums[0], nums[1]);
        if (n == 2) return max(dp[0], dp[1]);
        for (int i = 2; i < n; i++)
        {
            dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);
        }
        return dp[n - 1];
    }
};