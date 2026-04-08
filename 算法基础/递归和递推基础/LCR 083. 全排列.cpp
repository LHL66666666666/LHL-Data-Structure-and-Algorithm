/*
给定一个不含重复数字的整数数组 nums ，返回其 所有可能的全排列 。可以 按任意顺序 返回答案。
*/
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> ans;
    void swap(vector<int>& nums,int i,int j)
    {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
    void dfs(vector<int>&nums,int idx)
    {
        //base case 终止条件
        if (idx == nums.size())
        {
            ans.push_back(nums);
            return;
        }
        for (int j = idx; j < nums.size(); j++)
        {
            //注意j从=idx开始，因为要算上自己在这一位的情况
            swap(nums, idx, j);
            dfs(nums, idx + 1);
            //恢复现场,一定要恢复，不然会出问题
            swap(nums, idx, j);
        }

    }
    vector<vector<int>> permute(vector<int>& nums) {
        //考虑是如何递归的：我们想要全排列
        //也就是说对于任一位置i，我们希望将每一个元素都放到i位置上来，然后递归后续的所有情况
        //注意：我们递归到i位置证明i之前的所有位置都被确定好了，
        //我们只需要考虑i之后的，直到i到末尾
        dfs(nums, 0);
        return ans;
    }
};