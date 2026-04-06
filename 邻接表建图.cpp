#include <vector>
#include <iostream>
using namespace std;
//邻接表法
const int MAXN = 105;
vector<vector<pair<int, int>>> graph;
//初始化
void build()
{
	graph.clear();
	graph.resize(MAXN + 1);
}
//建立有向图，带权图
void directgraph(vector<vector<int>>& edges)
{
	for (auto& edge : edges)
	{
		graph[edge[0]].push_back({ edge[1],edge[2] });
	}
}
//建立无向图，带权图
void undirectgraph(vector<vector<int>>& edges)
{
	for (auto& edge : edges)
	{
		graph[edge[0]].push_back({ edge[1],edge[2] });
		graph[edge[1]].push_back({ edge[0],edge[2] });
	}
}
//遍历
void traversal(int n)
{
	//从1号点到n号点
	for (int i = 1; i <= n; i++)
	{
		for (auto& edge : graph[i])
		{
			cout << edge.first << ' ' << edge.second << ' ';
		}
	}
}