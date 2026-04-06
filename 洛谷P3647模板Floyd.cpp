#include <iostream>
using namespace std;
int n, m;
int u, v, w;
const int INF = 0x3f3f3f3f;
int dis[105][105];
//约定忽略图的自环，重边仅保留权值最小的一条
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i == j) dis[i][j] = 0;
			else dis[i][j] = INF;
		}
	}
	while (m--)
	{
		cin >> u >> v >> w;
		if (dis[u][v] > w) {
			dis[u][v] = w;
			dis[v][u] = w;
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
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << dis[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}