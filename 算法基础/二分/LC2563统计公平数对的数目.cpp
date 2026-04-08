#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int binS(vector<int>& nums, int tar,int l,int r)
    {
        int ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] <= tar)
            {
                ans = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        return ans;
    }
    int binS2(vector<int>& nums, int tar,int l,int r)
    {
        int ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] >= tar)
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return ans;
    }
    
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        //先排序，遍历每一个i，二分查找两个临界的j，计算区间长度即为答案
        long long ans = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int tmp1 = binS2(nums, lower - nums[i],i+1,n-1);
            int tmp2 = binS(nums, upper - nums[i],i+1,n-1);
            if (tmp1 != -1 && tmp2 != -1 && tmp1 <= tmp2)
            {
                ans += tmp2 - tmp1 + 1;
            }

        }
        return ans;
    }
};
/*
方法一：二分查找
思路与算法

题目要求我们找到两个数 nums[i] 和 nums[j]，满足

lower≤nums[i]+nums[j]≤upper
可以发现排序并不会影响最后的计数结果，因此我们可以先进行排序。
对于每一个 nums[j]，可以使用二分查找找到一个区间 [l,r]，
使得所有的 i∈[l,r] 满足
lower−nums[j]≤nums[i]≤upper−nums[j]

具体来说，我们可以找到 ≤upper−nums[j] 的元素个数，
减去 <lower−nums[j] 的元素个数，加入答案。
*/
/*
方法二：三指针
思路与算法

在给数组 nums 排序后，随着枚举的 nums[j] 变大，upper−nums[j] 
和 lower−nums[j] 都变小，具有单调性！！！
于是我们可以用三指针来代替二分查找的搜索过程。

具体来说，使用两个指针 left 和 right 分别表示 ≤upper−nums[j] 的最大元素位置
和 <lower−nums[j] 的最大元素位置,
那么满足条件的 nums[i] 就被夹在三个指针当中，作差从而得到答案的数量。

*/

class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        ranges::sort(nums);
        long long ans = 0;
        int l = nums.size(), r = l;
        for (int j = 0; j < nums.size(); j++) {
            while (r && nums[r - 1] > upper - nums[j]) {
                r--;
            }
            while (l && nums[l - 1] >= lower - nums[j]) {
                l--;
            }
            // 在方法一中，二分的结果必须 <= j
            // 方法二同理，要保证 l 和 r 都 <= j
            ans += min(r, j) - min(l, j);
        }
        return ans;
    }
};
