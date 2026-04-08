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
int T;
int n;
vector<vector<int>> g;
vector<int> siz;
vector<int> deg;
int ct1, ct2, cnt1, cnt2;
void dfs(int u, int fa) {
    siz[u] = 1;
    int tmp = 0;
    for (auto& v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];
        tmp = max(tmp, siz[v]);
    }
    tmp = max(tmp, n - siz[u]);
    if (tmp < cnt1) {
        ct2 = ct1, cnt2 = cnt1;
        ct1 = u, cnt1 = tmp;
    }
    else if (tmp < cnt2) {
        ct2 = u, cnt2 = tmp;
    }
}
pair<int, int> eg1 = {};
void dfs1(int u, int fa) {
    if (deg[u] == 1) {
        eg1.first = u, eg1.second = fa;
        return;
    }
    for (auto& v : g[u]) {
        if (v == fa) continue;
        dfs1(v, u);
    }
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n;
        g.assign(n + 1, vector<int>());
        siz.assign(n + 1, 0);
        deg.assign(n + 1, 0);
        pair<int, int> eg0 = {};
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            if (i == 1) eg0.first = u, eg0.second = v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
            deg[u]++;
            deg[v]++;
        }
        //如果只有一个重心，那么不用动，
        //如果有两个，那么这两个相邻，只需要从一个重心一侧拆下一个叶节点，然后连接到另一个重心上
        ct1 = 0, ct2 = 0, cnt1 = INF, cnt2 = INF;
        dfs(1, 0);
        if (cnt1 < cnt2) {
            cout << eg0.first << ' ' << eg0.second << '\n';
            cout << eg0.first << ' ' << eg0.second << '\n';
            continue;
        }
        dfs1(ct2, ct1);
        cout << eg1.first << ' ' << eg1.second << '\n';
        cout << eg1.first << ' ' << ct1 << '\n';

    }

    return 0;
}