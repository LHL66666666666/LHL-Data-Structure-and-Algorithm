#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 5005;
int n, m;
//vis数组记录哪些边被发现过，相当于模拟一个集合
int vis[MAXN];
struct cmp {
	bool operator()(pair<int, int>& a, pair<int, int>& b)
	{
		return a.second > b.second;
	}
};
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	memset(vis, 0, sizeof(vis));
	//建图
	vector<vector<pair<int, int>>> g(n + 1);
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		//注意是无向图，两边都要建
		g[u].push_back({ v,w });
		g[v].push_back({ u,w });
	}
	//自定义比较器，按照pair<int,int>的second(边权)来组织小根堆
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
	//从任意位置开始都可以
	//cnt记录顶点的数量，如果顶点数量为n表示图联通，符合题意
	int cnt = 0;
	for (auto& i : g[1])
	{
		pq.push(i);
	}
	vis[1] = 1;
	cnt++;
	//开始按最小的边处理
	ll ans = 0;
	while (!pq.empty())
	{
		//每次弹出小根堆中最小的边
		int next = pq.top().first;
		int cost = pq.top().second;
		pq.pop();
		//如果去往的点不在集合中，将去往的点加入集合，同时统计这条边作为最小生成树的边，
		//并将新加入的点连接的边加入小根堆
		//否则不操作，防止生成环
		if (vis[next] == 0)
		{
			cnt++;
			vis[next] = 1;
			ans += cost;
			for (auto& i : g[next])
			{
				pq.push(i);
			}
		}
	}
	if (cnt == n)
	{
		cout << ans << '\n';
	}
	else cout << "orz\n";
	return 0;
}
//Prim算法不同于Kruskal，每次不是加边而是加点