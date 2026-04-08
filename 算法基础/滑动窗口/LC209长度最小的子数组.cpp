/*
给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其总和大于等于 target 的长度最小的 子数组 
[numsl, numsl+1, ..., numsr-1, numsr] ，
并返回其长度。如果不存在符合条件的子数组，返回 0 。
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int binS(vector<int>& nums,int tar, int l1, int r1)
    {
        int l = l1, r = r1;
        int ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (l1 != 0)
            {
                if (nums[mid] - nums[l1 - 1] >= tar)
                {
                    ans = mid;
                    r = mid - 1;
                }
                else l = mid + 1;
            }
            else {

                if (nums[mid] >= tar)
                {
                    ans = mid;
                    r = mid - 1;
                }
                else l = mid + 1;
            }
        }
        return ans;
    }
    int min(int a, int b)
    {
        return a < b ? a : b;
    }
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        for (int i = 1; i < n; i++)
        {
            nums[i] += nums[i - 1];
        }
        int ans = 1e6+5;
        int l = 0;
        int flag = 0;
        for (; l < n; l++)
        {
            int tmp = binS(nums, target, l, n - 1);
            if (tmp != -1)
            {
                flag = 1;
                ans = min(ans, tmp - l + 1);
            }
        }
        if (!flag)
        {
            return 0;
        }
        return ans;
    }
};

//滑动窗口相当于在维护一个队列。右指针的移动可以视作入队，左指针的移动可以视作出队
//滑动窗口，枚举右，维护左
class Solution {
public:
    int min(int a, int b)
    {
        return a < b ? a : b;
    }
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        long long sum = 0;
        int ans = 1e6 + 5;
        int l = 0, r = 0;
        int flag = 0;
        while (r < n) {
            // 扩展右边界
            sum += nums[r];
            r++;
            // 当满足条件时，收缩左边界
            while (sum >= target) {
                // 先记录当前满足条件的最小长度
                ans = min(ans, r - l);
                flag = 1;

                // 然后移动左指针
                sum -= nums[l];
                l++;
            }
        }
        //枚举右，维护左
        if (!flag)
        {
            return 0;
        }
        return ans;
    }
};

//在 while 循环结束后更新答案
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size(), ans = n + 1, sum = 0, left = 0;
        for (int right = 0; right < n; right++) { // 枚举子数组右端点
            sum += nums[right];
            while (sum - nums[left] >= target) { // 尽量缩小子数组长度
                sum -= nums[left];
                left++; // 左端点右移
            }
            if (sum >= target) {
                ans = min(ans, right - left + 1);
            }
        }
        return ans <= n ? ans : 0;
    }
};
