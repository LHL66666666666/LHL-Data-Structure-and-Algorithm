#include <iostream>
#include <queue>
#include<vector>
#include <cstring>
const int MOD = 80112002;
using namespace std;
typedef long long ll;
int head[500005];
int next1[500005];
int to[500005];
int indegree[500005];
//数组line表示路径数量
int line[500005];
int idx;
void build(int n)
{
	idx = 1;
	for (int i = 1; i <= n; i++)
	{
		head[i] = 0;
		next1[i] = 0;
		to[i] = 0;
		indegree[i] = 0;
		//注意line数组初始化为0
		line[i] = 0;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	build(n);
	while (m--)
	{
		int a, b;
		cin >> a >> b;
		//使用链式前向星建图
		next1[idx] = head[a];
		to[idx] = b;
		head[a] = idx;
		++idx;
		indegree[b]++;
	}
	//建完图开始拓扑排序
	ll ans = 0;
	queue<int> qe;
	for (int i = 1; i <= n; i++)
	{
		//只有最底层的，也就是一开始入度为0的点，line路径数量初始化为1，用于后续累加
		if (indegree[i] == 0)
		{
			line[i] = 1;
			qe.push(i);
		}
	}
	while (!qe.empty())
	{
		int tmp = qe.front();
		qe.pop();
		//判断如果这是一条链的最后一个节点那么统计答案
		if (head[tmp] == 0)
		{
			ans = (ans + line[tmp]) % MOD;
		}
		//消除入度影响，同时累积路径
		for (int ei = head[tmp]; ei != 0; ei = next1[ei])
		{
			//注意这里是line[to[ei]]，ei表示边，to[ei]表示去往的点，去往的点要被消除影响
			line[to[ei]] = (line[tmp] + line[to[ei]]) % MOD;
			indegree[to[ei]]--;
			if (indegree[to[ei]] == 0)
			{
				qe.push(to[ei]);
			}
		}
	}
	cout << ans << '\n';
	return 0;
}