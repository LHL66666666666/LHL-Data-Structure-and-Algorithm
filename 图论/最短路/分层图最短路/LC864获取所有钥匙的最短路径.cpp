/*
给定一个二维网格 grid ，其中：

'.' 代表一个空房间
'#' 代表一堵墙
'@' 是起点
小写字母代表钥匙
大写字母代表锁
我们从起点开始出发，一次移动是指向四个基本方向之一行走一个单位空间。
我们不能在网格外面行走，也无法穿过一堵墙。如果途经一个钥匙，我们就把它捡起来。
除非我们手里有对应的钥匙，否则无法通过锁。
假设 k 为 钥匙/锁 的个数，且满足 1 <= k <= 6，
字母表中的前 k 个字母在网格中都有自己对应的一个小写和一个大写字母。
换言之，每个锁有唯一对应的钥匙，每个钥匙也有唯一对应的锁。
另外，代表钥匙和锁的字母互为大小写并按字母顺序排列。
返回获取所有钥匙所需要的移动的最少次数。如果无法获取所有钥匙，返回 -1 。
*/
#include <vector>
#include <queue>
#include <deque>
#include <string>
using namespace std;
class Solution {
public:
    int dx[4] = { 0,0,1,-1 };
    int dy[4] = { 1,-1,0,0 };
    const int mask = 1LL << 6;
    char s[35][35];
    int vis[35][35][(1LL << 6)];
    int shortestPathAllKeys(vector<string>& grid) {
        //和之前考虑方向的01BFS很像，需要另开新一维数组来记录状态
        //记录的状态是当前钥匙收集情况，状态压缩，使用一个整数表示即可
        memset(vis, 0, sizeof(vis));
        int n = grid.size();
        int m = grid[0].size();
        //最终要求的状态:也就是钥匙全收集状态
        int key = 0;
        int startx, starty;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                s[i][j] = grid[i][j];
                if (grid[i][j] >= 'a' && grid[i][j] <= 'z')
                {
                    key |= (1LL << (grid[i][j] - 'a'));
                }
                if (grid[i][j] == '@')
                {
                    startx = i;
                    starty = j;
                }
            }
        }
        queue<tuple<int, int, int>> qe;
        //源点进入，源点状态为无钥匙，即每一位上都是0
        qe.emplace(startx, starty, 0);
        vis[startx][starty][0] = 1;
        int level = 1;
        while (!qe.empty())
        {
            int n1 = qe.size();
            for (int k = 0; k < n1; k++)
            {
                int x = get<0>(qe.front());
                int y = get<1>(qe.front());
                int state = get<2>(qe.front());
                qe.pop();
                //尝试四个方向扩展
                for (int i = 0; i < 4; i++)
                {
                    int xn = x + dx[i];
                    int yn = y + dy[i];
                    //staten表示新的状态
                    int staten = state;
                    //检查越界和撞墙,注意不在这里检查vis,因为vis的第三维参数待定
                    if (xn < 0 || xn >= n || yn < 0 || yn >= m || s[xn][yn] == '#') continue;
                    //跟据当前格子状态讨论,注意检查vis,标记过的不再访问
                    if (s[xn][yn] >= 'a' && s[xn][yn] <= 'z')
                    {
                        //钥匙
                        staten |= (1LL << (s[xn][yn] - 'a'));
                        if (staten == key)
                        {
                            return level;
                        }
                        //vis数组要检查真实的位置和钥匙的状态
                        if (!vis[xn][yn][staten])
                        {
                            vis[xn][yn][staten] = 1;
                            qe.emplace(xn, yn, staten);
                        }
                    }
                    else if (s[xn][yn] >= 'A' && s[xn][yn] <= 'Z')
                    {
                        //锁，检查是否能通过
                        if ((staten & (1LL << (s[xn][yn] - 'A'))) == 0)
                        {
                            //没有对应钥匙
                            continue;
                        }
                        else {
                            //有对应的钥匙,扩展
                            if (!vis[xn][yn][staten])
                            {
                                vis[xn][yn][staten] = 1;
                                qe.emplace(xn, yn, staten);
                            }
                        }
                    }
                    else {
                        //非墙，非钥匙也非锁，也就是开始位置和空位置
                        if (!vis[xn][yn][staten])
                        {
                            vis[xn][yn][staten] = 1;
                            qe.emplace(xn, yn, staten);
                        }
                    }
                }
            }
            ++level;
        }
        return -1;
    }
};