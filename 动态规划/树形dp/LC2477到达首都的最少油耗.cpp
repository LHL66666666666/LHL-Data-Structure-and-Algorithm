#include <vector>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
struct node {
    int cnt;
    ll cost;
};
class Solution {
public:
    vector<vector<int>> g;
    vector<int> vis;
    vector<int> degree;
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        int n = roads.size();
        g.resize(n+1);
        vis.resize(n+1);
        degree.resize(n + 1);
        for (int i = 0; i < n; i++)
        {
            int u = roads[i][0], v = roads[i][1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
            degree[u]++;
            degree[v]++;
        }
        //每一个节点最好和父节点合并起来
        //实际上我们可以认为每个节点的车辆是无穷多的
        //使用贡献法
        //实际上，我们可以计算每个节点的贡献
        //对于每个节点，他的子节点对他的贡献就是子节点需要的车的数量*1
        //需要时刻累计人数，计算每个节点上需要几辆车
        ll res = 0;
        vis[0] = 1;
        res = dfs(0, seats).cost;
        return res;
    }
    node dfs(int u,int seats)
    {
        if (u!=0 && degree[u]==1)
        {
            node x;
            x.cnt = 1;
            x.cost = 1;
            return x;
        }
        node ret;
        ll cost = 0;
        int cnt = 1;
        for (auto& v : g[u])
        {
            if (!vis[v])
            {
                vis[v] = 1;
                auto to = dfs(v, seats);
                cnt += to.cnt;
                cost += to.cost;
            }
        }
        if (u!=0) cost += (cnt + seats - 1) / seats;
        ret.cost = cost;
        ret.cnt = cnt;
        return ret;
    }
};