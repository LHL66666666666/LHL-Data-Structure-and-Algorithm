/*
有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组 nums 中。
现在要求你戳破所有的气球。
戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币。 
这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号。
如果 i - 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球。
求所能获得硬币的最大数量
*/
#include <vector>
using namespace std;
typedef long long ll;
class Solution {
public:
    //递归函数,表示当前可以在[l..r]范围上选择最后一个被打爆的气球的位置，得到的最大得分
    //f1隐含的前提条件:由于在[l..r]上选择最后被打爆的位置,保证l-1位置,r+1位置气球未被打爆
    ll f1(vector<int>& a, int l, int r, vector<vector<ll>>& dp)
    {
        if (dp[l][r] != -1) return dp[l][r];
        if (l > r) return 0;
        if (l == r)
        {
            return 1LL * a[l - 1] * a[l] * a[l + 1];
        }
        ll ans = 0;
        //这里[l...r]范围上，每个点都可以作为最后一个被打爆的位置
        //同时，由于i号位置是最后一个被打爆的位置，那么在i点被打爆时，结算分数应该为
        //l-1的 乘上 i的 乘上 r+1的 (因为i最后一个爆，区间上的已经在他之前消失了)
        //其次，我们调递归的时候，i位置作为划分点是左侧区间的右边界+1，以及右侧区间的左边界-1
        //满足我们要求的：调用f1(l..r)时，保证l-1位置,r+1位置气球未被打爆
        for (int i = l; i <= r; i++)
        {
            ll tmp = 1LL * a[l - 1] * a[i] * a[r + 1];
            tmp += f1(a, l, i - 1, dp) + f1(a, i + 1, r, dp);
            ans = max(ans, tmp);
        }
        dp[l][r] = ans;
        return ans;
    }
    int maxCoins(vector<int>& nums) {
        //关键点是逆推：因为如果正向推的话，讨论哪一个气球先被打爆，
        //这样的话，每消除掉一个数字会使得数组改变，也就是说，具有后效性，很难递推
        //因此我们考虑逆向，讨论某个气球最后被打爆，
        //问题就变成逐渐向数组中添加气球
        //这样一来，在进行递归的时候，我们按照最后被打爆的气球作为分界点，递归调用子区间
        //就能保证子区间上的每一个点始终可以找到：这个点的气球被打爆时，左侧的元素和右侧的元素
        int n1= nums.size();
        //先预处理，在两侧各添加1，为了避免越界的讨论
        vector<int> a;
        a.emplace_back(1);
        for (int i = 0; i < n1; i++) a.emplace_back(nums[i]);
        a.emplace_back(1);
        int n = a.size();
        vector<vector<ll>> dp(n + 1, vector<ll>(n + 1,-1));
        return f1(a, 1, n - 2, dp);
    }
};

//改为严格位置依赖的dp
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n1 = nums.size();
        vector<int> a;
        a.emplace_back(1);
        for (int i = 0; i < n1; i++) a.emplace_back(nums[i]);
        a.emplace_back(1);
        int n = a.size();
        vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
        //我们要填的有效区间为[1,n-2]
        //base case
        for (int i = 1; i <= n - 2; i++)
        {
            dp[i][i] = a[i - 1] * a[i] * a[i + 1];
        }
        for (int i = n - 2; i >= 1; i--)
        {
            for (int j = i + 1; j <= n-2; j++)
            {
                dp[i][j] = 0;
                //枚举分割点
                for (int k = i; k <= j; k++)
                {
                    ll tmp = a[i - 1] * a[j + 1] * a[k];
                    tmp += dp[i][k - 1] + dp[k + 1][j];
                    dp[i][j] = max(dp[i][j], tmp);
                }
            }

        }
        return dp[1][n - 2];
    }
};