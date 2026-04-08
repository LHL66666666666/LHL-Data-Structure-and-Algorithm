#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    int dx[8] = { 1,1,2,2,-1,-1,-2,-2 };
    int dy[8] = { 2,-2,1,-1,2,-2,1,-1 };
    //状态定义：在(x,y)位置，此时已经移动了t步
    //到末尾才结算方案
    double dp[30][30][105];
    double knightProbability1(int n, int k, int row, int column) {
        for (int i = 0; i < 30; i++)
        {
            for (int j = 0; j < 30; j++)
            {
                for (int k = 0; k < 105; k++)
                {
                    dp[i][j][k] = -1;
                }
            }
        }
        return dfs1(row, column, 0, k, n);
    }
    //记忆化搜索
    double dfs1(int x, int y, int t, int k, int n)
    {
        if (t == k)
        {
            return 1;
        }
        if (dp[x][y][t] != -1)
        {
            return dp[x][y][t];
        }
        double ans = 0;
        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n)
            {
                ans += dfs1(nx, ny, t + 1, k, n) / 8.0;
            }
        }
        dp[x][y][t] = ans;
        return ans;
    }
    //动态规划
    double knightProbability(int n, int k, int row, int column) {
        return dfs2(n, k, row, column);
    }
    double dfs2(int n,int k,int x0,int y0)
    {
        //base case
        //能经过k次还留在棋盘上，都是1
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dp[i][j][k] = 1;
            }
        }
        //每个位置依赖上一层
        for (int t = k - 1; t >= 0; t--)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    dp[i][j][t] = 0;
                    int x = i, y= j;
                    for (int l = 0; l < 8; l++)
                    {
                        int ni = i + dx[l];
                        int nj = j + dy[l];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n)
                        {
                            dp[i][j][t] += dp[ni][nj][t + 1] / 8.0;
                        }
                    }
                }
            }
        }
        return dp[x0][y0][0];
    }
};