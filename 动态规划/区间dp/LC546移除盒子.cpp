#include <vector>
#include <string>
using namespace std;
typedef long long ll;
class Solution {
public:
    vector<vector<vector<ll>>> dp;
    //记忆化搜索
    //k表示区间[l,r]上在l前面与l相同的前缀数字的数量
    //dp[i][j][k]表示区间[i,j]上，i有k个数值等于a[i]的元素的前缀，所能达到的最大分数
    //由于这个前缀我们可以考虑存起来一起消除，我们以前缀何时消去来决策
    //假设一个区间            1111 2..3 1111 3..4 11111 4..5 11111 6..7
    //我们假设有k个前缀1        1         2          3          4
    //前缀可能在1,2,3,4位置一起消去，当然也可能没有，我们枚举这样的段
    ll dfs(vector<int>& a, int l, int r, int k)
    {
        if (dp[l][r][k] != -1) return dp[l][r][k];
        //base case
        if (l > r) return 0;
        if (l == r) return 1LL * (k + 1) * (k + 1);
        //找到最长前缀
        int s = l;
        while (s + 1 <= r && a[s + 1] == a[l])
        {
            ++s;
        }
        //决策1：前缀先消去
        int cnt = k + s - l + 1;
        ll ret = cnt * cnt + dfs(a, s + 1, r, 0);
        //决策2：前缀跟着后面的某个区间消去
        //枚举，找到后面区间起始位置
        //我们已知s+1位置必然不等于a[l]，直接从s+2开始枚举
        for (int i = s + 2; i <= r; i++)
        {
            //剪枝，我们对于一个连续区间，如果区间上的数字等于a[l],则只需考虑开头数字即可
            if (a[i] == a[l] && a[i] != a[i - 1])
            {
                ret = max(ret, dfs(a, s + 1, i - 1, 0) + dfs(a, i, r, cnt));
            }
        }
        dp[l][r][k] = ret;
        return ret;
    }
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        if (n == 1) return 1;
        //显然，对于连续的一段(长度为k)，我们一次全部消除是最优的，得分k^2
        //如果正向来看，每次操作会使得数组改变，我们不妨逆向考虑
        //最好将同样的数字合起来一起操作，即我们可以储存一些数字，最后一块算，这样收益最大
        //dp需要开三维
        dp.assign(105, vector<vector<ll>>(105, vector<ll>(105, -1)));
        return dfs(boxes, 0, n - 1, 0);
    }
};