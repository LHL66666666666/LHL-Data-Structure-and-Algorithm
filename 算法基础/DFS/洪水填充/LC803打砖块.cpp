#include<vector>
using namespace std;
class Solution {
public:
    int m, n, len;
    int x0[4] = { 0,0,1,-1 };
    int y0[4] = { 1,-1,0,0 };
    void dfs(vector<vector<int>>& grid,int x,int y)
    {
        //打上标记
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 1)
        {
            return;
        }
        grid[x][y] = 2;
        dfs(grid, x + 1, y);
        dfs(grid, x - 1, y);
        dfs(grid, x, y + 1);
        dfs(grid, x, y - 1);
    }
    int dfs2(vector<vector<int>>& grid, int x, int y)
    {
        int s = 0;
        if (grid[x][y] == 1)
        {
            grid[x][y] = 2;
            s += 1;
        }
        else return 0;
        for (int i = 0; i < 4; i++)
        {
            int x_n = x + x0[i];
            int y_n = y + y0[i];
            if (x_n >= 0 && x_n < m && y_n >= 0 && y_n < n)
            {
                s += dfs2(grid, x_n, y_n);
            }
        }
        return s;
    }
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        //使用到时光倒流的一种处理流程
        //本题的核心在于处理的流程，
        //逆向处理，将正向的每次计算掉落的砖块数量转换为逆向每次恢复，
        //逆向计算每次恢复的砖块的个数，就是每次掉落的个数
        //由于逆向处理，我们只需要研究每次加上被打的砖块之后，能增加几个与天花板相连的砖块即可
        //已经与天花板相连的不需要再考虑，本次检查到的新与天花板相连的打上标记，这样就简化了计算
        //m*n的网格
        m = grid.size();
        n = grid[0].size();
        len = hits.size();
        vector<int> ans(len);
        //第一步，记录每次操作，每次操作会使网格中对应位置的数值-1
        for (int i = 0; i < len; i++)
        {
            grid[hits[i][0]][hits[i][1]]--;
        }
        //第二步，洪水填充，将全部打完之后与天花板相连的标记
        for (int i = 0; i < n; i++)
        {
            if (grid[0][i] == 1)
            {
                dfs(grid, 0, i);
            }
        }
        //第三步，开始逆向恢复
        for (int i = len - 1; i >= 0; i--)
        {
            //如果这个位置+1变成0，证明最开始就是0，没被打中，所以这个位置答案为0
            grid[hits[i][0]][hits[i][1]]++;
            if (grid[hits[i][0]][hits[i][1]] == 0)
            {
                ans[i] = 0;
            }
            else {
                //如果该位置+1变为1，那么考察这个位置是否与天花板连接
                int flag = 0;
                if (hits[i][0] == 0)
                {
                    //被打的位置在天花板上
                    flag = 1;
                }
                //检查四个邻接位置
                for (int j = 0; j < 4; j++)
                {
                    int x_n = hits[i][0] + x0[j];
                    int y_n = hits[i][1] + y0[j];
                    if (x_n >= 0 && x_n < m && y_n >= 0 && y_n < n && grid[x_n][y_n] == 2)
                    {
                        flag = 1;
                    }
                }
                if (flag)
                {
                    //也就是说这个恢复之后与天花板产生了联系
                    //检查会新产生多少个2，减去1即为答案
                    int sum = dfs2(grid, hits[i][0], hits[i][1]);
                    //需要-1，因为自己不算
                    ans[i] = sum - 1;

                }
                else {
                    //这个位置没有和天花板产生联系，攒着，可能是前面的步骤使这个位置的掉落
                    ans[i] = 0;
                }
            }
        }
        return ans;
    }
};