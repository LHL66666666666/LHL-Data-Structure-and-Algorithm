#include <vector>
#include <iostream>
using namespace std;
//邻接矩阵法
const int MAXN = 105;
int graph[MAXN][MAXN];
//初始化
void build()
{
	for (int i = 0; i < MAXN; i++)
	{
		for (int j = 0; j < MAXN; j++)
		{
			graph[i][j] = 0;
		}
	}
}
//建立有向图、带权图
void directgraph(vector<vector<int>>& edges)
{
	//edges数组三个参数：起点，终点，边权
	for (auto& edge : edges)
	{
		graph[edge[0]][edge[1]] = edge[2];
	}
}
//建立无向图，带权图
void undirectgraph(vector<vector<int>>& edges)
{
	for (auto& edge : edges)
	{
		graph[edge[0]][edge[1]] = edge[2];
		graph[edge[1]][edge[0]] = edge[2];
	}
}
//遍历
void traversal(int n)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << graph[i][j] << ' ';
		}
	}
}