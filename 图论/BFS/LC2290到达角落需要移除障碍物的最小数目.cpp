/*
给你一个下标从 0 开始的二维整数数组 grid ，数组大小为 m x n 。每个单元格都是两个值之一：

0 表示一个 空 单元格，
1 表示一个可以移除的 障碍物 。
你可以向上、下、左、右移动，从一个空单元格移动到另一个空单元格。

现在你需要从左上角 (0, 0) 移动到右下角 (m - 1, n - 1) ，返回需要移除的障碍物的 最小 数目。
*/
#include <vector>
#include <queue>
#include <deque>
using namespace std;
class Solution {
public:
    int dx[4] = { 0,0,-1,1 };
    int dy[4] = { -1,1,0,0 };
    int minimumObstacles(vector<vector<int>>& grid) {
        //m行n列
        int m = grid.size();
        int n = grid[0].size();
        //初始化distance距离表,最初距离无穷大
        vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
        deque<pair<int, int>> dq;
        //源点入队，距离设为0
        dq.push_front({ 0,0 });
        distance[0][0] = 0;
        //开始01BFS循环
        while (!dq.empty())
        {
            //弹出队首，考察四个方向
            int x = dq.front().first;
            int y = dq.front().second;
            dq.pop_front();
            for (int i = 0; i < 4; i++)
            {
                int xn = x + dx[i];
                int yn = y + dy[i];
                //检查不越界，并且如果能让distance变得更小
                if (xn >= 0 && xn < m && yn >= 0 && yn<n &&
                    distance[xn][yn]>distance[x][y] + grid[xn][yn])
                {
                    //更新距离
                    distance[xn][yn] = distance[x][y] + grid[xn][yn];
                    //讨论边权是否为0，0从队列首加入，1从队尾加入
                    if (grid[xn][yn] == 0)
                    {
                        dq.push_front({ xn,yn });
                    }
                    else dq.push_back({ xn,yn });
                }
            }
        }
        return distance[m - 1][n - 1];
    }
};