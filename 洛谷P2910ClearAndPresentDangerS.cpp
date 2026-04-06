#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int n, m;
int u, v, w;
const int INF = 0x3f3f3f3f;
int dis[105][105];
vector<int> p;
//约定忽略图的自环，重边仅保留权值最小的一条
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a;
		cin >> a;
		p.push_back(a);
	}
	/*
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i == j) dis[i][j] = 0;
			else dis[i][j] = INF;
		}
	}
	*/
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> dis[i][j];
		}
	}
	//Floyd
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			if (dis[i][k] == INF) continue;
			for (int j = 1; j <= n; j++)
			{
				if (dis[i][j] > dis[i][k] + dis[k][j])
				{
					dis[i][j] = dis[i][k] + dis[k][j];
				}
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i < m - 1; i++)
	{
		int ui = p[i], vi = p[i + 1];
		ans += dis[ui][vi];
	}
	cout << ans << '\n';
	return 0;
}