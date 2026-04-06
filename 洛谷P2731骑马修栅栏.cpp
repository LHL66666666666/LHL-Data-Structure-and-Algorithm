#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
int m;
vector<vector<int>> g(501);
vector<int> cnt(501);
vector<int> ans;
int degree[505];
//针对无向图，我们额外加一个二维数组来处理删边
int exist[505][505];
void dfs(int cur)
{
	for (int i = cnt[cur]; i < g[cur].size(); i = cnt[cur])
	{
		//如果有边(没被删掉)
		if (exist[cur][g[cur][i]])
		{
			//删边
			exist[cur][g[cur][i]]--;
			exist[g[cur][i]][cur]--;
			//这边注意进递归之前要先进行这一步cnt[cur] = i + 1;更新经过的边
			//不然会重复访问一条边，这一步也是在删边！！
			cnt[cur] = i + 1;
			dfs(g[cur][i]);
		}
		else cnt[cur] = i + 1;
		
	}
	ans.emplace_back(cur);
}
int main()
{
	cin >> m;
	while (m--)
	{
		int u, v;
		cin >> u >> v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
		//有重边！！！
		exist[u][v]++;
		exist[v][u]++;
		degree[u]++;
		degree[v]++;
	}
	for (int i = 1; i <= 500; i++)
	{
		sort(g[i].begin(), g[i].end());
	}
	//无向图，找到奇点，然后从起始位置出发
	//如果找不到奇点那么就说明有欧拉回路，从1开始即可
	int s1 = INF;
	for (int i = 1; i <= 500; i++)
	{
		if (degree[i] & 1)
		{
			s1 = min(s1, i);
		}
	}
	if (s1 == INF)
	{
		//最小的点不一定是1，太坑了！！！
		for (int i = 1; i <= 500; i++)
		{
			if (degree[i] != 0)
			{
				s1 = i;
				break;
			}
		}
	}
	dfs(s1);
	reverse(ans.begin(), ans.end());
	for (auto& i : ans) cout << i << '\n';
	return 0;
}