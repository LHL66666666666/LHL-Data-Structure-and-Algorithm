#include <vector>
using namespace std;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    //最大乘积子数组
    long long dp1[20005];
    //最小乘积子数组
    long long dp2[20005];
    int maxProduct(vector<int>& nums) {
        //状态定义：dp1[i]表示以i结尾的乘积最大的子数组
        //状态定义：dp2[i]表示以i结尾的乘积最小的子数组
        //说是最小，其实也是在找绝对值尽量大的
        //来到每一个下标i，考虑如果nums[i]是负数，希望找一个尽量小的负数
        //也就是绝对值大的负数，负负得正，可能得到更大的乘积
        //因此我们需要维护乘积最大子数组和乘积最小子数组
        //每次更新这两个数组时，候选值：nums[i],nums[i]*dp1[i-1],nums[i]*dp2[i-1]
        //找到最小值和最大值填入即可
        int n = nums.size();
        if (n == 1) return nums[0];
        dp1[0] = nums[0], dp2[0] = nums[0];
        long long ans = nums[0];
        for (int i = 1; i <= n - 1; i++)
        {
            dp1[i] = max((long long)nums[i], max(dp1[i - 1] * nums[i], dp2[i - 1] * nums[i]));
            dp2[i] = min((long long)nums[i], min(dp1[i - 1] * nums[i], dp2[i - 1] * nums[i]));
            ans = max(ans, dp1[i]);
        }
        return ans;
    }
};