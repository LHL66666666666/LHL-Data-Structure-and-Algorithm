#include <vector>
#include <queue>
#include <deque>
using namespace std;
auto cmp = [](const vector<int>& a, const vector<int>& b)
    {
        return a[2] > b[2];
    };
class Solution {
public:
    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
        int n = charge.size();
        //建图,注意是无向图,边权全都是非负
        vector<vector<pair<int, int>>> g(n);
        for (auto& i : paths)
        {
            int u = i[0], v = i[1], w = i[2];
            g[u].push_back({ v,w });
            g[v].push_back({ u,w });
        }
        //实际上，在我们建立的图的模型：图上的点不是实际的点，图上的点+当前电量状态才是真实的点
        //vis开二维,第一维是点的编号,第二维是电量状态
        vector<vector<int>> vis(n, vector<int>(cnt + 1));
        //同样地:dis表示距离也开二维,与vis含义相同，表示到达当前状态的时间开销
        vector<vector<int>> dis(n, vector<int>(cnt + 1, INT_MAX));
        //接下来就是找最短路，
        //关键点：我们虚拟化一种路径当电量未满时：我们定义从一个城市该电量 到 这个城市该电量+1 为一条边
        //边权为在本城市充点1h的花费
        //优先队列存三个参数：点的编号，当前电量，截至目前的时间开销，表示一个状态
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        //源点入队
        pq.push({ start,0,0 });
        dis[start][0] = 0;
        while (!pq.empty())
        {
            int u = pq.top()[0];
            int power = pq.top()[1];
            int cost = pq.top()[2];
            pq.pop();
            if (vis[u][power]) continue;
            vis[u][power] = 1;
            if (u == end)
            {
                return cost;
            }
            //尝试两种情况(讨论下一种状态)
            //情况1.如果电未满，尝试到自己的电量+1状态
            if (power < cnt)
            {
                if (!vis[u][power + 1] && cost + charge[u] < dis[u][power + 1])
                {
                    dis[u][power + 1] = cost + charge[u];
                    pq.push({ u,power + 1,dis[u][power+1]});
                }
            }
            //情况2.尝试走到自己联通的位置
            //尝试联通的每条边找最短路
            for (auto& i : g[u])
            {
                int v = i.first;
                //到v这个城市的距离
                int w = i.second;
                //注意，要有足够的电量到下一个城市，这里用一个新变量记录走到这个城市还剩多少电量
                int rest = power - w;
                if (rest >= 0 && !vis[v][rest] && w + dis[u][power] < dis[v][rest])
                {
                    dis[v][rest] = w + dis[u][power];
                    pq.push({ v,rest,dis[v][rest] });
                }
            }
        }
        return -1;
    }
};