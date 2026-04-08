#include <vector>
#include <string>
using namespace std;
typedef long long ll;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    vector<vector<vector<int>>> dp;
    vector<int> pre;
    int dfs(int l, int r,int cnt,int k)
    {
        //base case
        if (r - l + 1 == cnt)
        {
            return 0;
        }
        if (dp[l][r][cnt] != -1) return dp[l][r][cnt];
        int ret = 0;
        //枚举第1堆是由几个合并而来的
        if (cnt == 1)
        {
            if (l == 0) ret += pre[r];
            else ret += pre[r] - pre[l - 1];
            int tmp = INF;
            for (int i = l; i < r; i += k - 1)
            {
                tmp = min(tmp, dfs(l, i, 1, k) + dfs(i + 1, r, k - 1, k));
            }
            ret += tmp;
        }
        else {
            int tmp = INF;
            for (int i = l; i < r; i += k - 1)
            {
                tmp = min(tmp, dfs(l, i, 1, k) + dfs(i + 1, r, cnt - 1, k));
            }
            ret += tmp;
        }
        dp[l][r][cnt] = ret;
        return ret;
        
    }
    int mergeStones(vector<int>& stones, int k) {
        //首先判断能否实现
        int n = stones.size();
        if (k != 2 && n % (k - 1) != 1)
        {
            return -1;
        }
        //如果可以实现
        //每次要找连续的一段变成1个
        dp.assign(n + 1, vector<vector<int>>(n + 1, vector<int>(k + 1, -1)));
        pre.assign(n, 0);
        pre[0] = stones[0];
        for (int i = 1; i < n; i++)
        {
            pre[i] = pre[i - 1] + stones[i];
        }
        return dfs(0, n - 1, 1, k);
    }
};
/*
我们考虑，最后一步进行了什么?
答案是：我们将最后的 k 堆合并为了1堆
那么我们可以从枚举这最后一步的 k 堆的第1堆入手考虑
考虑这个第1堆是怎么得来的，显然，这个第1堆是由1+(k-1)*m,m>=0合并来的
我们就可以枚举第1堆是由几个堆合并来的，然后后面还剩 k-1 堆
定义dfs(i,j,k)表示[i,j]区间上合并到不能再合并所需的最小代价

还有一个要点，如果区间[l,r]上最终合成1份，那么我们需要加上[l,r]区间数值累加和
为什么?因为合并不会改变总石子的数量
而如果不是1份，是m份(m<k)那么就无需再加，因为整个区间不需要再合起来

Q & A
Q：为什么只考虑分出 1 堆和 p−1 堆，而不考虑分出 x 堆和 p−x 堆
A：无需计算，因为 p−1 堆继续递归又可以分出 1 堆和 p−2 堆，和之前分出的 1 堆组合，
就已经能表达出「分出 2 堆和 p−2 堆」的情况了。其他同理。所以只需要考虑分出 1 堆和 p−1 堆
*/


//还可以进一步优化，实际上，只要确定了一个范围[l,r]这个区间最终合并出多少份是一定的
//因此我们可以将第三维压掉
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    vector<vector<int>> dp;
    vector<int> pre;
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if (k != 2 && n % (k - 1) != 1)
        {
            return -1;
        }
        dp.assign(n + 1, vector<int>(n + 1, 0));
        pre.assign(n, 0);
        pre[0] = stones[0];
        for (int i = 1; i < n; i++)
        {
            pre[i] = pre[i - 1] + stones[i];
        }
        //base case
        for (int i = 0; i < n; i++)
        {
            dp[i][i] = 0;
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < n; j++)
            {
                dp[i][j] = INF;
                //枚举
                for (int m = i; m < j; m += k - 1)
                {
                    dp[i][j] = min(dp[i][j], dp[i][m] + dp[m + 1][j]);
                }
                //如果要合并为1份，加上区间累加和
                if (k==2 || (j - i + 1) % (k - 1) == 1)
                {
                    if (i == 0) dp[i][j] += pre[j];
                    else dp[i][j] += pre[j] - pre[i - 1];
                }
            }
        }
        return dp[0][n - 1];
    }
};