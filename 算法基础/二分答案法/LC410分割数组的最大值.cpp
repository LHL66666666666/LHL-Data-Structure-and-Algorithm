/*
给定一个非负整数数组 nums 和一个整数 k ，你需要将这个数组分成 k 个非空的连续子数组，使得这 k 个子数组各自和的最大值 最小。

返回分割后最小的和的最大值。

子数组 是数组中连续的部份。
*/
//https://leetcode.cn/problems/split-array-largest-sum/description/
class Solution {
public:
    int check(vector<int>& nums, int s)
    {
        int cnt = 1, n = nums.size();
        //cnt=1，至少有一段
        long long sum = 0;
        for (int i = 0; i < n; i++)
        {
            //使用了贪心
            if (nums[i] > s)
            {
                return 51;
            }
            else if (sum + nums[i] > s)
            {
                sum = nums[i];
                cnt++;
            }
            else sum += nums[i];
        }
        return cnt ;
    }
    int splitArray(vector<int>& nums, int k) {
        //先粗略估计答案的范围
        //首先最大值不可能超过所有数之和
        //最大值不可能小于数组中最大元素，因为最大值被划分为1个的时候，就是这个最大值
        //范围是[max,sum]
        //另一种思路也可：
        //先计算一个平均值sum/k
        //容易发现要求的最大值大于等于这个平均值
        //小于数组中所有元素之和
        //范围是[average,sum]
        //范围确定了，如何二分？
        //用一个函数实现判断，如果要使得这个数组中任意划分的区间和全都不大于答案，
        //需要怎样的x？如果x小于给定的目标k，那么就增大答案，判断
        //如果x大于目标k，缩小答案
        //增大和缩小答案用二分查找完成
        int sum = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
        }
        int avg = sum / k;
        //[avg,sum]区间确定
        //找单调性
        //单调性：最大累加和 和 划分数 之间的单调性
        //函数实现完成，开始二分
        int l = avg, r = sum, ans = sum;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (check(nums, mid) <= k)
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return ans;
    }
};