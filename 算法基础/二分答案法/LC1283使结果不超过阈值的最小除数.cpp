#include <vector>
using namespace std;
class Solution {
public:
    bool check(vector<int>& nums, int x, int threshold)
    {
        long long sum = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            sum += (nums[i] + x - 1) / x;
        }
        return sum <= threshold;
    }
    int smallestDivisor(vector<int>& nums, int threshold) {
        //nums.length <= threshold <= 10^6
        //答案具有范围[1,1e6]
        //如果这个选择的除数越大
        //那么和就越小
        //满足单调性
        //可以二分答案
        int l = 1, r = 1000000;
        int ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (check(nums, mid, threshold))
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return ans;
    }
};