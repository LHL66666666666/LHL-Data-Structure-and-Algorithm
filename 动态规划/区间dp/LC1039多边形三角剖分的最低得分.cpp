#include <vector>
#include <string>
using namespace std;
typedef long long ll;
class Solution {
public:
    const ll INF = 0x3f3f3f3f3f3f3f3f;
    ll f1(int l, int r, vector<int>& a,vector<vector<ll>>& dp)
    {
        if (dp[l][r] != -1) return dp[l][r];
        if (r - l == 2)
        {
            return 1LL * a[l] * a[l + 1] * a[l + 2];
        }
        if (r - l < 2) return 0;
        ll ret = INF;
        //注意到:每一条边都必须对应一个三角形
        //那么0-(n-1)这条边，必定对应一个三角形
        //枚举分割点，一开始将0和n-1放在一起，固定这条线段
        //对于递归中的每一个子问题，我们都预定一条线段(两端的线段，然后枚举分割点)
        for (int i = l + 1; i <= r - 1; i++)
        {
            ll tmp = 1LL * a[l] * a[r] * a[i];
            tmp += f1(l, i, a,dp) + f1(i, r, a,dp);
            ret = min(ret, tmp);
        }
        dp[l][r] = ret;
        return ret;
    }
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        //n个顶点，划分为n-2个三角形
        //显然这是一个Catalan数相关的问题
        //每次枚举划分点分成两个区间，直到不能再分
        vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, -1));
        return f1(0, n - 1, values,dp);
    }
}; 
//严格位置依赖的dp
class Solution {
public:
    const ll INF = 0x3f3f3f3f3f3f3f3f;
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
        //base case
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i; j <= min(i + 1, n - 1); j++)
            {
                dp[i][j] = 0;
            }
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i + 2; j < n; j++)
            {
                dp[i][j] = INF;
                for (int k = i + 1; k <= j - 1; k++)
                {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + 1LL * values[i] * values[j] * values[k]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
//实际上，这个问题就是基于Catalan数的思路来的
//设(n + 2)边形三角剖分的方案数为T_n．先选定一条边 (1, n + 2) 作为基边，
//它一定属于一个三角形，记该三角形的第三个点为k
//k属于[2, n + 1]这样，原凸多边形变成了三个部分：
//三角形(1, k, n + 2)
//k边形，顶点 1~k
//(n + 3 - k) 边形，顶点 k~n-2
//后面两个部分都是子问题，所以，有递推关系
