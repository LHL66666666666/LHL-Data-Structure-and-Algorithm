#include <vector>
using namespace std;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    //第一次的尝试：失败
    //将环拆成链，链重复两遍即可覆盖所有情况
    //还要维护左端点,子数组的长度最长为n
    //错误原因：在子数组长度超过n的时候，无法判断由于要维护长度不超过n而需要在开头删去哪些元素
    //正难则反
    //正确思路：我们不拆环为链，就是讨论两种情况
    //情况1：子数组不跨越边界：这就是经典子数组最大累加和
    //情况2：子数组跨越边界：那么这个子数组一定是：开头连续一段+结尾连续一段组成的
    //这样一段的结构相当于本来的整个数组删掉一个子数组
    //对于情况2，我们计算出数组所有元素之和sum，然后再计算出不跨越边界的子数组最小累加和
    //sum减去最小累加和即为答案
    //两种情况选优即可
    int dp1[100005];
    int dp2[100005];
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        //子数组最大累加和
        dp1[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            dp1[i] = max(nums[i], nums[i] + dp1[i - 1]);
        }
        //子数组最小累加和
        dp2[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            dp2[i] = min(nums[i], nums[i] + dp2[i - 1]);
        }
        int sum = 0;
        int maxsum = -INF, minsum = INF;
        int ext = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] >= 0) ext = 1;
            sum += nums[i];
            maxsum = max(maxsum, dp1[i]);
            minsum = min(minsum, dp2[i]);
        }
        //特别需要注意的是，本题要求子数组不能为空，我们需要在代码中做出相应的调整
        //如果全是负数，我们计算出来的最小累加和是把数组中所有数字全加起来的
        //这样减去之后会出现空数组，不满足题意，特判即可
        if (ext) return max(maxsum, sum - minsum);
        else return maxsum;
    }
    //实际上还有另一种解法
    int maxSubarraySumCircular2(vector<int>& nums) {
        //处理跨区见的子数组时我们换一种思路考虑
        //先求出前缀和，再求前缀和的前缀最大数组(类似单调队列)
        //枚举右边那一段的边界，通过前缀最大数组找到左边半段的前缀和最大值
        //(由于左边半段和右边半段都是连续的，所以这样可行)
    }
};