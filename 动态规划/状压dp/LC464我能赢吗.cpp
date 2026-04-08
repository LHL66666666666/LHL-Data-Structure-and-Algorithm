#include <vector>
#include <string>
using namespace std;
typedef long long ll;
class Solution {
public:
    vector<int> dp;
    //status表示当前状态，rest表示还剩多少达到要求的累加和
    //dfs(status,rest)表示在当前玩家为先手的情况下，是否存在必胜策略
    //dp表只需要一个参数status，原因是，status一旦确定，那么rest也是被status所确定的
    //因此不需要rest这一维参数
    int dfs(int status,int rest,int n)
    {
        if (rest <= 0)
        {
            return 0;
        }
        if (dp[status] != -1) return dp[status];
        //枚举每种选择，如果存在对手必输的状态，则表示有先手必赢策略
        //理解：实际上我们可以从最后一步来思考，最后一步一定有先手/后手必胜策略，再逐级向前推
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            //如果这个数字能选
            //且选这个数字之后，后手是必败
            if ((status & (1 << i)) && !dfs((status ^ (1 << i)), rest - i, n))
            {
                ans = 1;
                break;
            }
        }
        dp[status] = ans;
        //这样做的逻辑：如果存在对手必败策略，那么必胜，
        //反之，对手轮次的返回值均为1，对手是必胜的，则自己必败
        return ans;
    }
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        int n = maxChoosableInteger, m = desiredTotal;
        //如果可以一次取够
        if (n >= m)
        {
            return true;
        }
        //如果取了所有的数字还是不够
        if (n * (n + 1) / 2 < m)
        {
            return false;
        }
        dp.assign((1LL << (n + 1))+1, -1);
        return dfs((1 << (n + 1)) - 1, m, n);
    }
};