#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
// constexpr ll MOD=998244353;
constexpr ll MOD = 1e9 + 7;
int n;
vector<vector<pair<int, ll>>> g;
//树形dp的方法求树的直径(边权可能为负数)
//dis[u]表示节点u向下能达到的最远距离(注意从0开始，因为边权可能为负数)
vector<ll> dis;
//len[u]表示经过一定节点u的最长链的长度
vector<ll> len;
void dfs(int u, int fa) {
    //dfs时维护以u为根的dis的最大值和次大值(注意从0开始)
    ll mx1 = 0, mx2 = 0;
    for (auto& e : g[u]) {
        int v = e.first;
        ll w = e.second;
        if (v == fa) continue;
        dfs(v, u);
        ll cur = w + dis[v];
        if (cur > mx1) {
            mx2 = mx1;
            mx1 = cur;
        }
        else if (cur > mx2) {
            mx2 = cur;
        }
    }
    dis[u] = mx1;
    len[u] = mx1 + mx2;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    g.assign(n + 1, vector<pair<int, ll>>());
    dis.assign(n + 1, 0);
    len.assign(n + 1, 0);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    dfs(1, 0);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, len[i]);
    }
    cout << ans << '\n';



    return 0;
}