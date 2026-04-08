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
int n, m;
vector<vector<int>> g;
vector<vector<int>> dp;
vector<int> cost;
vector<int> val;
vector<int> siz;
void dfs0(int u) {
    siz[u] = (val[u] != 0);
    for (auto& v : g[u]) {
        dfs0(v);
        siz[u] += siz[v];
    }
}
//dp[u][j]表示以u为根节点，有j个观众，取得的最大收益
//j不会超过m，且子节点的选择依赖于父节点的选择
//观众只在叶子节点上
void dfs(int u) {
    //父亲节点一定选择
    if (val[u] == 0) dp[u][0] = -cost[u];
    else dp[u][1] = val[u] - cost[u];
    int p = (val[u] != 0);
    for (auto& v : g[u]) {
        dfs(v);
        for (int j = min(m, p + siz[v]); j >= 1; j--) {
            for (int k = 0; k <= siz[v] && j - k >= 0; k++) {
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k]);
            }
        }
        p += siz[v];
    }
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    g.assign(n + 1, vector<int>());
    dp.assign(n + 1, vector<int>(m + 1, -INF));
    cost.assign(n + 1, 0);
    val.assign(n + 1, 0);
    siz.assign(n + 1, 0);
    for (int i = 1; i <= n - m; i++) {
        int k;
        cin >> k;
        for (int j = 1; j <= k; j++) {
            int a, c;
            cin >> a >> c;
            g[i].emplace_back(a);
            cost[a] = c;
        }
    }
    for (int i = n - m + 1; i <= n; i++) {
        cin >> val[i];
    }
    dfs0(1);
    dfs(1);
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        if (dp[1][i] >= 0) {
            ans = i;
        }
    }
    cout << ans << '\n';





    return 0;
}