/*
给你一个 m x n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度，
请计算图中形状最多能接多少体积的雨水。
*/
//本题是经典的BFS结合优先级队列
#include <vector>
#include <deque>
#include <queue>
using namespace std;
class Solution {
public:
    int dx[4] = { 0,0,1,-1 };
    int dy[4] = { 1,-1,0,0 };
    int trapRainWater(vector<vector<int>>& heightMap) {
        //首先应当认识到三维接雨水和二维接雨水是不同的问题
        //如果我们按照类似二维的前后缀最大值来处理，
        //在三维空间可能会被行/列上不单调的高度卡，因此这就启发我们向四周扩(BFS)找瓶颈
        //首先，边缘的格子无法接水，我们用小根堆来维护水位线(因为每个格子可容纳的水量受到周围最大高度的最小值限制)
        //我们就从高度的最小值(也就是瓶颈)入手，每次考察堆顶，看堆顶这个瓶颈的限制最多能扩到哪里
        //每次按照最薄弱的点展开，保证水线一定可以到这个高度
        int m = heightMap.size();
        int n = heightMap[0].size();
        vector<vector<int>> vis(m, vector<int>(n));
        //优先队列里面存三个参数，行，列，水位线
        //lambda表达式
        auto cmp = [](const vector<int>& a, const vector<int>& b)
            {
                return a[2] > b[2];
            };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        //初始化vis数组，把边缘的点先进堆
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == 0 || j == 0 || i == m - 1 || j == n - 1)
                {
                    pq.push({ i,j,heightMap[i][j] });
                    vis[i][j] = 1;
                }
                else vis[i][j] = 0;
            }
        }
        //按照最薄弱的点依次弹出并结算
        int ans = 0;
        while (!pq.empty())
        {
            int x = pq.top()[0];
            int y = pq.top()[1];
            int h = pq.top()[2];
            pq.pop();
            ans += h - heightMap[x][y];
            //遍历四个位置
            for (int i = 0; i < 4; i++)
            {
                int xn = x + dx[i];
                int yn = y + dy[i];
                if (xn >= 0 && xn < m && yn >= 0 && yn < n && !vis[xn][yn])
                {
                    vis[xn][yn] = 1;
                    //比较自己当前高度和扩过来的(也就是触发这个格子的)水位线哪个高
                    int tmp = max(h, heightMap[xn][yn]);
                    pq.push({ xn,yn,tmp });
                }
            }
        }
        return ans;
    }
};