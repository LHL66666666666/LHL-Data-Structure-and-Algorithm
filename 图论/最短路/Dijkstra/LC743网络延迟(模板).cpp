#include <vector>
#include <queue>
#include <deque>
using namespace std;
auto cmp = [](const pair<int, int>& a, const pair<int, int>& b)
    {
        return a.second > b.second;
    };
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        //邻接表建图，普通堆优化dijkstra
        vector<vector<pair<int,int>>> g(n + 1);
        for (auto& edge : times)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            g[u].push_back({ v, w });
        }
        //dis数组记录距离
        vector<int> dis(n + 1, INT_MAX);
        //vis数组记录访问过
        vector<int> vis(n + 1);
        //优先队列存两个参数:当前点，到源点的距离
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> pq(cmp);
        //加入源点
        dis[k] = 0;
        pq.push({ k,0 });
        while (!pq.empty())
        {
            int u = pq.top().first;
            pq.pop();
            //细节1：每次弹出时才标记
            if (vis[u]) {
                continue;
            }
            vis[u] = 1;
            for (auto& i : g[u])
            {
                int v = i.first;
                int w = i.second;
                //松弛操作，寻找最小值的可能性
                if (w + dis[u] < dis[v])
                {
                    dis[v] = w + dis[u];
                    pq.push({ v,dis[v] });
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            if (dis[i] == INT_MAX)
            {
                return -1;
            }
            ans = max(ans, dis[i]);
        }
        return ans;
    }
};