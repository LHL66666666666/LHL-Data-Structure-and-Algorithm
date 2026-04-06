#include <vector>
#include <iostream>
#include <cstring>
using namespace std;
//链式前向星建图
//本质上是用链表实现的邻接表
//使用数组模拟链表，模拟头插法
const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
//为了处理无向图，我们将将边的数量直接开成两倍，因为无向图一条边要加入两条新的
//head数组下标是点号，数值存储这个点头部边号
int head[MAXN];
//next数组下标是边号，存储这一条边下一个去往的边，0为结束
int next1[MAXM];
//to数组下标是边号，存储这条边去往的点
int to[MAXM];
//weight数组下标是边号，存储边权
int weight[MAXM];
//边号
int cnt;
//初始化
void build(int n)
{
	//cnt=1就相当于清空了next,to,weight三个数组
	cnt = 1;
	memset(head, 0, sizeof(head));
}
//加边的函数
void addEdge(int u, int v, int w)
{
	//三个参数意思是从u点指向v点，边权为w的有向边
	//模拟链表头插法来了
	//目前要插入的边是cnt号边，cnt边作为新的u的头部边
	//我们先将cnt号边的头部边设置为老头部边
	next1[cnt] = head[u];
	//设置to，cnt边去往的点是v
	to[cnt] = v;
	//设置边权
	weight[cnt] = w;
	//将点u的新头部设置为cnt
	head[u] = cnt;
	//更新cnt
	++cnt;

}
//建立有向图，带权图
void directgraph(vector<vector<int>>& edges)
{
	for (auto& edge : edges)
	{
		addEdge(edge[0], edge[1], edge[2]);
	}
}
//建立无向图，带权图
void undirectgraph(vector<vector<int>>& edges)
{
	for (auto& edge : edges)
	{
		addEdge(edge[0], edge[1], edge[2]);
		addEdge(edge[1], edge[0], edge[2]);
	}
}
//遍历
void traversal(int n)
{
	//遍历每一个点，沿着每一个点的头部边遍历直到头部边是0(结束位置)
	for (int i = 1; i <= n; i++)
	{
		//模拟链表的遍历
		for (int ei = head[i]; ei > 0; ei = next1[ei])
		{
			cout << i << ' ' << to[ei] << ' ' << weight[ei] << ' ';
		}
		cout << '\n';
	}
}