class Solution {
public:
    int binSearch(vector<int>& nums, int target)
    {
        int n = nums.size();
        int l = -1, r = n;
        while (r > l + 1)
        {
            int mid = l + (r - l) / 2;
            //跟据大于0，小于0染色
            if (nums[mid] >= target)
            {
                r = mid;
            }
            else l = mid;
        }
        //r就是查找到的
        return r;
    }
    int maximumCount(vector<int>& nums) {
        //有序数组，查找考虑二分
        //查找大于0的最小元素和小于0的最大元素
        //查找两次
        //用一下红绿灯标记法
        int n = nums.size();
        int neg = binSearch(nums, 0);
        int tmp = binSearch(nums, 1);
        int pos = n - tmp;
        return neg > pos ? neg : pos;
    }
};