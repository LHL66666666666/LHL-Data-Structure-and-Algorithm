#include <vector>
#include <queue>
#include <deque>
#include <iostream>
using namespace std;
typedef long long ll;
int n, m, k, s, t;
int a, b, c;
auto cmp = [](const vector<ll>& x, const vector<ll>& y)
	{
		return x[2] > y[2];
	};
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k >> s >> t;
	//建图,无向图
	vector<vector<pair<int, int>>> g(n);
	while (m--)
	{
		cin >> a >> b >> c;
		g[a].push_back({ b,c });
		g[b].push_back({ a,c });
	}
	//分层图最短路:定义状态:城市编号+第几次免费到达本城市
	//注意还要计算免费次数不能超过k
	vector<vector<int>> vis(n, vector<int>(k+1));
	vector<vector<ll>> dis(n, vector<ll>(k+1, LLONG_MAX));
	//pq存三个：节点编号、第几次免费、截至目前的开销
	priority_queue<vector<ll>, vector<vector<ll>>, decltype(cmp)>pq(cmp);
	//源点入队
	pq.push({ s,0,0 });
	dis[s][0] = 0;
	while (!pq.empty())
	{
		int u = pq.top()[0];
		int cur_k = pq.top()[1];
		int cost = pq.top()[2];
		pq.pop();
		if (vis[u][cur_k]) continue;
		vis[u][cur_k] = 1;
		if (u == t)
		{
			cout << cost << '\n';
			return 0;
		}
		for (auto& i : g[u])
		{
			int v = i.first;
			int w = i.second;
			//选择不免费
			if (!vis[v][cur_k] && dis[v][cur_k] > w + cost)
			{
				dis[v][cur_k] = w + cost;
				pq.push({ v,cur_k,dis[v][cur_k] });
			}
			//选择免费
			if (cur_k<k && !vis[v][cur_k + 1] && dis[v][cur_k + 1]>cost)
			{
				dis[v][cur_k + 1] = cost;
				pq.push({ v,cur_k + 1,dis[v][cur_k + 1] });
			}
		}
	}
	return 0;
}