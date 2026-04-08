#include<vector>
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
struct node {
	int w, val, id;
}a[1005];
bool cmp(node x, node y)
{
	return x.id < y.id;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int m, n;
	cin >> m >> n;
	set<int> s;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].w >> a[i].val >> a[i].id;
	}
	//排序并进行重编号
	sort(a + 1, a + 1 + n, cmp);
	vector<int> idx = {1};
	int cnt = 1;
	a[1].id = 1;
	for (int i = 2; i <= n; i++) {
		if (a[i - 1].id != a[i].id) {
			++cnt;
			idx.emplace_back(i);
		}
		a[i].id = cnt;
	}
	//状态定义:dp[i][j]表示来到第i组，容量不超过j，得到的最大价值
	//base case dp[0][j]全是0
	vector<vector<ll>> dp(n+1,vector<ll>(m+1));
	for (int i = 1; i <= cnt; i++)
	{
		vector<int> tmp;
		int id1 = idx[i - 1];
		while (id1 <= n && a[id1].id == i)
		{
			tmp.emplace_back(id1);
			++id1;
		}
		for (int j = 0; j <= m; j++)
		{
			//1.不选这组的
			dp[i][j] = dp[i - 1][j];
			//2.选这组的，枚举选哪个
			for (int k = 0; k < tmp.size(); k++)
			{
				int lst = j - a[tmp[k]].w;
				if (lst >= 0)
				{
					dp[i][j] = max(dp[i][j], dp[i - 1][lst] + a[tmp[k]].val);
				}
			}
		}
	}
	cout << dp[cnt][m] << '\n';
	return 0;
}
//空间压缩的话，就不需要再统计组的数量了，直接自我更新即可
//从右向左来更新dp表