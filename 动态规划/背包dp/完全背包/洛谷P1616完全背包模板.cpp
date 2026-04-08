#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
int t, m;
struct node {
	int cost, val;
}a[10005];
//完全背包的模板
//可以考虑一个朴素的做法：对于第i件物品，枚举其选了多少个来转移
//也就是dp[i][j]=dp[i-1][j-k*w[i]]+k*val[i],其中k从0到正无穷
//但是这样做的时间复杂度是O(n ^ 3)的
//优化：实际上对于dp[i][j]只需要考虑dp[i][j-w[i]]来转移即可
//dp[i][j]表示前i种物品随意选择，容量不超过j下的得到的最大价值
//因为一个物品可以选择任意多个，因此我们在来到dp[i][j]时，从dp[i][j-w[i]]来转移即可
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> t >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> a[i].cost >> a[i].val;
	}
	//空间压缩：每个格子依赖于本行左侧的格子和上一行该位置的格子
	//从左向右更新
	vector<ll> dp(t + 1);
	for (int i = 1; i <= m; i++)
	{
		for (int j = 0; j <= t; j++)
		{
			if (j - a[i].cost >= 0)
			{
				dp[j] = max(dp[j], dp[j - a[i].cost] + a[i].val);
			}
		}
	}
	cout << dp[t] << '\n';
	return 0;
}