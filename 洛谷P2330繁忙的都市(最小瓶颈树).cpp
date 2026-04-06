/*
城市 C 是一个非常繁忙的大都市，城市中的道路十分的拥挤，于是市长决定对其中的道路进行改造。城市 C 的道路是这样分布的：城市中有 n 个交叉路口，有些交叉路口之间有道路相连，两个交叉路口之间最多有一条道路相连接。这些道路是双向的，且把所有的交叉路口直接或间接的连接起来了。每条道路都有一个分值，分值越小表示这个道路越繁忙，越需要进行改造。但是市政府的资金有限，市长希望进行改造的道路越少越好，于是他提出下面的要求：

改造的那些道路能够把所有的交叉路口直接或间接的连通起来。
在满足要求 1 的情况下，改造的道路尽量少。
在满足要求 1、2 的情况下，改造的那些道路中分值最大的道路分值尽量小。
任务：作为市规划局的你，应当作出最佳的决策，选择哪些道路应当被修建。

输入格式
第一行有两个整数 n,m 表示城市有 n 个交叉路口，m 条道路。

接下来 m 行是对每条道路的描述，u,v,c 表示交叉路口 u 和 v 之间有道路相连，分值为 c。

输出格式
两个整数 s,max，表示你选出了几条道路，分值最大的那条道路的分值是多少。
*/
#include <algorithm>
#include <iostream>
#include <climits>
using namespace std;
int father[305];
struct node {
	int u, v, c;
}e[8005];
void build(int n)
{
    for (int i = 0; i <= n; i++)
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
    father[find(x)] = find(y);
}
bool cmp(node x, node y)
{
    return x.c < y.c;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
    build(n);
    for (int i = 0; i < m; i++)
    {
        cin >> e[i].u >> e[i].v >> e[i].c;
    }
    sort(e, e + m, cmp);
    int ans = INT_MIN;
    for (int i = 0; i < m; i++)
    {
        int u = e[i].u;
        int v = e[i].v;
        if (find(u) != find(v))
        {
            unite(u, v);
            ans = max(ans, e[i].c);
        }
    }
    //边数一定是n-1条，保证联通的最小生成树
    cout << n - 1 << ' ' << ans << '\n';

	return 0;
}