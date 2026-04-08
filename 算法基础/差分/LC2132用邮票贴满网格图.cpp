/*
给你一个 m x n 的二进制矩阵 grid ，每个格子要么为 0 （空）要么为 1 （被占据）。

给你邮票的尺寸为 stampHeight x stampWidth 。我们想将邮票贴进二进制矩阵中，且满足以下 限制 和 要求 ：

覆盖所有 空 格子。
不覆盖任何 被占据 的格子。
我们可以放入任意数目的邮票。
邮票可以相互有 重叠 部分。
邮票不允许 旋转 。
邮票必须完全在矩阵 内 。
如果在满足上述要求的前提下，可以放入邮票，请返回 true ，否则返回 false 。
*/
int b[10005][10005]  ;
int c[10005][10005]  ;

class Solution {
public:
    void set(int a[][10005], int x1, int y1, int x2, int y2)
    {
        a[x1][y1]++;
        a[x2 + 1][y2 + 1]++;
        a[x2 + 1][y1]--;
        a[x1][y2 + 1]--;
    }
    void build(int a[][10005],int m,int n)
    {
        for (int i = 1; i <=m; i++)
        {
            for (int j = 1; j <=n; j++)
            {
                a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + a[i][j];
            }
        }
    }

    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        //重置数组
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        //思路是先用二维前缀和统计空位的数量
        //由于不允许旋转
        //因为邮票之间可以重合，可以无限叠放
        //使用贪心
        //对于每个满足的height*width
        //如果满足空位的个数是height*width
        //就填入这个邮票
        //最后只需统计数组中是否含有0即可
        int m = grid.size();
        //m行
        int n = grid[0].size();
        //n列
        //int b[10005][10005] = { 0 };
        //int c[10005][10005] = { 0 };
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                b[i][j] = 1 - grid[i-1][j-1];
            }
        }
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + b[i][j];
            }
        }
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i + stampHeight-1<=m && j + stampWidth-1<=n && b[i + stampHeight-1][j + stampWidth-1] + b[i - 1][j - 1] - b[i + stampHeight-1][j - 1] - b[i - 1][j + stampWidth-1] == stampHeight * stampWidth)
                {
                    set(c, i, j, i + stampHeight-1, j + stampWidth-1);
                }
            }
        }
        build(c,m,n);
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (c[i][j] + grid[i-1][j-1] == 0)
                {
                    return false;
                }
            }
        }
        return true;

    }
};
//不会开vector导致TLE，只要开了vector问题就不大
//思路完全一样
class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        int m = grid.size();
        int n = grid[0].size();

        // 使用 vector 动态分配，只分配需要的空间
        vector<vector<int>> b(m + 2, vector<int>(n + 2, 0));
        vector<vector<int>> c(m + 2, vector<int>(n + 2, 0));

        // 构建空位数组
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                b[i][j] = 1 - grid[i - 1][j - 1];
            }
        }

        // 构建前缀和
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + b[i][j];
            }
        }

        // 检查可以放置邮票的位置（修正边界条件）
        for (int i = 1; i <= m - stampHeight + 1; i++) {
            for (int j = 1; j <= n - stampWidth + 1; j++) {
                int x2 = i + stampHeight - 1;
                int y2 = j + stampWidth - 1;

                int emptyCount = b[x2][y2] - b[i - 1][y2] - b[x2][j - 1] + b[i - 1][j - 1];

                if (emptyCount == stampHeight * stampWidth) {
                    // 直接更新差分数组，不需要单独的 set 函数
                    c[i][j]++;
                    if (x2 + 1 <= m + 1) c[x2 + 1][j]--;
                    if (y2 + 1 <= n + 1) c[i][y2 + 1]--;
                    if (x2 + 1 <= m + 1 && y2 + 1 <= n + 1) c[x2 + 1][y2 + 1]++;
                }
            }
        }

        // 构建覆盖数组
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                c[i][j] = c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1] + c[i][j];

                // 检查空位是否被覆盖
                if (grid[i - 1][j - 1] == 0 && c[i][j] == 0) {
                    return false;
                }
            }
        }

        return true;
    }
};