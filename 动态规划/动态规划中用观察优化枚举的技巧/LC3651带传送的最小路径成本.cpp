#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    const vector<int> dx = { 0,1 };
    const vector<int> dy = { 1,0 };
    int n, m;
    vector<vector<vector<int>>> dp;
    int dfs(int x, int y, int t, vector<vector<int>>& g)
    {
        if (x == n - 1 && y == m - 1)
        {
            return 0;
        }
        if (dp[x][y][t] != -1) return dp[x][y][t];
        int ans = 0;
        //普通移动
        int can1 = INF;
        for (int i = 0; i < 2; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < n && ny < m)
            {
                can1 = min(can1, dfs(nx, ny, t, g) + g[nx][ny]);
            }
        }
        //传送
        int can2 = INF;
        if (t > 0)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (i == x && j == y) continue;
                    if (g[i][j] <= g[x][y])
                    {
                        can2 = min(can2, dfs(i, j, t - 1, g));
                    }
                }
            }
        }
        ans = min(can1, can2);
        dp[x][y][t] = ans;
        return ans;
    }
    int minCost(vector<vector<int>>& grid, int k) {
        //n*m的数组
        n = grid.size(), m = grid[0].size();
        dp.assign(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, -1))); 
        return dfs(0, 0, k, grid);
    }
};

//改成严格位置依赖的dp
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    const vector<int> dx = { 0,1 };
    const vector<int> dy = { 1,0 };
    int n, m;
    vector<vector<vector<int>>> dp;
    int minCost(vector<vector<int>>& grid, int k) {
        //n*m的数组
        n = grid.size(), m = grid[0].size();
        dp.assign(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, 0)));
        //base case
        for (int t = 0; t <= k; t++)
        {
            dp[n - 1][m - 1][t] = 0;
        }
        //另一base case,t=0的情况下，无传送
        for (int x = n - 1; x >= 0; x--)
        {
            for (int y = m - 1; y >= 0; y--)
            {
                if (x == n - 1 && y == m - 1) continue;
                int can1 = INF;
                for (int i = 0; i < 2; i++)
                {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < n && ny < m)
                    {
                        can1 = min(can1, dp[nx][ny][0]+grid[nx][ny]);
                    }
                }
                dp[x][y][0] = can1;
            }
        }
        //下面的每一层都依赖于上面一层
        for (int t = 1; t <= k; t++)
        {
            for (int x = n - 1; x >= 0; x--)
            {
                for (int y = m - 1; y >= 0; y--)
                {
                    if (x == n - 1 && y == m - 1) continue;
                    //向右/向下移动
                    int can1 = INF;
                    for (int i = 0; i < 2; i++)
                    {
                        int nx = x + dx[i], ny = y + dy[i];
                        if (nx < n && ny < m)
                        {
                            can1 = min(can1, dp[nx][ny][t] + grid[nx][ny]);
                        }
                    }
                    //传送
                    int can2 = INF;
                    for (int i = 0; i < n; i++)
                    {
                        for (int j = 0; j < m; j++)
                        {
                            if (i == x && j == y) continue;
                            if (grid[i][j] <= grid[x][y])
                            {
                                can2 = min(can2, dp[i][j][t-1]);
                            }
                        }
                    }
                    dp[x][y][t] = min(can1, can2);
                }
            }
        }
        return dp[0][0][k];
    }
};

//TLE了，我们不能在传送的时候枚举所有的目标传送的格子
//后缀最小值优化：我们考虑传送只能是较大的值的格子传送到较小的值的格子
//对于传送的选择，因为传送代价为0
//实际上数值较小的格子(t,x,y)只需要继承：
//传送前一次的不小于自己的数值的格子的最小开销，
//也就是说那些全部的dp[i][j][t-1],满足g[i][j]>=g[x][y]的
//因此在记录完所有这一层的t之后，
//我们开一个数组minpre[x]记录数值满足次数为t-1下的g[i][j]>=x的最小开销
//然后使用一个变量滚动更新前缀最小值
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    const vector<int> dx = { 0,1 };
    const vector<int> dy = { 1,0 };
    int n, m;
    vector<vector<vector<int>>> dp;
    int minCost(vector<vector<int>>& grid, int k) {
        //n*m的数组
        n = grid.size(), m = grid[0].size();
        dp.assign(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, 0)));
        //base case
        for (int t = 0; t <= k; t++)
        {
            dp[n - 1][m - 1][t] = 0;
        }
        //另一base case,t=0的情况下，无传送
        for (int x = n - 1; x >= 0; x--)
        {
            for (int y = m - 1; y >= 0; y--)
            {
                if (x == n - 1 && y == m - 1) continue;
                int can1 = INF;
                for (int i = 0; i < 2; i++)
                {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < n && ny < m)
                    {
                        can1 = min(can1, dp[nx][ny][0] + grid[nx][ny]);
                    }
                }
                dp[x][y][0] = can1;
            }
        }
        //下面的每一层都依赖于上面一层
        for (int t = 1; t <= k; t++)
        {
            //每次预处理出minpre数组
            vector<int> minpre(10005,INF);
            for (int x = n - 1; x >= 0; x--)
            {
                for (int y = m - 1; y >= 0; y--)
                {
                    minpre[grid[x][y]] = min(minpre[grid[x][y]], dp[x][y][t - 1]);
                }
            }
            //倒序遍历求前缀最小值
            for (int l = 1; l <= 10000; l++) minpre[l] = min(minpre[l], minpre[l - 1]);
            //这样我们就得到了minsuf中的x表示到大于等于x的格子的最小开销
            for (int x = n - 1; x >= 0; x--)
            {
                for (int y = m - 1; y >= 0; y--)
                {
                    if (x == n - 1 && y == m - 1) continue;
                    //向右/向下移动
                    int can1 = INF;
                    for (int i = 0; i < 2; i++)
                    {
                        int nx = x + dx[i], ny = y + dy[i];
                        if (nx < n && ny < m)
                        {
                            can1 = min(can1, dp[nx][ny][t] + grid[nx][ny]);
                        }
                    }
                    //传送
                    //从minpre中转移过来
                    int can2 = minpre[grid[x][y]];
                    dp[x][y][t] = min(can1, can2);
                }
            }
        }
        return dp[0][0][k];
    }
};
