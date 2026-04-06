/*
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。
*/
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    bool flag1 = false;
    int flag[10][10];
    //查找上下左右四个位置
    int x0[4] = { 0,0,1,-1 };
    int y0[4] = { 1,-1,0,0 };
    //idx表示到了字符串的哪个位置
    void dfs(vector<vector<char>>& board, string& word, int idx, int x, int y, int m, int n)
    {
        if (flag1) return;  // 关键：提前终止
        //先检查自己
        if (board[x][y] != word[idx])
        {
            //自己都不对的话直接剪枝
            return;
        }
        if (idx == word.size() - 1)
        {
            flag1 = true;
            return;
        }
        //标记该位置已用
        flag[x][y] = 1;
        //搜索上下左右四个位置
        for (int i = 0; i < 4; i++)
        {
            int x_new = x + x0[i];
            int y_new = y + y0[i];
            if (x_new >= 0 && x_new < m && y_new >= 0 && y_new < n && flag[x_new][y_new] == 0)
            {
                //如果该位置合法，且未被使用，搜索该位置
                dfs(board, word, idx + 1, x_new, y_new, m, n);
            }
        }
        //恢复现场,回溯时恢复的是当前的节点
        flag[x][y] = 0;

    }
    bool exist(vector<vector<char>>& board, string word) {
        flag1 = false;
        //m*n的网格
        int m = board.size();
        int n = board[0].size();
        //遍历每个位置
        //记得要递归
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //找到开头位置
                if (board[i][j] == word[0])
                {
                    memset(flag, 0, sizeof(flag));
                    dfs(board, word, 0, i, j, m, n);
                    if (flag1) return true;  // 提前返回
                }
            }
        }
        return flag1;
    }
};


class Solution {
public:
    int dx[4] = { 0,0,1,-1 };
    int dy[4] = { 1,-1,0,0 };
    //标记之前使用过
    int vis[10][10];
    bool flag = 0;
    void dfs(vector<vector<char>>& b, string& w, int id,int x,int y)
    {
        int n = b.size();
        int m = b[0].size();
        int nw = w.size();
        if (b[x][y] != w[id])
        {
            return;
        }
        if (id == nw - 1)
        {
            flag = 1;
            return;
        }
        vis[x][y] = 1;
        //尝试4个位置
        for (int i = 0; i < 4; i++)
        {
            int xn = x + dx[i];
            int yn = y + dy[i];
            if (xn >= 0 && xn < n && yn >= 0 && yn < m && !vis[xn][yn])
            {
                dfs(b, w, id + 1, xn, yn);
            }
        }
        //回溯
        vis[x][y] = 0;
    }
    bool exist(vector<vector<char>>& board, string word) {
        flag = 0;
        int n = board.size();
        int m = board[0].size();
        bool ret = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == word[0])
                {
                    memset(vis, 0, sizeof(vis));
                    dfs(board, word, 0, i, j);
                }
            }
        }
        return flag;
    }
};