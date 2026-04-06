#include <vector>
#include <algorithm>
#include <climits>
#include <set>
using namespace std;
//自己写的第一版，T飞了，实际上不需要每次都算一遍面积，
//只需要一次算出面积来然后讨论即可
class Solution {
public:
    int x0[4] = { 0,0,1,-1 };
    int y0[4] = { 1,-1,0,0 };
    int ans = 0;
    int dfs(vector<vector<int>>& grid,int x,int y,int n)
    {
        int s = 0;
        if (grid[x][y] == 1)
        {
            grid[x][y] = 0;
            s += 1;
        }
        else return 0;
        for (int i = 0; i < 4; i++)
        {
            int x_n = x + x0[i];
            int y_n = y + y0[i];
            if (x_n >= 0 && x_n < n && y_n >= 0 && y_n < n)
            {
                s+=dfs(grid, x_n, y_n, n);
            }
        }
        return s;
    }
    void find(vector<vector<int>> grid)
    {
        int ans0 = 0;
        //这里按值传递
        int n = grid.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    ans0 = max(ans0, dfs(grid, i, j, n));
                }
            }
        }
        ans = max(ans, ans0);
    }
    int largestIsland(vector<vector<int>>& grid) {
        ans = 0;
        int n = grid.size();
        //尝试将每个0位置改为1，每次统计最大的面积
        //注意特判没有0的情况！！！
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                {
                    flag = 1;
                    grid[i][j] = 1;
                    find(grid);
                    grid[i][j] = 0;
                }
            }
        }
        if (!flag)
        {
            return n * n;
        }
        return ans;
    }
};

//改进
class Solution {
public:
    int x0[4] = { 0,0,1,-1 };
    int y0[4] = { 1,-1,0,0 };
    int dfs(vector<vector<int>>& grid, int x, int y, int n,int idx)
    {
        int s = 0;
        if (grid[x][y] == 1)
        {
            grid[x][y] = idx;
            s += 1;
        }
        else return 0;
        for (int i = 0; i < 4; i++)
        {
            int x_n = x + x0[i];
            int y_n = y + y0[i];
            if (x_n >= 0 && x_n < n && y_n >= 0 && y_n < n)
            {
                s += dfs(grid, x_n, y_n, n,idx);
            }
        }
        return s;
    }
    int largestIsland(vector<vector<int>>& grid) {
        int ans = 0;
        int n = grid.size();
        int idx = 2;
        //开一个数组存储面积
        vector<int> s(250002);
        s[0] = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    //算面积，打标记
                    s[idx]=dfs(grid, i, j, n, idx);
                    ++idx;
                }
            }
        }
        //讨论每一个0，注意特判全是1的情况
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                {
                    set<int> st;
                    //标记找到过0
                    flag = 1;
                    //四个位置，看看联通了哪些
                    for (int k = 0; k < 4; k++)
                    {
                        int i_n = i + x0[k];
                        int j_n = j + y0[k];
                        if (i_n >= 0 && i_n < n && j_n >= 0 && j_n < n)
                        {
                            st.insert(grid[i_n][j_n]);
                        }
                    }
                    int sum = 1;
                    for (auto a : st)
                    {
                        sum += s[a];
                    }
                    ans = max(ans, sum);
                }
            }
        }
        if (!flag)
        {
            return n * n;
        }
        return ans;
    }
};

//并查集的做法