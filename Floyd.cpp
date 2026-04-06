/*
是用来求任意两个结点之间的最短路的。
复杂度比较高，但是常数小，容易实现（只有三个 for）。
适用于任何图，不管有向无向，边权正负，但是最短路必须存在。（不能有个负环）
如果存在负环，那么我们可以无限地在这个负环上转圈，使得路径变的无穷小，此时再讨论最短路是无意义的
*/
#include <iostream>
const int MAXN = 205;
const int INF = 0x3f3f3f3f;
int distance[MAXN][MAXN];
int dist[MAXN][MAXN];
int n;
//由于Floyd只能适用于点数较少的图，我们使用邻接矩阵来建图，
//实际上初始化邻接矩阵也可以认为是在初始化distance数组
void floyd()
{
	//O(n^3)
	//关键点：首先枚举作为跳板的点
	//状态转移方程：dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j])
	for (int bridge = 0; bridge < n; bridge++)
	{
		//再枚举每一对点，看看是否让距离变得更小
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (distance[i][j] > distance[i][bridge] + distance[bridge][j])
				{
					distance[i][j] = distance[i][bridge] + distance[bridge][j];
				}
			}
		}
	}
}

void floyd2() {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			if (dist[i][k] == INF) continue;  // 优化：跳过无效的中间点
			for (int j = 0; j < n; j++) {
				if (dist[k][j] == INF) continue;  // 优化：跳过无效的终点
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
}
//如果要输出最短路径(输出沿途上的每个点)，使用类似链式前向星的思路，模拟链表
//一个数组p[][]来记录
//第一维参数表示起点，第二维参数表示去往的点
int p[MAXN][MAXN];
void init3()
{
	for (int i = 0; i < MAXN; i++)
	{
		for (int j = 0; j < MAXN; j++)
		{
			distance[i][j] = INF;
			p[i][j] = j;	//初始时，i的下一个点是j（直接走）
			if (i == j) distance[i][j] = 0;
		}
	}
}
void floyd3()
{
	//O(n^3)
	//关键点：首先枚举作为跳板的点
	//状态转移方程：dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j])
	for (int bridge = 0; bridge < n; bridge++)
	{
		//再枚举每一对点，看看是否让距离变得更小
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (distance[i][j] > distance[i][bridge] + distance[bridge][j])
				{
					distance[i][j] = distance[i][bridge] + distance[bridge][j];
					//关键：更新路径，i到j的下一个点 = i到k的下一个点(也就是k)
					p[i][j] = p[i][bridge];
				}
			}
		}
	}
}
// 打印从u到v的最短路径
void print_path3(int u, int v)
{
	if (dist[u][v] == INF) {
		std::cout << "No path from " << u << " to " << v << '\n';
		return;
	}
	std::cout << "Path from " << u << " to " << v << ": ";
	std::cout << u;

	int cur = u;
	while (cur != v) {
		cur = p[cur][v];
		std::cout << " -> " << cur;
	}
	std::cout << " (distance = " << dist[u][v] << ")" << '\n';
}
