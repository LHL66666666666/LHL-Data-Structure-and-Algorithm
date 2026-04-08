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
int n;
vector<int> c;
vector<vector<pair<int, int>>> g;
vector<int> siz;
int rt;
int tot;
void dfs0(int u, int fa) {
    siz[u] = c[u];
    int tmp = 0;
    for (auto& v : g[u]) {
        if (v.first == fa) continue;
        dfs0(v.first, u);
        tmp = max(tmp, siz[v.first]);
        siz[u] += siz[v.first];
    }
    tmp = max(tmp, tot - siz[u]);
    if (tmp <= tot / 2) {
        rt = u;
    }
}
vector<int> dis;
void dfs(int u, int fa, int w) {
    if (fa != 0) {
        dis[u] = dis[fa] + w;
    }
    for (auto& v : g[u]) {
        if (v.first == fa) continue;
        dfs(v.first, u, v.second);
    }
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    c.assign(n + 1, 0);
    tot = 0;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        tot += c[i];
    }
    g.assign(n + 1, vector<pair<int, int>>());
    siz.assign(n + 1, 0);
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    //这是一棵带点权的树
    //如果是不带点权的树，那么重心就是最优汇聚点
    //求点权树的重心，就是将点权看作新的size，跟据新的siz按照性质来求重心
    //只需要求出一个来即可
    rt = 0;
    dfs0(1, 0);
    //根节点已经确定下来为rt
    dis.assign(n + 1, 0);
    dfs(rt, 0, 0);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += 1LL * c[i] * dis[i];
    }
    cout << ans << '\n';
    return 0;
}
/*
可以这样想来方便理解：我们将点权w看作w个相同的节点打包在一起，
因此，我们计算点权树的重心时，
只需要将点权作为每个节点的siz，然后按照正常树的重心的思路来求即可
同时本题利用了重心的性质：
如果树上的边权都是正数，不管边权具体怎么分布，所有节点走到重心的总距离和最小
*/