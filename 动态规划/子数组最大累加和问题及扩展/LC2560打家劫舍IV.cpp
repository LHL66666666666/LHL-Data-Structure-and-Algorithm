#include <vector>
using namespace std;
//二分答案结合DP
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    long long dp[100005];
    bool check(int tar, vector<int>& nums,int k)
    {
        int n = nums.size();
        //memset(dp, 0, sizeof(dp));
        long long cnt = -INF;
        if (nums[0] <= tar)dp[0] = 1;
        else dp[0] = 0;
        dp[1] = max(dp[0], (long long)(nums[1] <= tar));
        cnt = max(dp[0], dp[1]);
        for (int i = 2; i < n; i++)
        {
            long long tmp = (long long)(nums[i] <= tar);
            dp[i] = max(dp[i - 1], dp[i - 2] + tmp);
            cnt = max(cnt, dp[i]);
        }
        return cnt >= k;
    }
    int minCapability(vector<int>& nums, int k) {
        //关键点：只能取数组中 小于等于能力值的元素
        //二分能力值
        //小于等于能力值的且满足要求的就全部拿走
        //dp数组状态定义：dp[i]表示到i位置最多选的的房子的个数
        //状态转移：选or不选i位置的房子
        //二分答案：答案范围是数组元素最小值-数组元素最大值
        //单调性：能力越大，可选择的数量就越大
        int liml = INF, limr = -INF;
        int n = nums.size();
        if (n == 1)
        {
            return nums[0];
        }
        if (n == 2)
        {
            return min(nums[0], nums[1]);
        }
        for (int i = 0; i < n; i++)
        {
            liml = min(liml, nums[i]);
            limr = max(limr, nums[i]);
        }
        int l = liml, r = limr;
        int ans = r;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (check(mid, nums,k))
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return ans;
    }
};
/*
定义 f[i] 表示从 nums[0] 到 nums[i] 中偷金额不超过 mx 的房屋，
最多能偷多少间房屋。
如果 f[n−1]≥k 则表示答案至多为 mx，否则表示答案必须超过 mx。
用「选或不选」来分类讨论：

不选 nums[i]：f[i]=f[i−1]；
选 nums[i]，前提是 nums[i]≤mx：f[i]=f[i−2]+1。
这两取最大值，即
f[i]=max(f[i−1],f[i−2]+1)
*/