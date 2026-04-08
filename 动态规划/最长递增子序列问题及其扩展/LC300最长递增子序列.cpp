/*
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int dp[200005];
    int lengthOfLIS(vector<int>& nums) {
        //O(n^2)暴力解
        //状态定义：dp[i]表示以i位置结尾的最长递增子序列的长度
        int n = nums.size();
        if (n == 1) return 1;
        dp[0] = 1;
        int ans = 1;
        for (int i = 1; i < n; i++)
        {
            dp[i] = 1;
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
//优化:O(nlogn)的解
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;
        //ends数组表示，
        //在ends数组中下标为i位置，表示i+1长度的子序列结尾的最小数字
        vector<int> ends;
        ends.emplace_back(nums[0]);
        for (int i = 1; i < n; i++)
        {
            //遍历到每个数字，二分查找ends中大于等于这个数字的第一个数
            //如果不存在，那么扩充ends数组，
            //如果存在，将这个位置的数改为nums[i]，因为nums[i]更小
            auto it = lower_bound(ends.begin(), ends.end(), nums[i]);
            if (it == ends.end())
            {
                ends.emplace_back(nums[i]);
            }
            else {
                int id = it - ends.begin();
                ends[id] = nums[i];
            }
        }
        return ends.size();
    }
};
//核心思想：去除无用数据：类似单调栈，单调队列的思想
//对应相同长度子序列的结尾的数值，
//较大的数字和较小的数字，二者的效果是一样的，
//所以较大的那个数字是个无用数据
//换句话说，对于相同的 f 值，我们只需保留更小的 nums[i]
//dp中优化时间复杂度的技巧：
//交换状态与状态值：
//对于这个问题，本来dp[i]表示以i位置为结尾元素的LIS长度
//交换：ends[i]表示长度为i+1的子序列的结尾元素的最小值


//扩展：最长不下降子序列问题，也就是不要求严格递增，出现相同数字也可以
//很简单，只需变为二分查找ends中严格大于这个数字的第一个数
//也就是upper_bound
int lengthOfLIS2(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return 1;
    //ends数组表示，
    //在ends数组中下标为i位置，表示i+1长度的子序列结尾的最小数字
    vector<int> ends;
    ends.emplace_back(nums[0]);
    for (int i = 1; i < n; i++)
    {
        //遍历到每个数字，二分查找ends中严格大于这个数字的第一个数
        //如果不存在，那么扩充ends数组，
        //如果存在，将这个位置的数改为nums[i]，因为nums[i]更小
        auto it = upper_bound(ends.begin(), ends.end(), nums[i]);
        if (it == ends.end())
        {
            ends.emplace_back(nums[i]);
        }
        else {
            int id = it - ends.begin();
            ends[id] = nums[i];
        }
    }
    return ends.size();
}