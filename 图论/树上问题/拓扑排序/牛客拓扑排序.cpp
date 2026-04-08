/*
描述
给定一个包含 n 个点 m 条边的有向无环图，求出该图的拓扑序。若图的拓扑序不唯一，输出任意合法的拓扑序即可。若该图不能拓扑排序，输出 -1。

输入描述：
第一行输入两个整数 n, m (1≤n,m≤2×10^5)，表示点的个数和边的条数。
接下来的 m 行，每行输入两个整数 u_i, v_i (1≤u,v≤n)，表示 u_i 到 v_i 之间有一条有向边。

输出描述：
若图存在拓扑序，输出一行 n 个整数，表示拓扑序。否则输出 -1。
注意：输出的最后一个数后面不要带空格。
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	//建图，同时统计入度
	vector<vector<int>> graph(n+1);
	vector<int> indegree(n + 1);
	while (m--)
	{
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		indegree[v]++;
	}
	vector<int> ans;
	//队列收集入度为0的点
	queue<int> qe;
	//cnt统计数量
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (indegree[i] == 0)
		{
			qe.push(i);
		}
	}
	while (!qe.empty())
	{
		int tmp = qe.front();
		qe.pop();
		cnt++;
		ans.emplace_back(tmp);
		//处理出度
		for (auto i : graph[tmp])
		{
			indegree[i]--;
			if (indegree[i] == 0)
			{
				qe.push(i);
			}
		}
	}
	if (cnt == n) {
		for (int i = 0; i < n; i++) {
			cout << ans[i];
			if (i != n - 1) cout << ' ';
		}
	}
	else {
		cout << -1;
	}
	return 0;
}