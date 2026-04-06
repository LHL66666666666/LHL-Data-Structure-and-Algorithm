//n皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，
//并且使皇后彼此之间不能相互攻击。
//给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。
//数组表示路径的n皇后问题
#include <cmath>
#include <vector>
class Solution {
public:
    std::vector<int> path;
    int totalNQueens(int n) {
        path.clear();
        return f1(0, path, n);
    }
    //检查在idx行，j列拜访一个皇后会不会与之前的皇后冲突
    //之前的是存储在path里面
    //0到idx-1行，path[0]到path[n-1]列
    bool check1(std::vector<int>&path, int idx, int j)
    {
        for (int m = 0; m < idx; m++)
        {
            int tmp1 = abs(idx - m);
            int tmp2 = abs(j - path[m]);
            //两个tmp表示横坐标之差和纵坐标之差
            //两个皇后不冲突的条件是斜率的绝对值不等于1
            if (path[m] == j || tmp1 == tmp2)
            {
                return false;
            }
        }
        return true;
    }
    //数组path表示前面路径上的皇后摆在哪些列上面
    //n为问题规模
    //数组下标从0到n-1,n个数字
    //返回：在[0,idx-1]位置已经确定的情况下，从idx位置到n-1位置的方法数
    int f1(int idx,std::vector<int>&path,int n)
    {
        //base case
        if (idx == n)
        {
            //递归能够到达末尾位置，证明可行
            return 1;
        }
        //记录答案的变量
        int ans = 0;
        //遍历每一行
        //找到可行位置,每一列都检查
        for (int j = 0; j < n; j++)
        {
            //剪枝
            if (check1(path, idx, j))
            {
                path.emplace_back(j);
                ans += f1(idx + 1, path, n);
                //回溯：恢复现场！！！
                path.pop_back();
            }
        }
        return ans;
    }
};
//使用静态数组可以避免回溯，使用下标管理路径位置即可
class Solution {
public:
    int totalNQueens(int n) {
        int path[n];  // 静态数组存储列位置
        return backtrack(0, path, n);
    }

private:
    int backtrack(int row, int path[], int n) {
        if (row == n) return 1;

        int count = 0;
        for (int col = 0; col < n; col++) {
            if (isValid(path, row, col)) {
                path[row] = col;  // 直接赋值，不需要push_back
                count += backtrack(row + 1, path, n);
                // 不需要恢复！因为下一轮循环会覆盖这个位置
            }
        }
        return count;
    }

    bool isValid(int path[], int row, int col) {
        for (int i = 0; i < row; i++) {
            if (path[i] == col || abs(row - i) == abs(col - path[i])) {
                return false;
            }
        }
        return true;
    }
};