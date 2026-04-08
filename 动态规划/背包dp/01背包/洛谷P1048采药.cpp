#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
constexpr int INF = 0x3f3f3f3f;
struct node {
	int w, v;
};
//状态定义：dp[i][j]表示自由选择前i个物品，占用容量不超过j的得到的价值
int dp[105][1005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t, m;
	cin >> t >> m;
	vector<node> a(m+1);
	for (int i = 1; i <= m; i++)
	{
		cin >> a[i].w >> a[i].v;
	}
	//来到每个位置，枚举选择或不选择，取较大值
	//能选择的前提是容量足够
	//base case:i==0时，也就是一个物品也不选择，那么价值就是0
	for (int i = 1; i <= m; i++)
	{
		int w = a[i].w, v = a[i].v;
		for (int j = 0; j <= t; j++)
		{
			//不选择i号位置的物品
			int can1 = dp[i - 1][j];
			//选择i号位置的物品
			int can2 = -INF;
			if (j - w >= 0)
			{
				can2 = dp[i - 1][j - w] + v;
			}
			dp[i][j] = max(can1, can2);
		}
	}
	cout << dp[m][t] << '\n';
	return 0;
}