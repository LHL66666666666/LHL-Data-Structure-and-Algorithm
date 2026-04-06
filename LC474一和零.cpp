#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    int findMaxForm1(vector<string>& strs, int m, int n) {
        return f1(strs, 0, m, n);
    }
    //暴力递归，枚举每个位置选还是不选
    int f1(vector<string>& strs, int i, int z, int o)
    {
        int n = strs.size();
        if (i == n) return 0;
        int p1 = 0, p2 = 0;
        //不选
        p1 = f1(strs, i + 1, z, o);
        //选
        int n1 = strs[i].size();
        int zz = 0, oo = 0;
        for (int j = 0; j < n1; j++)
        {
            if (strs[i][j] == '0') zz++;
            else oo++;
        }
        if (z >= zz && o >= oo)
        {
            p2 = 1 + f1(strs, i + 1, z-zz, o-oo);
        }
        return max(p1, p2);
    }
    //记忆化搜索
    //dp[][][]
    //0的数量、1的数量、遍历到的位置idx
    int dp[105][105][605];
    int findMaxForm2(vector<string>& strs, int m, int n) {
        memset(dp, -1, sizeof(dp));
        return f2(strs, 0, m, n);
    }
    int f2(vector<string>& strs, int i, int z, int o)
    {
        int n = strs.size();
        if (i == n) return 0;
        if (dp[z][o][i] != -1) return dp[z][o][i];
        int p1 = 0, p2 = 0;
        //不选
        p1 = f2(strs, i + 1, z, o);
        //选
        int n1 = strs[i].size();
        int zz = 0, oo = 0;
        for (int j = 0; j < n1; j++)
        {
            if (strs[i][j] == '0') zz++;
            else oo++;
        }
        if (z >= zz && o >= oo)
        {
            p2 = 1 + f2(strs, i + 1, z - zz, o - oo);
        }
        int ans = max(p1, p2);
        dp[z][o][i] = ans;
        return ans;
    }
    //严格位置依赖的dp
    int findMaxForm(vector<string>& strs, int m, int n) {
        return f3(strs, m, n);
    }
    int f3(vector<string>& strs,int z, int o)
    {
        int n = strs.size();
        //跟据base case 最上面一层也就是i==strs.size()的时候，都是0
        for (int i = 0; i <= z; i++)
        {
            for (int j = 0; j <= o; j++)
            {
                dp[i][j][n] = 0;
            }
        }
        //每一层格子依赖上面的格子，本层格子之间无依赖关系
        for (int k = n - 1; k >= 0; k--)
        {
            int zz = 0, oo = 0;
            int n1 = strs[k].size();
            for (int l = 0; l < n1; l++)
            {
                if (strs[k][l] == '0') zz++;
                else oo++;
            }
            for (int i = 0; i <= z; i++)
            {
                for (int j = 0; j <= o; j++)
                {
                    int p1 = 0, p2 = 0;
                    p1 = dp[i][j][k + 1];
                    if (i >= zz && j >= oo)
                    {
                        p2 = 1 + dp[i - zz][j - oo][k + 1];
                    }
                    dp[i][j][k] = max(p1, p2);
                }
            }
        }
        return dp[z][o][0];
    }
};