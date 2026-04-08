/*
给你一个 m x n 的网格图 grid 。 grid 中每个格子都有一个数字，对应着从该格子出发下一步走的方向。 
grid[i][j] 中的数字可能为以下几种情况：
1 ，下一步往右走，也就是你会从 grid[i][j] 走到 grid[i][j + 1]
2 ，下一步往左走，也就是你会从 grid[i][j] 走到 grid[i][j - 1]
3 ，下一步往下走，也就是你会从 grid[i][j] 走到 grid[i + 1][j]
4 ，下一步往上走，也就是你会从 grid[i][j] 走到 grid[i - 1][j]
注意网格图中可能会有 无效数字 ，因为它们可能指向 grid 以外的区域。
一开始，你会从最左上角的格子 (0,0) 出发。我们定义一条 有效路径 为从格子 (0,0) 出发，每一步都顺着数字对应方向走，
最终在最右下角的格子 (m - 1, n - 1) 结束的路径。有效路径 不需要是最短路径 。
你可以花费 cost = 1 的代价修改一个格子中的数字，但每个格子中的数字 只能修改一次 。
请你返回让网格图至少有一条有效路径的最小代价。
*/
#include <deque>
#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    //右，左，下，上
    int dx[4] = { 0,0,1,-1 };
    int dy[4] = { 1,-1,0,0 };
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        if (m == 1 && n == 1)
        {
            return 0;
        }
        //关键在于条件转化，也就是相当于来到每一个格子，
        //去往指向的格子的代价是0，去往其他三个方向的代价是1，
        //代价看作边权，就转化为01BFS
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX));
        deque<pair<int, int>> dq;
        dis[0][0] = 0;
        dq.push_back({ 0,0 });
        while (!dq.empty())
        {
            int x = dq.front().first;
            int y = dq.front().second;
            dq.pop_front();
            for (int i = 0; i < 4; i++)
            {
                int xn = x + dx[i];
                int yn = y + dy[i];
                //讨论四个方向
                int w = 1;
                if (i + 1 == grid[x][y])
                {
                    w = 0;
                }
                if (xn >= 0 && xn < m && yn >= 0 && yn<n &&
                    dis[xn][yn]>dis[x][y] + w)
                {
                    //满足条件，做修改
                    dis[xn][yn] = dis[x][y] + w;
                    if (w == 0)
                    {
                        dq.push_front({ xn,yn });
                    }
                    else dq.push_back({ xn,yn });
                }
            }
        }
        return dis[m - 1][n - 1];
    }
};