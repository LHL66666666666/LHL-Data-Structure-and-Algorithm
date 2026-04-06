#include <vector>
#include <queue>
#include <deque>
#include <cstdlib>
using namespace std;
auto cmp = [](const pair<int, int>& a, const pair<int, int>& b)
    {
        return a.second > b.second;
    };
class Solution {
public:
    int dx[4] = { 0,0,1,-1 };
    int dy[4] = { 1,-1,0,0 };
    int minimumEffortPath(vector<vector<int>>& heights) {
        //尝试一下BFS+优先队列
        //n*m的二维数组,给每个点(i,j)编号m*i+j
        int n = heights.size();
        int m = heights[0].size();
        //建图
        vector<vector<pair<int, int>>> g(n * m + 1);
        for (int i = 0; i < n * m; i++)
        {
            int x = i / m, y = i % m;
            for (int j = 0; j < 4; j++)
            {
                int xn = x + dx[j];
                int yn = y + dy[j];
                if (xn >= 0 && xn < n && yn >= 0 && yn < m)
                {
                    g[i].push_back({ xn * m + yn,abs(heights[x][y] - heights[xn][yn]) });
                }
            }
        }
        vector<int> dis(n * m + 1, INT_MAX);
        vector<int> vis(n * m + 1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        //源点入队
        pq.push({ 0,0 });
        dis[0] = 0;
        while (!pq.empty())
        {
            int u = pq.top().first;
            int d1 = pq.top().second;
            pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            //剪枝,发现终点直接返回
            if (u == n * m - 1)
            {
                return dis[u];
            }
            for (auto& i : g[u])
            {
                int v = i.first;
                int w = i.second;
                if (dis[v] > max(d1, w))
                {
                    dis[v] = max(d1, w);
                    pq.push({ v,dis[v] });
                }
            }
        }
        return dis[n * m - 1];
    }
};

//优化:实际上不需要建图
class Solution {
public:
    int dx[4] = { 0,0,1,-1 };
    int dy[4] = { 1,-1,0,0 };
    int minimumEffortPath(vector<vector<int>>& heights) {
        //尝试一下BFS+优先队列
        //n*m的二维数组,给每个点(i,j)编号m*i+j
        int n = heights.size();
        int m = heights[0].size();
        vector<int> dis(n * m + 1, INT_MAX);
        vector<int> vis(n * m + 1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        //源点入队
        pq.push({ 0,0 });
        dis[0] = 0;
        while (!pq.empty())
        {
            int u = pq.top().first;
            int d1 = pq.top().second;
            pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            //剪枝,发现终点直接返回
            if (u == n * m - 1)
            {
                return dis[u];
            }
            int x = u / m, y = u % m;
            for (int j = 0; j < 4; j++)
            {
                int xn = x + dx[j];
                int yn = y + dy[j];
                if (xn >= 0 && xn < n && yn >= 0 && yn < m && !vis[xn*m+yn])
                {
                    if (dis[xn * m + yn] > max(d1, abs(heights[x][y] - heights[xn][yn])))
                    {
                        dis[xn * m + yn] = max(d1, abs(heights[x][y] - heights[xn][yn]));
                        pq.push({ xn * m + yn,max(d1, abs(heights[x][y] - heights[xn][yn])) });
                    }
                }
            }
        }
        return dis[n * m - 1];
    }
};