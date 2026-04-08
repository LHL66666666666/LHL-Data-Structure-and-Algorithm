#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
int n;
vector<vector<int>> g;
vector<int> h;
vector<int> degree;
//对于每个节点，选择这个节点和不选择这个节点的最大价值都需要知道
struct node {
	//val1表示不选择这个节点的最大价值，val2表示选这个节点的最大价值
	int val1, val2;
};
node dfs(int cur)
{
	if (g[cur].empty())
	{
		node x;
		x.val1 = 0, x.val2 = h[cur];
		return x;
	}
	int res1 = 0, res2 = 0;
	for (auto& e : g[cur])
	{
		auto v = dfs(e);
		res1 += max(v.val1, v.val2);
		res2 += v.val1;
	}
	node ret;
	ret.val1 = res1, ret.val2 = res2 + h[cur];
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	h.resize(n+1);
	g.resize(n + 1);
	degree.resize(n + 1);
	for (int i = 1; i <= n; i++) cin >> h[i];
	for (int _ = 1; _ < n; _++)
	{
		int l, k;
		cin >> l >> k;
		g[k].emplace_back(l);
		degree[l]++;
	}
	int root = 0;
	for (int i = 1; i <= n; i++)
	{
		if (degree[i] == 0)
		{
			root = i;
		}
	}
	auto ans = dfs(root);
	cout<<max(ans.val1,ans.val2)<<'\n';
	return 0;
}