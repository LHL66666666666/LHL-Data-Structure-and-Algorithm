#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
constexpr int INF = 0x3f3f3f3f;
int n, m;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	//cost数组存储花费钱数
	vector<int> cost(m + 1);
	//val数组存储价值：价格*重要度
	vector<int> val(m + 1);
	//二维数组fans，fans[i]表示以i作为主件的附件的列表
	vector<vector<int>> fans(m + 1);
	//开一个数组存储主件，只有主件需要展开可能性，下标0弃而不用
	vector<int> a(1);
	for (int i = 1; i <= m; i++)
	{
		int v, p, q;
		cin >> v >> p >> q;
		cost[i] = v;
		val[i] = v * p;
		if (q == 0)
		{
			a.emplace_back(i);
		}
		else {
			fans[q].emplace_back(i);
		}
	}
	//开始跑背包dp
	//只需要在主件展开可能性
	int n1 = a.size();
	//状态定义：dp[i][j]表示前i个主件及附件任取(满足要求的前提下)，花费钱数不超过j，得到的最大价值
	vector<vector<int>> dp(n1 + 1, vector<int>(n + 1));
	//第0行为base case 表示不选任何物品，得到价值为0
	//虽然我们弃用了0下标，但是计算size还算上了0，注意这里要小于n1,否则越界
	for (int i = 1; i < n1; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			//不选主件
			dp[i][j] = dp[i - 1][j];
			//如果要选主件
			//只选主件
			if (j - cost[a[i]] >= 0)
			{
				dp[i][j] = max(dp[i][j], dp[i - 1][j - cost[a[i]]] + val[a[i]]);
			}
			//有几个附件
			int nfans = fans[a[i]].size();
			for (int k = 0; k < nfans; k++)
			{
				int id = j - cost[a[i]] - cost[fans[a[i]][k]];
				if (id >= 0)
				{
					dp[i][j] = max(dp[i][j], dp[i - 1][id] + val[a[i]] + val[fans[a[i]][k]]);
				}
			}
			//如果两个全要
			if (nfans == 2)
			{
				int id = j - cost[a[i]] - cost[fans[a[i]][0]] - cost[fans[a[i]][1]];
				if (id >= 0)
				{
					dp[i][j] = max(dp[i][j], dp[i - 1][id] + val[a[i]] + val[fans[a[i]][0]] + val[fans[a[i]][1]]);
				}
			}
		}
		
	}
	//记得n1-1
	cout<<dp[n1-1][n]<<'\n';
	return 0;
}