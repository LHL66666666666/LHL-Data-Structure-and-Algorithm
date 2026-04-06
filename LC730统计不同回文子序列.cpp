#include <vector>
#include <string>
#include <set>
using namespace std;
typedef long long ll;
class Solution {
public:
    const int MOD = 1e9 + 7;
    vector<vector<ll>> dp;
    vector<int> left;
    vector<int> right;
    //dfs(l,r)表示[l,r]范围上，不同的回文子序列的数量
    ll dfs(string& s, int l, int r)
    {
        //base case
        if (l > r)
        {
            return 0;
        }
        if (l == r)
        {
            return 1;
        }
        if (dp[l][r] != -1) return dp[l][r];
        ll ret = 0;
        //跟据左右端点是否相等来讨论
        //情况1：左右端点不相等
        //那么只需求出[l,r-1]的回文序列数量+[l+1,r]的回文序列数量-[l+1,r-1]的回文序列数量
        //核心就是容斥，中间部分被计算了两次
        if (s[l] != s[r])
        {
            ret = dfs(s, l, r - 1) + dfs(s, l + 1, r) - dfs(s, l + 1, r - 1);
        }
        //情况2：左右端点相等，不妨假设两端点都是a
        //分三种情况：
        //1.区间[l+1,r-1]没有a
        //那么dp[l][r]= 2*dp[l+1,r-1] + 2 , 原因是中间生成的回文子序列可以选择两边套上两个a或者不套
        //+2是因为考虑 a 和 aa 这两个序列
        //2.区间[l+1,r-1]上只有一个a
        //那么dp[l][r]= 2*dp[l+1,r-1] + 1 ,原因是a被算重复了1次
        //3.区间[l+1,r-1]上只有大于等于2个数量的a
        //那么dp[l][r]= 2*dp[l+1][r-1] - dp[i+1][j-1]
        //其中i是l位置的a右侧的第一个a的位置
        //j是r位置的a左侧的第一个a的位置
        //原因：举例：a....a...a........a
        //                i   j
        //[i+1,j-1]位置的回文序列，在考虑两边套上a时，重复计算了一次，需要减掉
        else {
            int ri = right[l], le = left[r];
            if (ri > le)
            {
                //区间[l,r]内部没有这个字母
                ret = dfs(s, l + 1, r - 1) * 2 + 2;
            }
            else if (ri == le)
            {
                //区间[l,r]内部有且仅有1个这个字母
                ret = dfs(s, l + 1, r - 1) * 2 + 1;
            }
            else {
                //区间[l,r]内部有1个以上的这个字母
                ret = dfs(s, l + 1, r - 1) * 2 - dfs(s, ri + 1, le - 1);
            }
        }
        ret = (ret % MOD + MOD) % MOD;
        dp[l][r] = ret;
        return ret;
    }
    int countPalindromicSubsequences(string s) {
        int n = s.size();
        if (n == 1) return 1;
        if (n == 2) return 2;
        dp.assign(n + 1, vector<ll>(n + 1, -1));
        //我们需要预处理每个位置左侧/右侧离自己最近的和自己一样的字符的位置
        left.assign(n, -1);
        right.assign(n, -1);
        for (int j = 0; j < 4; j++)
        {
            int pre = -1;
            char c = j + 'a';
            for (int i = 0; i < n; i++)
            {
                if (s[i] == c)
                {
                    left[i] = pre;
                    pre = i;
                }
            }
        }
        for (int j = 0; j < 4; j++)
        {
            int pre = -1;
            char c = j + 'a';
            for (int i = n - 1; i >= 0; i--)
            {
                if (s[i] == c)
                {
                    right[i] = pre;
                    pre = i;
                }
            }
        }
        return dfs(s, 0, n - 1);
    }
};
//本题的核心点是容斥原理加上递推
