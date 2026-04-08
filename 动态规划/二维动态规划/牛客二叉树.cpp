/*
小强现在有n个节点,他想请你帮他计算出有多少种不同的二叉树满足
节点个数为n
且树的高度不超过m的方案.
因为答案很大,所以答案需要模上1e9+7后输出.
树的高度: 定义为所有叶子到根路径上节点个数的最大值.
例如: 当n=3,m=3时,有如下5种方案:
数据范围：1≤n,m≤50
*/
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 1e9 + 7;
int n, m;
ll dp1[55][55];
ll f1(int n1, int h) {
    if (n1 == 0) {
        return 1;
    }
    if (h == 0) {
        return 0;
    }
    if (dp1[n1][h] != -1) {
        return dp1[n1][h];
    }
    //固定头节点，划分左树和右树
    //假设还剩x个节点(除了头节点)，划分为
    //左：0，右：x
    //左：1，右：x-1
    //左：2，右：x-2
    //以此类推
    ll ans = 0;
    for (int i = 0; i <= n1 - 1; i++) {
        ans = (ans % N + (f1(i, h - 1) % N * f1(n1 - i - 1, h - 1) % N) % N) % N;
    }
    dp1[n1][h] = ans;
    return ans;
}
//改dp
//n*m的表
ll f2() {
    for (int i = 1; i <= n; i++) {
        dp1[i][0] = 0;
    }
    for (int j = 0; j <= m; j++) {
        dp1[0][j] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k <= i - 1; k++) {
                dp1[i][j] += (dp1[k][j - 1] % N * dp1[i - 1 - k][j - 1] % N) % N;
                dp1[i][j] %= N;
            }
        }
    }
    return dp1[n][m];
}
//滚动数组优化
ll dp[55];
ll f3()
{
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = 0;
    }
    for (int j = 1; j <= m; j++)
    {
        for (int i = n; i >= 1; i--)
        {
            //注意这里每次要将原始数据（上一列的）清空
            dp[i] = 0;
            for (int k = 0; k <= i - 1; k++)
            {
                dp[i] += (dp[k] % N * dp[i - 1 - k] % N) % N;
                dp[i] %= N;
            }
        }
    }
    return dp[n];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    //memset(dp1, 0, sizeof(dp1));
    //根节点最多有1个
    //对于一个节点而言，左孩子和右孩子认为是不同的
    cout << f3();
    return 0;
}