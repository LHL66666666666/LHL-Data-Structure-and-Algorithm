#include <vector>
using namespace std;
class Solution {
public:
    void dfs(vector<vector<char>>& a,int x,int y,int n,int m)
    {
        if (x < 0 || x >= n || y < 0 || y >= m || a[x][y] != 'O')
        {
            return;
        }
        a[x][y] = 0;
        dfs(a, x - 1, y, n, m);
        dfs(a, x + 1, y, n, m);
        dfs(a, x, y - 1, n, m);
        dfs(a, x, y + 1, n, m);
    }
    void solve(vector<vector<char>>& board) {
        //只要区域中位置全不在边缘，那么就可以捕获，如果有一个在边缘就不可以
        //那么我们只搜边缘，将边缘搜到的的区域不变，其他的全变为x
        int n = board.size();
        int m = board[0].size();
        //n*m矩阵
        //扫边缘的行
        for (int i = 0; i < m; i++)
        {
            if (board[0][i] == 'O')
            {
                dfs(board, 0, i, n, m);
            }
            if (board[n - 1][i] == 'O')
            {
                dfs(board, n - 1, i, n, m);
            }
        }
        //扫边缘的列
        for (int i = 0; i < n; i++)
        {
            if (board[i][0] == 'O')
            {
                dfs(board, i, 0, n, m);
            }
            if (board[i][m - 1] == 'O')
            {
                dfs(board, i, m - 1, n, m);
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == 'O')
                {
                    board[i][j] = 'X';
                }
                if (board[i][j] == 0)
                {
                    board[i][j] = 'O';
                }
            }
        }
    }
};