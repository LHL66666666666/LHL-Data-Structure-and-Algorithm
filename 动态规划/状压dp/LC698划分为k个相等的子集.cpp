#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
class Solution {
public:
    vector<int> dp;
    int dfs(int status, int cur, int rest, int tar, int n, vector<int>& a)
    {
        if (rest == 0)
        {
            return 1;
        }
        if (dp[status] != -1) return dp[status];
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (status & (1 << i))
            {
                if (cur + a[i] == tar)
                {
                    ans |= dfs(status ^ (1 << i), 0, rest - 1, tar, n, a);
                }
                else if (cur + a[i] < tar)
                {
                    ans |= dfs(status ^ (1 << i), cur + a[i], rest, tar, n, a);
                }
            }
        }
        dp[status] = ans;
        return ans;
    }
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end(), greater<int>());
        //需要钦定一个和x，让所有自己的和都是x
        int sum = 0;
        for (int i = 0; i < n; i++) sum += nums[i];
        if (sum % k != 0) return false;
        dp.assign((1 << n) + 1, -1);
        return dfs((1 << n) - 1, 0, k, sum / k, n, nums);
    }
};