#include <vector>
class Solution {
public:
    int x[4] = { 0,0,1,-1 };
    int y[4] = { 1,-1,0,0 };
    void dfs(std::vector<std::vector<char>>& grid,int x0,int y0,int m,int n)
    {
        //如果自己是1，标记
        if (grid[x0][y0] == '1')
        {
            grid[x0][y0] = 0;
        }
        else return;
        for (int i = 0; i < 4; i++)
        {
            int x_new = x0 + x[i];
            int y_new = y0 + y[i];
            if (x_new >= 0 && x_new < m && y_new >= 0 && y_new < n)
            {
                dfs(grid, x_new, y_new, m, n);
            }
        }
    }
    int numIslands(std::vector<std::vector<char>>& grid) {
        //问题是找到一个1所有联通的1
        //显然是dfs
        //记得剪枝，将用过的区域标记
        //原地标记即可
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == '1')
                {
                    dfs(grid, i, j, m, n);
                    ans++;
                }
            }
        }
        return ans;
    }
};