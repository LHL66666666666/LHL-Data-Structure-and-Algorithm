#include <vector>
using namespace std;
int tmp[10005];
class Solution {
public:
    int merge(vector<int>& nums, int l, int m, int r)
    {
        //发现从大到小排序比较简单？
        //当然从小到大排序也可以，都是使用不回退的双指针进行统计
        //先统计满足要求的数对
        int pr = m+1, ans = 0;
        for (int j = l; j <= m; j++)
        {
            //乘法一定要防止爆int
            while (pr <= r && (long long)nums[j] <= (long long)2 * nums[pr])
            {
                pr++;
            }
            ans += (r - pr + 1);
            if (pr >= r)
            {
                continue;
            }
        }
        for (int i = l; i <= r; i++)
        {
            tmp[i] = nums[i];
        }
        int p1 = l, p2 = m + 1;
        int idx = l;
        while (p1 <= m && p2 <= r)
        {
            if (tmp[p1] >= tmp[p2])
            {
                nums[idx++] = tmp[p1++];
            }
            else {
                nums[idx++] = tmp[p2++];
            }
        }
        while (p1 <= m)
        {
            nums[idx++] = tmp[p1++];
        }
        while (p2 <= r)
        {
            nums[idx++] = tmp[p2++];
        }
        return ans;
        
    }
    int mergeSort(vector<int>& nums, int l, int r)
    {
        if (l >= r)
        {
            return 0;
        }
        int ans = 0;
        int m = l + (r - l) / 2;
        return mergeSort(nums, l, m) + mergeSort(nums, m + 1, r) + merge(nums, l, m, r);
    }
    int reversePairs(vector<int>& nums) {
        //对于这个问题，由于下标对应的数字要求了大小关系
        //所以我们不能将数组直接排序
        int n = nums.size();
        //可以并归分治
        int ret = mergeSort(nums, 0, n - 1);
        return ret;
    }
};