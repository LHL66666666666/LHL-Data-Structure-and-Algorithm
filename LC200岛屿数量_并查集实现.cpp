#include <vector>
using namespace std;
class Solution {
public:
    const int MAXN = 1e5 + 5;
    int father[100005];
    void build()
    {
        for (int i = 0; i < MAXN; i++)
        {
            father[i] = i;
        }
    }
    int find(int x)
    {
        if (x != father[x])
        {
            father[x] = find(father[x]);
        }
        return father[x];
    }
    bool isSame(int x, int y)
    {
        return find(x) == find(y);
    }
    void Union(int x, int y)
    {
        father[find(x)] = find(y);
    }
    int numIslands(vector<vector<char>>& grid) {
        build();
        //使用并查集的思路是：将每个位置的1和它相连通的1合并为1个集合
        //最后输出集合的数量即可
        //优化点是每次遍历到1都只需检查它左侧和上侧的
        //m*n的矩阵
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == '1')
                {
                    ans++;
                    int idx = i * n + j;
                    //先检查，在合并
                    if (i - 1 >= 0 && grid[i - 1][j] == '1')
                    {
                        int idx1 = (i - 1) * n + j;
                        if (!isSame(idx, idx1))
                        {
                            Union(idx, idx1);
                            ans--;
                        }
                    }
                    if (j - 1 >= 0 && grid[i][j - 1] == '1')
                    {
                        int idx2 = i * n + j - 1;
                        if (!isSame(idx, idx2))
                        {
                            Union(idx, idx2);
                            ans--;
                        }
                    }
                }
            }
        }
        return ans;
    }
};