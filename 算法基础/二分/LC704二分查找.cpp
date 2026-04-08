class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = n - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] > target)
            {
                r = mid - 1;
            }
            else if (nums[mid] < target)
            {
                l = mid + 1;
            }
            else return mid;
        }
        return -1;
    }
};
//给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，
//写一个函数搜索 nums 中的 target，如果 target 存在返回下标，否则返回 - 1。
//
//你必须编写一个具有 O(log n) 时间复杂度的算法。
//最经典的二分查找，easy
//也可以使用红绿灯标记法的模板完成