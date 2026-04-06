#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
int n, m;
vector<int> val;
vector<vector<int>> g;
vector<vector<vector<int>>> dp;
//dp[i][j][k]表示以i节点为头节点，在前j个节点进行选择，一共选k个元素，得到的最大价值
//注意，这里k个元素包含i节点，且要求选择的必须连续
int dfs(int i, int j, int k)
{
	//base case
	if (k == 0)
	{
		return 0;
	}
	if (j == 0 || k == 1)
	{
		return val[i];
	}
	if(dp[i][j][k] != -1)
	{
		return dp[i][j][k];
	}
	//我们来到前j个节点，就第j个节点要选/不要选进行讨论
	//不选j
	int ans = dfs(i, j - 1, k);
	//选j
	//枚举j中选择几个
	int v = g[i][j - 1];
	for (int s = 1; s < k; s++)
	{
		ans = max(ans, dfs(i, j - 1, k - s) + dfs(v,g[v].size(), s));
	}
	dp[i][j][k] = ans;
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	val.resize(n + 1);
	g.resize(n + 1);
	val[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		int u;
		cin >> u;
		cin >> val[i];
		g[u].emplace_back(i);
	}
	//0号节点是最初的头节点，必须要，获得0号节点得到的价值为0
	dp.assign(n + 1, vector<vector<int>>(n + 1, vector<int>(m + 5, -1)));
	cout << dfs(0, g[0].size(), m + 1);
	return 0;
}
//这种做法的时间复杂度为O(n*平均子树节点个数*m*m),因为经历了m的枚举
/*
每门课最多只有一门先修课的特点，与有根树中一个点最多只有一个父亲结点的特点类似．
因此可以想到根据这一性质建树，从而所有课程组成了一个森林的结构．
为了方便起见，我们可以新增一门 0 学分的课程（设这个课程的编号为 0），
0作为所有无先修课课程的先修课，这样我们就将森林变成了一棵以 0 号课程为根的树．
我们设 f(u,i,j) 表示以 u 号点为根的子树中，已经遍历了 u 号点的前 i 棵子树，选了 j 门课程的最大学分．
转移的过程结合了树形 DP 和 背包 DP 的特点，我们枚举 u 点的每个子结点 v，
同时枚举以 v 为根的子树选了几门课程，将子树的结果合并到 u 上．
*/