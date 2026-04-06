#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
constexpr int INF = 0x3f3f3f3f;
typedef long long ll;
int n;
vector<int> ans;
int del[26];
//这里dfs多加一个参数id，表示上一个搜到的字符串，
//一旦没下一个可搜，开始回溯，把上一个搜到的入栈
//特别地，第一个搜的时候我们将id定义为-1，表示前面没有
void dfs(int cur, vector<vector<pair<int, int>>>& g, int id)
{
	for (int i = del[cur]; i < g[cur].size(); i = del[cur])
	{
		int v = g[cur][i].first;
		int new_id = g[cur][i].second;
		del[cur] = i + 1;
		dfs(v, g, new_id);
	}
	if (id != -1) ans.push_back(id);
}
//分别表示入度,出度
int degree[26][2];
//比较函数，要按照边来排序！！！
bool cmp(const pair<int, int>& a, const pair<int, int>& b)
{
	return a.second < b.second;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	//这是一个有向图
	vector<vector<pair<int,int>>> g(26);
	vector<string> wd;
	for (int i = 0; i < n; i++)
	{
		string ss;
		cin >> ss;
		wd.emplace_back(ss);
	}
	//难点在于如何建图
	//每个单词只能出现一次，我们将每个单词看作边，连接字母(节点)
	//每个点可以出现多次，但是边仅能出现1次
	//这样就变成找欧拉路径
	sort(wd.begin(), wd.end());
	for (int i = 0; i < n; i++)
	{
		int n1 = wd[i].size();
		int u = wd[i][0] - 'a';
		int v = wd[i][n1 - 1] - 'a';
		g[u].push_back({v,i});
		degree[u][1]++;
		degree[v][0]++;
	}
	for (int i = 0; i < 26; i++)
	{
		if (!g[i].empty())
		{
			sort(g[i].begin(), g[i].end(), cmp);
		}
	}
	//找起点和终点
	int start = INF;
	int cnts = 0, cnte = 0;
	//falg=1表示目前所有点入度==出度
	int flag = 1;
	for (int i = 0; i < 26; i++)
	{
		if (degree[i][0] == 0 && degree[i][1] == 0)
		{
			continue;
		}
		if (degree[i][0] - degree[i][1] == 1)
		{
			flag = 0;
			cnte++;
		}
		if (degree[i][0] - degree[i][1] == -1)
		{
			flag = 0;
			cnts++;
			start = i;
		}
	}
	if (!flag && (cnts != 1 && cnte != 1))
	{
		cout << "***\n";
		return 0;
	}
	//如果所有点入度==出度，找一个字典序最小的作为起点
	if (flag)
	{
		for (int i = 0; i < 26; i++)
		{
			if (degree[i][0] != 0)
			{
				start = i;
				break;
			}
		}
	}
	dfs(start,g,-1);
	reverse(ans.begin(), ans.end());
	int nn = ans.size();
	//判联通
	if (nn != n)
	{
		cout << "***\n";
		return 0;
	}
	for (int i = 0; i < nn; i++)
	{
		cout << wd[ans[i]];
		if (i != nn - 1) cout << '.';
	}
	cout << '\n';
	return 0;
}
//思路：
//这个题的思路想出来了，实现上也是对的，但是卡在排序上面，
//排序应该按照每个字符串的字典序从小到大，来确定访问顺序
//构造图的时候，以单词为有向边，字母为顶点。比如单词 abc，就是从顶点 a 指向顶点 c 的边之一。
//当一个单词的首末字母相同时，它就是一个自环。建图完毕后，先判断是否存在欧拉路，再 DFS 寻找字典序最小的欧拉路。