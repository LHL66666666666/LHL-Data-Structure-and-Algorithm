#include <vector>
using namespace std;
class Solution {
public:
    int dp1[105];
    int dp2[105];
    int rob(vector<int>& nums) {
        int n = nums.size();
        //不能取相邻元素的环形数组子数组累加和
        //实际上是对首尾元素多加了限制，不能同时取首尾元素
        //可能性分类：选or不选nums[0]
        //如果不选nums[0],那么[1...n-1]位置的元素可以任意选择，我们找到一个最大值
        //如果选nums[0],那么不能选nums[1]和nums[n-1],问题变成了[2...n-2]位置上的任取找最大值
        //这两种方案覆盖了所有情况（毕竟 nums[0] 只有偷与不偷，没有第三种选择），
        //所以取两种方案的最大值，即为答案
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        if (n == 3) return max(nums[0], max(nums[1], nums[2]));
        //不选nums[0]
        dp1[1] = nums[1];
        int ans1 = dp1[1];
        for (int i = 2; i < n ; i++)
        {
            dp1[i] = max(nums[i] + dp1[i - 2], dp1[i - 1]);
            ans1 = max(ans1, dp1[i]);
        }
        //选择nums[0]，问题转化为[2,n-2]上的
        dp2[2] = nums[2];
        int ans2 = dp2[2];
        for (int i = 2; i <= n - 2; i++)
        {
            dp2[i] = max(dp2[i - 1], dp2[i - 2] + nums[i]);
            ans2 = max(ans2, dp2[i]);
        }
        return max(ans1, ans2 + nums[0]);
    }
};