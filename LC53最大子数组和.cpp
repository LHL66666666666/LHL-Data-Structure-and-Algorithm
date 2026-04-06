/*
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），
返回其最大和。
子数组是数组中的一个连续部分。
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int dp[100005];
    const int INF = 0x3f3f3f3f;
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        memset(dp, 0, sizeof(dp));
        //状态定义：dp[i]表示以i位置结尾的最大累加和
        //对于每个位置i，选择或不选择前面的dp[i-1]
        //如果加上前面的能让自己变得更大，那就加上，如果加上不如自己单独大，那就选自己单独
        //也就是说dp[i]=max(nums[i],nums[i]+dp[i-1])
        int ans = -INF;
        dp[0] = nums[0];
        ans = max(ans, dp[0]);
        for (int i = 1; i < n; i++)
        {
            dp[i] = max(nums[i], nums[i] + dp[i - 1]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
    //附加问题：求出最大累加和的子数组的同时，返回下面三个信息：
    //最大累加和子数组开头left
    //最大累加和子数组结尾right
    //最大累加和子数组的累加和sum
    //如果不止一个子数组有最大累加和，返回任意一个即可
    int ans, left, right;
    void extra(vector<int>& nums)
    {
        //dp时同时维护左右端点即可
        int n = nums.size();
        //memset(dp, 0, sizeof(dp));
        int l = 0, r = 0, pre = -INF;
        ans = -INF;
        for (; r < n; r++)
        {
            if (pre >= 0)
            {
                //要前面的
                pre += nums[r];
            }
            else {
                //不要前面的
                pre = nums[r];
                l = r;
            }
            if (pre > ans)
            {
                ans = pre;
                left = l;
                right = r;
            }
        }

    }
};