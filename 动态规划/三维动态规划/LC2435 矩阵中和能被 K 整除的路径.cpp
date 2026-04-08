#include <vector>
using namespace std;
class Solution {
public:
    const int MOD = 1e9 + 7;
    int dx[2] = { 0,-1 };
    int dy[2] = { -1,0 };
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        //n*m的矩阵
        int n = grid.size();
        int m = grid[0].size();
        //状态定义：到达坐标为(x,y)位置,当前路径和对k取模是cur,的路径数量dp[x][y][cur]
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(k, -1)));
        //要求的是dp[n-1][m-1][0]
        return f1(grid, n - 1, m - 1, grid[n - 1][m - 1] % k, k, dp);

    }
    long long f1(vector<vector<int>>& grid, int x, int y, int cur, int k, vector<vector<vector<int>>>& dp)
    {
        int n = grid.size();
        int m = grid[0].size();
        if (x == 0 && y == 0)
        {
            //路径问题，我们到结束位置再结算
            if (cur % k == 0)
            {
                return 1;
            }
            else return 0;
        }
        if (dp[x][y][cur] != -1)
        {
            return dp[x][y][cur];
        }
        long long ans = 0;
        //向两个方向移动
        for (int i = 0; i < 2; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m)
            {
                int tmp = (cur + grid[nx][ny]) % k;
                ans += f1(grid, nx, ny, tmp, k, dp);
                ans %= MOD;
            }
        }
        dp[x][y][cur] = ans;
        return ans;
    }
};
class Solution {
public:
    const int MOD = 1e9 + 7;
    int dx[2] = { 0,1 };
    int dy[2] = { 1,0 };
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        //n*m的矩阵
        int n = grid.size();
        int m = grid[0].size();
        //状态定义：到达坐标为(x,y)位置,当前路径和对k取模是cur,的路径数量dp[x][y][cur]
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(k, -1)));
        //要求的是dp[n-1][m-1][0]
        return f1(grid, 0, 0, grid[0][0] % k, k, dp);

    }
    long long f1(vector<vector<int>>& grid, int x, int y, int cur, int k, vector<vector<vector<int>>>& dp)
    {
        int n = grid.size();
        int m = grid[0].size();
        if (x == n - 1 && y == m - 1)
        {
            //路径问题，我们到结束位置再结算
            if (cur % k == 0)
            {
                return 1;
            }
            else return 0;
        }
        if (dp[x][y][cur] != -1)
        {
            return dp[x][y][cur];
        }
        long long ans = 0;
        //向两个方向移动
        for (int i = 0; i < 2; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m)
            {
                int tmp = (cur + grid[nx][ny]) % k;
                ans += f1(grid, nx, ny, tmp, k, dp);
                ans %= MOD;
            }
        }
        dp[x][y][cur] = ans;
        return ans;
    }
};

class Solution {
public:
    const int MOD = 1e9 + 7;
    //严格位置依赖的dp
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        //n*m的矩阵
        int n = grid.size();
        int m = grid[0].size();
        //状态定义：到达坐标为(x,y)位置,当前路径和对k取模是cur,的路径数量dp[x][y][cur]
        //要求的是dp[n-1][m-1][0],每个格子(x,y)依赖于(cur-grid[x][y])%k层的他的左和他的上
        //关键在于这个层数不一定是多少，所以难以跟据这个来敲定顺序
        //之前遇到的是依赖上一层，而剩下两个位置难以确定
        //这个问题是层数不确定，但是在二维平面上的位置以来是确定的，每个格子依赖他的左和他的上
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(k)));
        return f2(grid, k, dp);
    }
    long long f2(vector<vector<int>>& grid, int k, vector<vector<vector<int>>>& dp)
    {
        int n = grid.size();
        int m = grid[0].size();
        //先填base case
        int tmp = grid[n - 1][m - 1] % k;
        for (int i = 0; i < k; i++)
        {
            if (i == tmp) dp[n - 1][m - 1][i] = 1;
            else dp[n - 1][m - 1][i] = 0;
        }
        //二维网格的最后一行
        for (int j = m - 2; j >= 0; j--)
        {
            for (int kk = 0; kk < k; kk++)
            {
                int need = (kk - grid[n - 1][j] % k + k) % k;
                dp[n - 1][j][kk] = dp[n - 1][j + 1][need] % MOD;
            }
        }
        //二维网格的最后一列
        for (int i = n - 2; i >= 0; i--)
        {
            for (int kk = 0; kk < k; kk++)
            {
                int need = (kk - grid[i][m - 1] % k + k) % k;
                dp[i][m - 1][kk] = dp[i + 1][m - 1][need] % MOD;
            }
        }
        //依次填
        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = m - 2; j >= 0; j--)
            {
                for (int kk = 0; kk < k; kk++)
                {
                    long long ans = 0;
                    int need = (kk - grid[i][j] % k + k) % k;
                    ans = (ans + dp[i + 1][j][need]) % MOD;
                    ans = (ans + dp[i][j + 1][need]) % MOD;
                    dp[i][j][kk] = ans;
                }
            }
        }
        return dp[0][0][0];
    }
};