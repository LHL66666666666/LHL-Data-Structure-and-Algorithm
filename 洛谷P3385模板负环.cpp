/*
给定一个 n 个点的有向图，请求出图中是否存在从顶点 1 出发能到达的负环。
负环的定义是：一条边权之和为负数的回路。

输入格式
输入的第一行是一个整数 T，表示测试数据的组数。对于每组数据的格式如下：
第一行有两个整数，分别表示图的点数 n 和接下来给出边信息的条数 m。
接下来 m 行，每行三个整数 u, v, w。
若 w ≥ 0，则表示存在一条从 u 至 v 边权为 w 的边，还存在一条从 v 至 u 边权为 w 的边。
若 w < 0，则只表示存在一条从 u 至 v 边权为 w 的边。

输出格式
对于每组数据，输出一行一个字符串，若所求负环存在，则输出 YES，否则输出 NO。
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int T, n, m;
int ui, vi, wi;
constexpr int INF = 0x3f3f3f3f;
//dis数组记录最短路径
vector<int> dis;
//vis数组记录是否在队列中
vector<int> vis;
//cnt数组记录源点到这个点最短路径的边数(OIWiKi写法)
vector<int> cnt;
bool spfa(vector<vector<pair<int, int>>>& g)
{
    //Bellman-Ford+SPFA
    queue<int> qe;
    dis.assign(n + 1, INF);
    vis.assign(n + 1, 0);
    cnt.assign(n + 1, 0);
    //源点入队列
    //注意进出队列和vis数组的操作始终绑定
    dis[1] = 0;
    qe.push(1);
    vis[1] = 1;
    while (!qe.empty())
    {
        int u = qe.front();
        qe.pop();
        vis[u] = 0;
        for (auto& i : g[u])
        {
            int v = i.first, w = i.second;
            //判断能否松弛
            if (dis[v] > w + dis[u])
            {
                //松弛
                dis[v] = w + dis[u];
                //最短路的边数更新
                //只要发生了松弛，说明之前记录的路径不是最短的，
                //那么对应的边数记录也应该被新的、更优的路径取代
                //我们只需要关注源点到这个位置最短路的边数
                //cnt记录的是当前最短路径的边数
                //如果存在负环，可以有无限多的边，只需一直更新最短路的边数即可
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n)
                {
                    return true;
                }
                //如果已经在队列，不需要再次入队
                if (!vis[v])
                {
                    qe.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        //建图
        vector<vector<pair<int, int>>> g(n + 1);
        while (m--)
        {
            cin >> ui >> vi >> wi;
            if (wi >= 0)
            {
                g[ui].push_back({ vi,wi });
                g[vi].push_back({ ui,wi });
            }
            else g[ui].push_back({ vi,wi });
        }
        bool flag = spfa(g);
        if (flag) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}