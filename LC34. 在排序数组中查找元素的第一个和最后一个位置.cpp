class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ret;
        int n = nums.size();

        // 处理空数组情况
        if (n == 0) {
            return { -1, -1 };
        }

        int l = 0, r = n - 1, ans1 = -1, ans2 = -1;

        // 查找第一个大于等于target的位置（开始位置）
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] >= target) {
                ans1 = mid;
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }

        // 重置指针，查找最后一个小于等于target的位置（结束位置）
        l = 0;
        r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] <= target) {
                ans2 = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }

        // 检查找到的位置是否有效
        //注意这里：如果忘记检查的话，那么直接访问数组下标为-1的元素是非法的操作
        if (ans1 != -1 && ans2 != -1 && nums[ans1] == target && nums[ans2] == target) {
            return { ans1, ans2 };
        }
        else {
            return { -1, -1 };
        }
    }
};
//也就是说，要求连续元素的开始位置和末位置
//双指针可以O(n),要求O(log n),二分
//给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
//
//如果数组中不存在目标值 target，返回[-1, -1]。
//
//你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
//nums 是一个非递减数组

//用红绿灯标记法
//先写模板
class Solution {
public:
    int binSearch(vector<int>& nums, int target)
    {
        int n = nums.size();
        int l = -1, r = n;
        while (r - l > 1)
        {
            int mid = (l + r) / 2;
            if (nums[mid] >= target)
            {
                r = mid;
            }
            else l = mid;
        }
        return r;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0)
        {
            return { -1,-1 };
        }
        vector<int> ret;
        int idx = binSearch(nums, target);
        if (idx == n)
        {
            return { -1,-1 };
        }
        else if (nums[idx] != target)
        {
            return { -1,-1 };
        }
        else ret.push_back(binSearch(nums, target));
        int idx1 = binSearch(nums, target + 1);
        {
            if (idx1 == n)
            {
                ret.push_back(n - 1);
            }
            //这里idx1查找的是大于target的最小元素的位置
            //记得减1才是target的位置
            else ret.push_back(idx1-1);
        }
        return ret;
    }
};