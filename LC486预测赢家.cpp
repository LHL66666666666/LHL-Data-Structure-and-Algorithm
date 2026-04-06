#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    //一个递归函数求出当前最大得分
    //这个递归的含义是，来到l,r的局面，当前选手的最大得分
    int f1(int l, int r, int sum, vector<int>& nums, vector<vector<int>>& dp)
    {
        if (dp[l][r] != -1) return dp[l][r];
        //终局状态
        if (l == r)
        {
            return nums[l];
        }
        //选择从左拿
        int ret1 = sum - f1(l + 1, r, sum - nums[l],nums, dp);
        //选择从右拿
        int ret2 = sum - f1(l, r - 1, sum - nums[r], nums, dp);
        dp[l][r] = max(ret1, ret2);
        return max(ret1, ret2);
    }
    //另一递归写法，本质上是一样的
    bool predictTheWinner(vector<int>& nums) {
        //首先，两个人的得分总和是固定的
        int n = nums.size();
        if (n == 1) return true;
        int sum = 0;
        for (int i = 0; i < n; i++) sum += nums[i];
        vector<vector<int>> dp(n, vector<int>(n, -1));
        //MinMax的思想，因为是零和博弈，二者最终得分之和为定值，
        //来到每个人的回合，都希望尽量最小化对手得分，就可以最大化自己的得分
        int fst= f1(0, n - 1, sum, nums, dp);
        return fst >= sum - fst;
    }
};