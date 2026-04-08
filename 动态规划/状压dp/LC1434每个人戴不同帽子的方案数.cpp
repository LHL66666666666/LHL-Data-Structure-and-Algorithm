#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
class Solution {
public:
    vector<vector<ll>> dp;
    vector<vector<int>> a;
    //status表示人的状态,0表示已满足,1表示未满足
    //cur表示当前的帽子
    //我们按照每个帽子的顺序来处理，遍历帽子
    ll dfs(int status,int cur)
    {
        if (cur > 40)
        {
            return status == 1;
        }
        if (dp[status][cur] != -1) return dp[status][cur];
        ll ans = 0;
        //可能性1：要cur号颜色的帽子
        for (auto& e : a[cur])
        {
            if (status & (1 << e))
            {
                ans += dfs(status ^ (1 << e), cur + 1) % MOD;
            }
        }
        //可能性2：不要cur号颜色的帽子
        ans += dfs(status, cur + 1);
        ans %= MOD;
        dp[status][cur] = ans;
        return ans;
    }
    int numberWays(vector<vector<int>>& hats) {
        int n = hats.size();
        //朴素的想法是拿帽子是否使用过来做状态压缩，但是帽子数量太大，
        //因此进行一步转化，我们将人是否满足需求来做状态
        //本来是人选择帽子，现在转化为，
        //对于每一种颜色的帽子，选定一个喜欢这种颜色的帽子的人，来进行递归
        //先进行一步预处理，
        //我们创建一个新的列表，每种帽子的颜色后面接着喜欢这种帽子颜色的人
        //这里人编号定为1-n
        a.resize(41);
        for (int i = 0; i < n; i++)
        {
            int n1 = hats[i].size();
            for (int j = 0; j < n1; j++)
            {
                a[hats[i][j]].emplace_back(i+1);
            }
        }
        int s = (1 << (n + 1)) - 1;
        dp.assign(s + 1, vector<ll>(41, -1));
        return dfs(s, 1);
    }
};