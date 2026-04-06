//使用二分实现
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //先排序
        vector<int> ret;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; i++)
        {
            int flag = 0;
            int tmp = nums[i];
            int f = target - tmp;
            //也就是说，现在目标变为在i往后的数组中查找f
            int l = i + 1, r = n - 1;
            while (l <= r)
            {
                int mid = (l + r) / 2;
                if (nums[mid] > f)
                {
                    r = mid - 1;
                }
                else if (nums[mid] < f)
                {
                    l = mid + 1;
                }
                else {
                    ret.push_back(nums[mid]);
                    ret.push_back(nums[i]);
                    flag = 1;
                    return ret;
                }
            }
           
        }
        return ret;
    }
};