//给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
//nums 为 无重复元素 的 升序 排列数组
//请必须使用时间复杂度为 O(log n) 的算法。

//假设题意是叫你在排序数组中寻找是否存在一个目标值，那么训练有素的读者肯定立马就能想到利用二分法在 O(logn) 
//的时间内找到是否存在目标值。但这题还多了个额外的条件，即如果不存在数组中的时候需要返回按顺序插入的位置，
//那我们还能用二分法么？答案是可以的，我们只需要稍作修改即可。
//
//考虑这个插入的位置 pos，它成立的条件为：
//nums[pos−1] < target≤nums[pos]
//其中 nums 代表排序数组。由于如果存在这个目标值，我们返回的索引也是 pos，因此我们可以将两个条件合并得出最后的目标：
//「在一个有序数组中找第一个大于等于 target 的下标」。
//
//问题转化到这里，直接套用二分法即可，即不断用二分法逼近查找第一个大于等于 target 的下标 。
//下文给出的代码是笔者习惯的二分写法，ans 初值设置为数组长度可以省略边界条件的判断，因为存在一种情况是 target 大于数组中的所有数，此时需要插入到数组长度的位置。
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        if (nums[0] > target)
        {
            return 0;
        }
        if (nums[n - 1] < target)
        {
            return n;
        }
        int l = 0, r = n - 1, ans = -1;
        //查找>=target的最小的数字即可
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] >= target)
            {
                ans = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        return ans;
    }
};
