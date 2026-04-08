#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;
class Solution {
public:
    vector<int> dp;
    //status再次唯一确定了cur和rest
    //原因是我们再调用过程中，不会调用违规状态，也就是加上一条边之后边长大于要求边长的违规状态
    //因此我们保证每一种status对应的都是已经满足了一些边，当前在凑的这条边为cur，还剩rest条边的状态
    int dfs(int status, ll cur, int rest,ll len,int n, vector<int>& a)
    {
        if (rest == 0)
        {
            return 1;
        }
        if (dp[status] != -1) return dp[status];
        int ans = 0;
        //枚举每种选择
        //这里要与数组下标对齐
        for (int i = 0; i <= n-1; i++)
        {
            //找能选的位置
            if ((status & (1 << i)))
            {
                if (cur + a[i] == len)
                {
                    ans |= dfs((status ^ (1 << i)), 0, rest - 1, len, n, a);
                }
                else if (cur + a[i] < len)
                {
                    ans |= dfs((status ^ (1 << i)), cur + a[i], rest, len, n, a);
                }
            }
        }
        dp[status] = ans;
        return ans;
    }
    bool makesquare(vector<int>& matchsticks) {
        //钦定一个正方形的边长，检查能否达到这个边长的正方形
        //实际上，由于要使用所有的火柴，长度之和必须是4的倍数
        int n = matchsticks.size();
        if (n < 4) return false;
        ll sum = 0;
        for (int i = 0; i < n; i++) sum += matchsticks[i];
        if (sum % 4 != 0) return false;
        //确定边长
        ll len = sum / 4;
        //在n个里面组合，要凑出4个边长来
        //朴素的想法：记录当前状态status表示还有哪些边可以选择，
        //cur表示当前在拼的这个边长度到了多少，rest表示还差几条边拼完
        //但是！dp表不需要开三维，因为status再次唯一确定了cur和rest
        dp.assign((1LL << (n + 1)), -1);
        //这里我们将status设置为n个1即可，为了与数组下标对齐
        return dfs((1 << (n + 1)) - 1, 0, 4, len, n, matchsticks);
    }
};