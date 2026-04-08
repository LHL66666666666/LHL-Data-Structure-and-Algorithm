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
int n, m;
vector<vector<int>> g;
vector<int> dep;
vector<int> dis;
vector<vector<int>> st;
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    if (u != 1) {
        dis[u] = dis[fa] + 1;
        st[u][0] = fa;
    }
    for (int j = 1; j <= 20; j++) {
        st[u][j] = st[st[u][j - 1]][j - 1];
    }
    for (auto& v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}
int lca(int v1, int v2) {
    if (dep[v1] < dep[v2]) swap(v1, v2);
    int stp1 = dep[v1] - dep[v2];
    int pos1 = v1, pos2 = v2;
    for (int j = 20; j >= 0; j--) {
        if (stp1 >= (1LL << j)) {
            pos1 = st[pos1][j];
            stp1 -= (1LL << j);
        }
    }
    if (pos1 == pos2) {
        return pos1;
    }
    for (int j = 20; j >= 0; j--) {
        if (dep[pos1] - (1LL << j) > 0) {
            if (st[pos1][j] != st[pos2][j]) {
                pos1 = st[pos1][j];
                pos2 = st[pos2][j];
            }
        }
    }
    return st[pos1][0];
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    g.assign(n + 1, vector<int>());
    dep.assign(n + 1, 0);
    dis.assign(n + 1, 0);
    st.assign(n + 1, vector<int>(21));
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    //钦定1为根节点
    dis[1] = 0;
    dfs(1, 0);
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        //这三个点最多有2个LCA
        //假设只有1个LCA，那么三个点都到哪里汇聚
        //假设有两个，那么在那个dep较大的点汇聚
        int l1 = lca(x, y), l2 = lca(x, z), l3 = lca(y, z);
        //分析结构可知，如果l1,l2相等，那么l1=l2一定是那个较高的LCA
        //如果不相等，dep小的那个一定是较高的LCA
        int high = 0, low = 0;
        int ans = 0;
        if (l1 == l2) {
            high = l1;
            if (dep[l3] > dep[high]) {
                //y,z先汇聚到l3,x再前往l3
                ans = (dis[y] + dis[z] - 2 * dis[l3]) + (dis[x] + dis[l3] - 2 * dis[l1]);
            }
            else {
                //dep[l3]==dep[high]
                ans = dis[x] + dis[y] + dis[z] - 3 * dis[l3];
            }
            cout << l3 << ' ' << ans << '\n';
        }
        else {
            if (dep[l1] < dep[l2]) {
                high = l1;
                low = l2;
                ans = (dis[x] + dis[z] - 2 * dis[low]) + (dis[low] + dis[y] - 2 * dis[high]);
            }
            else {
                high = l2;
                low = l1;
                ans = (dis[x] + dis[y] - 2 * dis[low]) + (dis[low] + dis[z] - 2 * dis[high]);
            }
            cout << low << ' ' << ans << '\n';
        }
    }

    return 0;
}