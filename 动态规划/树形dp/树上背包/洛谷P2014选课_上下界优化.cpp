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
vector<int> val;
vector<int> siz;
vector<vector<int>> dp;
void dfs0(int u) {
    siz[u] = 1;
    for (auto& v : g[u]) {
        dfs0(v);
        siz[u] += siz[v];
    }
}
//dp[u][j]表示以u为根节点的子树，选择体积不超过j的物品，得到的最大价值
//实际上是树上分组背包，把一个子树与父亲的关系看作一个分组背包，
//对于不同的容量j，价值应该是在子树里选k个与非该子树中选j−k个的价值
void dfs(int u) {
    //p代表已经处理过的节点的总个数，我们当前能选的总容量不会超过p
    //要给父节点留一个位置
    int p = 1;
    dp[u][1] = val[u];
    for (auto& v : g[u]) {
        dfs(v);
        //j>siz[pos]+siz[i]就没有计算的必要了，
        //因为根本调用不到这个值
        for (int j = min(p + siz[v], m + 1); j >= 1; j--) {
            //k之所以要<=siz[v]是因为下面调用了f[i][k]，
            //如果k>siz[v]是没有必要遍历的，子树一共就siz[v]个节点
            //j-k>=1，必须给父亲留一个位置
            for (int k = 0; k <= siz[v] && k < j; k++) {
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
    //由于这是一个森林，我们不妨设置一个源点0，
    //0节点连接所有没有先修课的节点，学分为0
    //加上0，一共能选n+1门
    val.assign(n + 1, 0);
    siz.assign(n + 1, 0);
    g.assign(n + 1, vector<int>());
    for (int i = 1; i <= n; i++) {
        int k, s;
        cin >> k >> s;
        g[k].emplace_back(i);
        val[i] = s;
    }
    dp.assign(n + 1, vector<int>(m + 5, 0));
    dfs0(0);
    dfs(0);
    cout << dp[0][m + 1] << '\n';
    return 0;
}