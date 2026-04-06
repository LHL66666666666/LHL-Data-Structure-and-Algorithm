#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
int n, m;
vector<int> val0;
vector<int> val;
vector<vector<int>> g;
vector<int> dfn;
vector<int> siz;
int cnt;
void dfs(int u,int fa)
{
	dfn[u] = ++cnt;
	for (auto& v : g[u])
	{
		if (v != fa) {
			dfs(v, u);
			siz[dfn[u]] += siz[dfn[v]];
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	cnt = 0;
	val0.resize(n + 5);
	val.resize(n + 5);
	g.resize(n + 1);
	dfn.resize(n + 5);
	siz.assign(n + 5, 1);
	val[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		int u;
		cin >> u;
		cin >> val0[i];
		g[u].emplace_back(i);
	}
	//dfn序我们增加一个最后的n+2号节点，用于边界处理
	dfs(0, -1);
	for (int i = 0; i <= n + 1; i++)
	{
		val[dfn[i]] = val0[i];
	}
	val[n + 2] = 0;
	siz[n + 2] = 0;
	//0号节点是最初的头节点，必须要，获得0号节点得到的价值为0
	//我们先使用dfn序，对节点进行重排，保证父节点的编号小于子节点的
	//定义dp[i][j]表示来到i号节点(dfn序下)，在满足要求(假设这些点作为头节点，在最后能连接到一起)的前提下，
	//选j个，得到的最大价值
	vector<vector<int>> dp(n + 5, vector<int>(m + 2));
	for (int i = n + 1; i >= 1; i--)
	{
		for (int j = 1; j <= m + 1; j++)
		{
			//两种情况:1.不要i位置的元素，那么i的子树的元素都不能要
			dp[i][j] = dp[i + siz[i]][j];
			//2.要i位置的元素，就可以要它子树的元素
			dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + val[i]);
		}
	}
	cout << dp[1][m + 1] << '\n';
	return 0;
}
//通过这种有效结构的定义，优化到O(n*m)