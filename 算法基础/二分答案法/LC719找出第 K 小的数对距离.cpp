////暴力解法
//class Solution {
//public:
//    int smallestDistancePair(vector<int>& nums, int k) {
//        int n = nums.size();
//        int arr[1000005] = {0};
//        for (int i = 0; i < n - 1; i++)
//        {
//            for (int j = i + 1; j < n; j++) 
//            {
//                arr[abs(nums[i] - nums[j])]++;
//            }
//        }
//        int cnt = 0;
//        for (int i = 0; i < 1000005; i++)
//        {
//            cnt += arr[i];
//            if (cnt >= k)
//            {
//                return i;
//            }
//        }
//        return 0;
//    }
//};

//优化：首先注意到：这个数组排序之后不影响答案
//因为求的是绝对值
//绝对值差值的范围已知：[0,max-min]
//max-min在排序后很容易求得 
//单调性：如果这个绝对值越小，对应的位次k也就越小
class Solution {
public:
    bool check(vector<int>& nums, int k, int mid)
    {
        //滑动窗口
        //举例：找绝对值的差不大于8的
        //[1,1,2,3,4,7,8,9,10,11,11,23]
        // ^             ^
        //   ^           ^
        //     ^           ^
        //只需要找到窗口的两端，然后在这个窗口中任取两个数字，
        //绝对值的差都小于给定的要求，这样计数不对，会重复
        //小心重复！！！
        //思路换一下，遍历数组的每一个元素作为窗口左端，然后
        //找到右侧临界元素，每次只记录以l为起点的数对的个数
        int n = nums.size();
        int l = 0, r = 0, cnt = 0;
        while (l < n - 1)
        {
            int r = l;
            while (r<=n-1 && nums[r] - nums[l] <= mid )
            {
                r++;
            }
            cnt += r - l - 1;
            l++;
        }
        if (cnt >= k)
        {
            return true;
        }
        return false;

    }
    int smallestDistancePair(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int l = 0, r = nums[n - 1] - nums[0], ans = r;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (check(nums, k, mid))
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return ans;
    }
};
/*
数对 (a,b) 由整数 a 和 b 组成，其数对距离定义为 a 和 b 的绝对差值。
给你一个整数数组 nums 和一个整数 k ，数对由 nums[i] 和 nums[j] 组成
且满足 0 <= i < j < nums.length 。
返回 所有数对距离中 第 k 小的数对距离
*/