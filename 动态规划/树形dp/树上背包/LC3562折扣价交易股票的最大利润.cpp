#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr ll MOD = 998244353;
// constexpr ll MOD=1e9+7;
class Solution {
public:
    int b;
    vector<vector<int>> g;
    //dfs(u,j,k)表示以u为根节点，花费不超过j，是否有优惠(k=1表示有优惠)，取得的最大利润
    vector<vector<vector<int>>> dp;
    //k=1表示有优惠,k=0表示没有优惠，花费可以表示为p[u]/(k+1)
    void dfs(int u, vector<int>& p, vector<int>& f) {
        //先递归子节点，计算出子节点对应k=1,k=0的sub[j][k],这是分组背包
        //对于节点u,我们先计算一个sub(j,0/1)
        //表示它的所有子节点的子树一共花了j的预算，且u有(1)没有(0)买股票的最大收益
        vector<vector<int>> sub(b + 1, vector<int>(2, 0));
        for (auto& v : g[u]) {
            dfs(v, p, f);
            //01背包的空间压缩，倒序枚举
            for (int j = b; j >= 0; j--) {
                //j表示遍历过的所有儿子的总预算
                for (int m = 0; m <= j; m++) {
                    //m表示分给新一个儿子的预算
                    for (int k = 0; k < 2; k++) {
                        sub[j][k] = max(sub[j][k], sub[j - m][k] + dp[v][m][k]);
                    }
                }
            }
        }
        //计算自己
        //如果自己不买，转移来源是sub[j][0]
        for (int j = 0; j <= b; j++) {
            dp[u][j][0] = dp[u][j][1] = sub[j][0];
        }
        //如果自己买，转移来源是sub[j][1]
        for (int j = 0; j <= b; j++) {
            if (j - p[u - 1] >= 0) {
                int x = j - p[u - 1];
                dp[u][j][0] = max(dp[u][j][0], sub[j - p[u - 1]][1] + f[u - 1] - p[u - 1]);
            }
            if (j - p[u - 1] / 2 >= 0) {
                int x = j - p[u - 1] / 2;
                dp[u][j][1] = max(dp[u][j][1], sub[j - p[u - 1] / 2][1] + f[u - 1] - p[u - 1] / 2);
            }
        }
    }
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        auto& p = present;
        auto& f = future;
        auto& h = hierarchy;
        b = budget;
        g.assign(n + 1, vector<int>());
        for (int i = 0; i < n - 1; i++) {
            g[h[i][0]].emplace_back(h[i][1]);
        }
        dp.assign(n + 1, vector(b + 1, vector<int>(2)));
        dfs(1, p, f);
        int ans = dp[1][b][0];
        return ans;
    }
};