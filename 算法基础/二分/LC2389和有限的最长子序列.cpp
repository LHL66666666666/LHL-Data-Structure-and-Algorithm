/*
给你一个长度为 n 的整数数组 nums ，和一个长度为 m 的整数数组 queries 。

返回一个长度为 m 的数组 answer ，其中 answer[i] 是 nums 中 元素之和小于等于 queries[i] 的 子序列 的 最大 长度  。

子序列 是由一个数组删除某些元素（也可以不删除）但不改变剩余元素顺序得到的一个数组。
*/
//思路正确，注意边界条件判断
class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        //可以排序
        sort(nums.begin(), nums.end());
        vector<int> ret;
        int n = nums.size();
        int m = queries.size();
        //前缀和，这里使用了贪心
        for (int i = 1; i < n; i++)
        {
            nums[i] = nums[i - 1] + nums[i];
        }
        //前缀和处理完之后不用遍历，直接二分查找即可
        for (int i = 0; i < m; i++)
        {
            int flag = 1;
            //记得处理两个边界
            if (nums[0] > queries[i])
            {
                ret.push_back(0);
                continue;
            }
            if (nums[n - 1] <= queries[i])
            {
                ret.push_back(n);
                continue;
            }
            for (int j = 1; j < n; j++)
            {
                if (nums[j] > queries[i])
                {
                    ret.push_back(j);
                    flag = 0;
                    break;
                }
            }
        }
        return ret;
    }
};

//可以不用遍历，用二分查找
class Solution {
public:
    int binSearch(vector<int>& nums, int target)
    {
        int n = nums.size();
        //目标是查找小于等于target的最大元素
        int l = 0, r = n - 1, ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] <= target)
            {
                ans = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        return ans;

    }
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        sort(nums.begin(), nums.end());
        vector<int> ret;
        int n = nums.size();
        int m = queries.size();
        for (int i = 1; i < n; i++)
        {
            nums[i] = nums[i - 1] + nums[i];
        }
        for (int i = 0; i < m; i++)
        {
            int b = binSearch(nums, queries[i]);
            if (b == -1)
            {
                ret.push_back(0);
            }
            else ret.push_back(b + 1);
        }
        return ret;
    }
};
/*
核心思路
贪心：由于元素和有上限，为了能让子序列尽量长，子序列中的元素值越小越好。

对于本题来说，元素在数组中的位置是无关紧要的。因为我们从小到大算数组中的元素和，
无论数组是 [1,2,3] 还是 [3,2,1] 还是别的顺序，不影响答案。所以可以排序。

把 nums 从小到大排序后，再从小到大选择尽量多的元素（相当于选择一个前缀），
使这些元素的和不超过询问值。

时间优化
既然求的是前缀的元素和（前缀和），那么干脆把每个前缀和都算出来。

做法是递推：前 i 个数的元素和，等于前 i−1 个数的元素和，加上第 i 个数的值。

例如 [4,5,2,1] 排序后为 [1,2,4,5]，从左到右递推计算前缀和，得到 [1,3,7,12]。

由于 nums[i] 都是正整数，前缀和是严格单调递增的，这样就能在前缀和上使用二分查找：
找到大于 queries[i] 的第一个数的下标，由于下标是从 0 开始的，
这个数的下标正好就是前缀和小于等于 queries[i] 的最长前缀的长度。

例如在 [1,3,7,12] 二分查找大于 3 的第一个数（7），得到下标 2，
这正好就是前缀和小于等于 3 的最长前缀长度。对应到 nums 中，
就是选择了 2 个数（1 和 2）作为子序列中的元素。*/