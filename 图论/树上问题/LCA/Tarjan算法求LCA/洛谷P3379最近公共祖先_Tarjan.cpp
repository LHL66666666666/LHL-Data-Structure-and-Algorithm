#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
// constexpr ll MOD=1e9+7;
int n, m, s;
struct node {
    int v, id;
};
struct DSU {
    vector<size_t> pa, size;
    explicit DSU(size_t size_) : pa(size_), size(size_, 1) {
        iota(pa.begin(), pa.end(), 0);
    }
    size_t find(size_t x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
    void unite(size_t x, size_t y) {
        x = find(x), y = find(y);
        if (x == y) return;
        pa[y] = x;
        size[x] += size[y];
    }
};
vector<vector<int>> g;
vector<int> vis;
vector<vector<node>> q;
vector<int> ans;
void dfs(int u, int fa, DSU& dsu) {
    vis[u] = 1;
    for (auto& v : g[u]) {
        if (v == fa) continue;
        dfs(v, u, dsu);
        //注意，合并的时候，一定要将父节点作为dsu的代表节点
        dsu.unite(u, v);
    }
    //处理任务列表
    for (auto& qu : q[u]) {
        int v = qu.v, id = qu.id;
        if (vis[v]) {
            ans[id] = dsu.find(v);
        }
    }
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    g.assign(n + 1, vector<int>());
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    q.assign(n + 1, vector<node>());
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        q[a].emplace_back(b, i);
        q[b].emplace_back(a, i);
    }
    ans.assign(m + 1, 0);
    vis.assign(n + 1, 0);
    DSU dsu(n + 1);
    dfs(s, 0, dsu);
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }




    return 0;
}