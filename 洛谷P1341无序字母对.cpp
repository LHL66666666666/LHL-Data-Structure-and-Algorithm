#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
int n;
int degree[52];
int del[52];
//这边防止出现重边，不得不防
int vis[52][52];
vector<int> ans;
void dfs(int cur,vector<vector<int>>& g)
{
	for (int i = del[cur]; i < g[cur].size(); i = del[cur])
	{
		int v = g[cur][i];
		if (vis[cur][v]>0)
		{
			vis[cur][v]--;
			vis[v][cur]--;
			del[cur] = i + 1;
			dfs(v, g);
		}
		else del[cur] = i + 1;
	}
	//没边了，进栈
	ans.emplace_back(cur);
}
//DSU来判连通性
int father[60];
void build()
{
	for (int i = 0; i < 60; i++)
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
	father[find(y)] = find(x);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	build();
	vector<vector<int>> g(52);
	set<int> s;
	while (n--)
	{
		string s1;
		cin >> s1;
		//看作图上的点，只有联通才能实现n+1个字母的构造
		//冷知识：'A'比'a'ASCII码更小
		int n0, n1;
		if (s1[0] >= 'a' && s1[0] <= 'z')
		{
			n0 = s1[0] - 'a' + 26;
		}
		else n0 = s1[0] - 'A';
		if (s1[1] >= 'a' && s1[1] <= 'z')
		{
			n1 = s1[1] - 'a' + 26;
		}
		else n1 = s1[1] - 'A';
		//建无向图
		g[n0].emplace_back(n1);
		g[n1].emplace_back(n0);
		degree[n1]++;
		degree[n0]++;
		vis[n1][n0]++;
		vis[n0][n1]++;
		s.insert(n1);
		s.insert(n0);
		unite(n1, n0);
	}
	//要求按照字典序尽量小的，排序
	for (int i = 0; i < 52; i++)
	{
		if (!g[i].empty())
		{
			sort(g[i].begin(), g[i].end());
		}
	}
	//检查联通
	int cnt = 0;
	for (int i = 0; i < 52; i++)
	{
		if (s.count(i) && i == find(i))
		{
			++cnt;
		}
	}
	if (cnt > 1)
	{
		cout << "No Solution\n";
		return 0;
	}
	//找奇点,要么没有奇点，要么有两个
	int cnt1 = 0;
	int start = INF;
	for (int i = 0; i < 52; i++)
	{
		if (s.count(i) && (degree[i] & 1))
		{
			start = min(start, i);
			cnt1++;
		}
	}
	if (cnt1 != 0 && cnt1 != 2)
	{
		cout << "No Solution\n";
		return 0;
	}
	if (start == INF)
	{
		auto it = s.begin();
		start = *it;
	}
	dfs(start,g);
	reverse(ans.begin(), ans.end());
	for (auto& i : ans)
	{
		if (i >= 0 && i < 26) cout << (char)(i + 'A');
		else cout << (char)(i - 26 + 'a');
	}
	cout << '\n';
	return 0;
}
//判断联通也可以不使用并查集，可以最后判断ans中点的个数，
//点的个数-1就是经过的边数，判断这个边数是否等于n即可
//改进版本：
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
int n;
int degree[52];
int del[52];
//这边防止出现重边，不得不防
int vis[52][52];
vector<int> ans;
void dfs(int cur, vector<vector<int>>& g)
{
	for (int i = del[cur]; i < g[cur].size(); i = del[cur])
	{
		int v = g[cur][i];
		if (vis[cur][v] > 0)
		{
			vis[cur][v]--;
			vis[v][cur]--;
			del[cur] = i + 1;
			dfs(v, g);
		}
		else del[cur] = i + 1;
	}
	//没边了，进栈
	ans.emplace_back(cur);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	vector<vector<int>> g(52);
	set<int> s;
	for (int i=1;i<=n;i++)
	{
		string s1;
		cin >> s1;
		//看作图上的点，只有联通才能实现n+1个字母的构造
		//冷知识：'A'比'a'ASCII码更小
		int n0, n1;
		if (s1[0] >= 'a' && s1[0] <= 'z')
		{
			n0 = s1[0] - 'a' + 26;
		}
		else n0 = s1[0] - 'A';
		if (s1[1] >= 'a' && s1[1] <= 'z')
		{
			n1 = s1[1] - 'a' + 26;
		}
		else n1 = s1[1] - 'A';
		//建无向图
		g[n0].emplace_back(n1);
		g[n1].emplace_back(n0);
		degree[n1]++;
		degree[n0]++;
		vis[n1][n0]++;
		vis[n0][n1]++;
		s.insert(n1);
		s.insert(n0);
	}
	//要求按照字典序尽量小的，排序
	for (int i = 0; i < 52; i++)
	{
		if (!g[i].empty())
		{
			sort(g[i].begin(), g[i].end());
		}
	}
	//找奇点,要么没有奇点，要么有两个
	int cnt1 = 0;
	int start = INF;
	for (int i = 0; i < 52; i++)
	{
		if (s.count(i) && (degree[i] & 1))
		{
			start = min(start, i);
			cnt1++;
		}
	}
	if (cnt1 != 0 && cnt1 != 2)
	{
		cout << "No Solution\n";
		return 0;
	}
	if (start == INF)
	{
		auto it = s.begin();
		start = *it;
	}
	dfs(start, g);
	reverse(ans.begin(), ans.end());
	if (ans.size() - 1 != n)
	{
		cout << "No Solution\n";
		return 0;
	}
	for (auto& i : ans)
	{
		if (i >= 0 && i < 26) cout << (char)(i + 'A');
		else cout << (char)(i - 26 + 'a');
	}
	cout << '\n';
	return 0;
}