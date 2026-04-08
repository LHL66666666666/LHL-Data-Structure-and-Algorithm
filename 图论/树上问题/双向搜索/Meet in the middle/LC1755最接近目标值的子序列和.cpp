/*
给你一个整数数组 nums 和一个目标值 goal 。
你需要从 nums 中选出一个子序列，使子序列元素总和最接近 goal 。
也就是说，如果子序列元素和为 sum ，你需要 最小化绝对差 abs(sum - goal) 。
返回 abs(sum - goal) 可能的 最小值 。
注意，数组的子序列是通过移除原始数组中的某些元素（可能全部或无）而形成的数组。
*/
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
class Solution {
public:
    vector<ll> l;
    vector<ll> r;
    void dfs(int idx, int end, ll sum, int f, vector<int>& nums)
    {
        if (idx > end)
        {
            if (f == 0) l.emplace_back(sum);
            else r.emplace_back(sum);
            return;
        }
        dfs(idx + 1, end, sum + nums[idx], f, nums);
        dfs(idx + 1, end, sum, f, nums);
    }
    int minAbsDifference(vector<int>& nums, int goal) {
        l.clear();
        r.clear();
        int n = nums.size();
        int m = n / 2;
        if (n == 1)
        {
            return min(abs(goal), abs(goal - nums[0]));
        }
        //分两侧dfs
        dfs(0, m, 0, 0, nums);
        dfs(m + 1, n - 1, 0, 1, nums);
        sort(l.begin(), l.end());
        sort(r.begin(), r.end());
        int p1 = 0, p2 = r.size() - 1;
        ll ans = LLONG_MAX;
        for (; p1 < l.size(); p1++)
        {
            while (p2>=0 && l[p1] + r[p2] >= goal)
            {
                ans = min(ans, abs(goal - l[p1] - r[p2]));
                --p2;
            }
            if (p2 >= 0)
            {
                ans = min(ans, abs(goal - l[p1] - r[p2]));

            }

        }
        return ans;
    }
};