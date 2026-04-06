//给定一个包含[0, n] 中 n 个数的数组 nums ，
//找出[0, n] 这个范围内没有出现在数组中的那个数。
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum1 = 0, sum2 = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            sum1 ^= nums[i];
            sum2 ^= i;
        }
        sum2 ^= n;
        return sum1 ^ sum2;
    }
};