#include <vector>
using namespace std;
class Solution {
public:
    long long dp[205];
    long long tmp[205];
    const int INF = 0x3f3f3f3f;
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        //n*m的矩阵
        int n = matrix.size();
        int m = matrix[0].size();
        int l1 = 0, r1 = 0, l2 = 0, r2 = 0;
        long long ans = -INF;
        //使用的之前单调栈里面的技巧，压缩数组
        //我们要求最大子矩阵，考虑这个矩阵一定是以某一行为结束位置的
        //我们枚举这个结束位置的行，同时枚举开头位置的行
        //此时我们就可以将这些行的同列的各个数字全部相加，压缩为一个一维数组
        //因为我们要求的子矩阵必须连续，这个问题就转化为子数组最大累加和问题
        //时间复杂度:O(n^2*m)
        //枚举起始位置的行是O(n^2)枚举，计算子数组最大累加和是O(m)
        //还要维护行和列的编号
        //可以先对每一列前缀和，可以O(m)计算出每次要求最大累加和的数组
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                matrix[i][j] += matrix[i - 1][j];
            }
        }
        //枚举起始位置的行
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                //压缩数组
                if (i == 0)
                {
                    for (int k = 0; k < m; k++)
                    {
                        tmp[k] = matrix[j][k];
                    }
                }
                else {
                    for (int k = 0; k < m; k++)
                    {
                        tmp[k] = matrix[j][k] - matrix[i - 1][k];
                    }
                }
                //子数组最大累加和
                dp[0] = tmp[0];
                if (dp[0] > ans)
                {
                    l1 = i, l2 = j, r1 = 0, r2 = 0;
                    ans = dp[0];
                }
                int tmpl = 0;
                for (int r = 1; r < m; r++)
                {
                    if (dp[r - 1] >= 0)
                    {
                        dp[r] = dp[r - 1] + tmp[r];
                    }
                    else {
                        dp[r] = tmp[r];
                        tmpl = r;
                    }
                    if (dp[r] > ans)
                    {
                        ans = dp[r];
                        l1 = i, l2 = j, r1 = tmpl, r2 = r;
                    }
                }
            }
        }
        vector<int> ret = { l1,r1,l2,r2 };
        return ret;
    }
};
/*
问题从一维变成了二维，但实质是一样的，
同样是再求最大子序和，我们需要将二维转化为一维，
对于矩阵的每一列，我们将其加在一起，成为了一维上的一个数，二维矩阵的和转化为了一维数组的和
*/