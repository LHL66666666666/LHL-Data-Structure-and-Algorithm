/*
洛谷P3366[模板]最小生成树
如题，给出一个无向图，求出最小生成树，如果该图不连通，则输出 orz。

输入格式
第一行包含两个整数 N,M，表示该图共有 N 个结点和 M 条无向边。

接下来 M 行每行包含三个整数Xi,Yi,Zi，表示有一条长度为Zi的无向边连接结点Xi,Yi
输出格式
如果该图连通，则输出一个整数表示最小生成树的各边的长度之和。如果该图不连通则输出 orz。
*/
//Kruskal算法的基本思想是从小到大加入边，是个贪心算法
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m;
const int MAXN = 5005;
int father[MAXN];
void build(int n)
{
	for (int i = 1; i <= n; i++)
	{
		father[i] = i;
	}
}
int find(int x)
{
	if (father[x] != x)
	{
		father[x] = find(father[x]);
	}
	return father[x];
}
void unite(int x, int y)
{
	father[find(x)] = find(y);
}
bool cmp(vector<int>& a, vector<int>& b)
{
	return a[2] < b[2];
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	//Kruskal算法无需建图，按照边权排序来计算即可，需要并查集
	build(n);
	vector<vector<int>> edge(m, vector<int>(3));
	for (int i = 0; i < m; i++)
	{
		cin >> edge[i][0] >> edge[i][1] >> edge[i][2];
	}
	sort(edge.begin(), edge.end(), cmp);
	ll ans = 0;
	int cnt = 0;
	for (int i = 0; i < m; i++)
	{
		int u = edge[i][0];
		int v = edge[i][1];
		if (find(u) != find(v))
		{
			//不在一个集合，需要合并
			cnt++;
			ans += edge[i][2];
			unite(u, v);
		}
	}
	if (cnt == n - 1)
	{
		cout << ans << '\n';
	}
	else cout << "orz\n";
	return 0;
}