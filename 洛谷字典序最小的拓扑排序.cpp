/*
题目描述
有向无环图上有n个点，m条边。求这张图字典序最小的拓扑排序的结果。
字典序最小指希望排好序的结果中，比较靠前的数字尽可能小。

输入格式
第一行是用空格隔开的两个整数n和m，表示n个点和m条边。
接下来是m行，每行用空格隔开的两个数u和v，表示有一条从u到v的边。

输出格式
输出一行，拓扑排序的结果，数字之间用空格隔开
*/
#include <vector>
#include <deque>
#include <queue>
#include <iostream>
using namespace std;
int head[100005];
int next1[100005];
int to[100005];
int indegree[100005];
int cnt;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	cnt = 1;
	//建图,使用链式前向星防止卡空间
	//同时统计入度
	while (m--)
	{
		int u, v;
		cin >> u >> v;
		//模拟链表
		next1[cnt] = head[u];
		to[cnt] = v;
		head[u] = cnt;
		++cnt;
		indegree[v]++;
	}
	//使用小根堆来存储每次入度为的点，这样每次弹出堆顶元素就保证了最小的字典序
	priority_queue<int, vector<int>,greater<int>> pq;
	for (int i = 1; i <= n; i++)
	{
		if (indegree[i] == 0)
		{
			pq.push(i);
		}
	}
	vector<int> ans;
	while (!pq.empty())
	{
		int tmp = pq.top();
		pq.pop();
		ans.emplace_back(tmp);
		for (int ei = head[tmp]; ei > 0; ei = next1[ei])
		{
			indegree[to[ei]]--;
			if (indegree[to[ei]] == 0)
			{
				pq.push(to[ei]);
			}
		}
	}
	for (auto i : ans)
	{
		cout << i << ' ';
	}
	cout << '\n';
	return 0;
}
