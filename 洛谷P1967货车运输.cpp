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
int n, m, q;
struct node {
    int u, v, w;
    bool operator>(const node& o)const {
        return w > o.w;
    }
};
vector<node> edge;
vector<vector<pair<int, int>>> g;
vector<int> dep;
vector<vector<int>> st1;
vector<vector<int>> st2;
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
void dfs(int u, int fa, int w) {
    dep[u] = dep[fa] + 1;
    st1[u][0] = fa;
    st2[u][0] = w;
    for (int j = 1; j <= 20; j++) {
        if (dep[u] - (1LL << j) > 0) {
            st1[u][j] = st1[st1[u][j - 1]][j - 1];
        }
        else break;
    }
    for (int j = 1; j <= 20; j++) {
        if (dep[u] - (1LL << j) > 0) {
            st2[u][j] = min(st2[u][j - 1], st2[st1[u][j - 1]][j - 1]);
        }
        else break;
    }
    for (auto& e : g[u]) {
        int v = e.first;
        if (v == fa) continue;
        dfs(v, u, e.second);
    }
}
int query(int v1, int v2) {
    if (dep[v1] < dep[v2]) swap(v1, v2);
    int minw1 = INF, minw2 = INF;
    int stp1 = dep[v1] - dep[v2];
    int pos1 = v1, pos2 = v2;
    for (int j = 20; j >= 0; j--) {
        if (stp1 >= (1LL << j)) {
            minw1 = min(minw1, st2[pos1][j]);
            pos1 = st1[pos1][j];
            stp1 -= (1LL << j);
        }
    }
    if (pos1 == pos2) {
        return minw1;
    }
    for (int j = 20; j >= 0; j--) {
        if (dep[pos1] - (1LL << j) > 0) {
            if (st1[pos1][j] != st1[pos2][j]) {
                minw1 = min(minw1, st2[pos1][j]);
                minw2 = min(minw2, st2[pos2][j]);
                pos1 = st1[pos1][j];
                pos2 = st1[pos2][j];
            }
        }
    }
    minw1 = min(minw1, st2[pos1][0]);
    minw2 = min(minw2, st2[pos2][0]);
    return min(minw1, minw2);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    //瓶颈是路径上的最小值
    //如果有多条道路，只需要保留边权最大者
    //需要保证连通性，所以只需要最大生成树即可，其余边权较小的边可以全部忽略
    //实际上这是一个最大生成森林
    DSU dsu(n + 1);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        edge.emplace_back(u, v, w);
    }
    sort(edge.begin(), edge.end(), greater<>());
    g.assign(n + 1, vector<pair<int, int>>());
    dep.assign(n + 1, 0);
    st1.assign(n + 1, vector<int>(20));
    st2.assign(n + 1, vector<int>(20));
    for (auto& e : edge) {
        int u = e.u, v = e.v, w = e.w;
        int fu = dsu.find(u), fv = dsu.find(v);
        if (fu != fv) {
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
            dsu.unite(u, v);
        }
    }
    //任意钦定一个根节点
    //需要求出任意两点之间路径上边权的最小值
    //倍增维护两个信息，
    //一个是去往的节点，一个是这个节点到去往的节点的路径上的边权的最小值
    for (int i = 1; i <= n; i++) {
        //注意这个图中会有多个连通分量
        if (dsu.find(i) == i) {
            dfs(i, 0, 0);
        }
    }
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (dsu.find(x) != dsu.find(y)) {
            cout << -1 << '\n';
            continue;
        }
        int cur = query(x, y);
        cout << cur << '\n';
    }
    return 0;
}