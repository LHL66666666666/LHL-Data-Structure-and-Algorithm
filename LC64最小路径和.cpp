#include <vector>
#include <string>
#include <climits>
using namespace std;
class Solution {
public:
    int minPathSum1(vector<vector<int>>& grid) {
        //暴力递归展开
        return f1(grid, 0, 0);
    }
    int f1(vector<vector<int>>& grid,int i,int j)
    {
        int n = grid.size();
        int m = grid[0].size();
        if (i == n - 1 && j == m - 1)
        {
            return grid[n - 1][m - 1];
        }
        //递归展开，每次往下走还是往右走
        int ans = grid[i][j];
        //如果能向下，就向下展开
        int tmp1 = INT_MAX, tmp2 = INT_MAX;
        if (i + 1 <= n - 1)
        {
            tmp1 = f1(grid, i + 1, j);
        }
        //如果能向右，就向右展开
        if (j + 1 <= m - 1)
        {
            tmp2 = f1(grid, i, j + 1);
        }
        ans += min(tmp1,tmp2);
        return ans;
    }
    //记忆化搜素
    int dp[205][205];
    int minPathSum2(vector<vector<int>>& grid) {
        //挂缓存表，记忆化搜素
        int n = grid.size();
        int m = grid[0].size();
        memset(dp, -1, sizeof(dp));
        dp[n - 1][m - 1] = grid[n - 1][m - 1];
        return f2(grid, 0, 0);
    }
    int f2(vector<vector<int>>& grid, int i, int j)
    {
        int n = grid.size();
        int m = grid[0].size();
        if (i == n - 1 && j == m - 1)
        {
            return grid[n - 1][m - 1];
        }
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }
        //递归展开，每次往下走还是往右走
        int ans = grid[i][j];
        //如果能向下，就向下展开
        int tmp1 = INT_MAX, tmp2 = INT_MAX;
        if (i + 1 <= n - 1)
        {
            tmp1 = f2(grid, i + 1, j);
        }
        //如果能向右，就向右展开
        if (j + 1 <= m - 1)
        {
            tmp2 = f2(grid, i, j + 1);
        }
        ans += min(tmp1, tmp2);
        dp[i][j] = ans;
        return ans;
    }
    //严格位置依赖的dp
    int minPathSum3(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        memset(dp, 0, sizeof(dp));
        dp[0][0] = grid[0][0];
        return f3(grid, 0, 0);
    }
    int f3(vector<vector<int>>& grid, int i, int j)
    {
        int n = grid.size();
        int m = grid[0].size();
        for (int p = 1; p < n; p++)
        {
            dp[p][0] = grid[p][0] + dp[p - 1][0];
        }
        for (int q = 1; q < m; q++)
        {
            dp[0][q] = grid[0][q] + dp[0][q - 1];
        }
        for (int p = 1; p < n; p++)
        {
            for (int q = 1; q < m; q++)
            {
                dp[p][q] = grid[p][q] + min(dp[p - 1][q], dp[p][q - 1]);
            }
        }
        return dp[n - 1][m - 1];
    }
    //加入空间压缩
    int dp1[205];
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        memset(dp1, 0, sizeof(dp1));
        return f4(grid);
    }
    int f4(vector<vector<int>>& grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        //先处理第0行
        dp1[0] = grid[0][0];
        for (int j = 1; j < m; j++)
        {
            dp1[j] = dp1[j - 1] + grid[0][j];
        }
        //每一行滚动更新
        for (int i = 1; i < n; i++)
        {
            //每一行第0列单独处理
            dp1[0] = dp1[0] + grid[i][0];
            for (int j = 1; j < m; j++)
            {
                dp1[j] = grid[i][j] + min(dp1[j - 1], dp1[j]);
            }
        }
        return dp1[m - 1];
    }
}; 