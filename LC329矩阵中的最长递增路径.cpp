#include <vector>
using namespace std;
class Solution {
public:
    //DFS,超时，这里状态定义的是到位置x,y的最长路径
    int dx[4] = { 0,0,-1,1 };
    int dy[4] = { 1,-1,0,0 };
    int dp[205][205];
    int n, m;
    void dfs(vector<vector<int>>& matrix,int x,int y)
    {
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny<m && matrix[nx][ny]>matrix[x][y])
            {
                dp[nx][ny] = max(dp[nx][ny], 1 + dp[x][y]);
                dfs(matrix, nx, ny);
            }
        }
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        n = matrix.size();
        m = matrix[0].size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                dp[i][j] = 1;
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                dfs(matrix, i, j);
            }
        }
        int ans = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }
};

//加上记忆化搜索
class Solution {
public:
    int dx[4] = { 0,0,-1,1 };
    int dy[4] = { 1,-1,0,0 };
    int dp[205][205];
    int n, m;
    int dfs(vector<vector<int>>& matrix, int x, int y)
    {
        if (dp[x][y] != -1)
        {
            return dp[x][y];
        }
        int ans = 1;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny<m && matrix[nx][ny]>matrix[x][y])
            {
                ans = max(ans, 1 + dfs(matrix, nx, ny));
            }
        }
        dp[x][y] = ans;
        return ans;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        n = matrix.size();
        m = matrix[0].size();
        memset(dp, -1, sizeof(dp));
        //定义状态为从i,j位置出发能得到的最长路径
        int ans = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                ans = max(ans, dfs(matrix, i, j));
            }
        }
        return ans;
    }
};