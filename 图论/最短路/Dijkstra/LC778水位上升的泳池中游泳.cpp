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
    //grid[i][j] 中每个值均无重复
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<int> dis(n * m + 1, INT_MAX);
        vector<int> vis(n * m + 1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        //源点入队
        pq.push({ 0,grid[0][0]});
        dis[0] = grid[0][0];
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
                if (xn >= 0 && xn < n && yn >= 0 && yn < m && !vis[xn * m + yn])
                {
                    if (dis[xn * m + yn] > max(d1, grid[xn][yn]))
                    {
                        dis[xn * m + yn] = max(d1, grid[xn][yn]);
                        pq.push({ xn * m + yn,max(d1, grid[xn][yn]) });
                    }
                }
            }
        }
        return dis[n * m - 1];
    }
};