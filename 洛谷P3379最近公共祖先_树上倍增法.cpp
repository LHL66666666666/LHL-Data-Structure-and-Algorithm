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
vector<vector<int>> g;
vector<vector<int>> st;
vector<int> dep;
int tot;
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    st[u][0] = fa;
    for (int j = 1; j <= tot; j++) {
        if (dep[u] - (1LL << j) > 0) {
            st[u][j] = st[st[u][j - 1]][j - 1];
        }
    }
    for (auto& v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
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
    tot = __lg(n);
    st.assign(n + 1, vector<int>(tot + 1));
    dep.assign(n + 1, 0);
    dfs(s, 0);
    while (m--) {
        int a, b;
        cin >> a >> b;
        //先将两个点移动到同一深度
        if (dep[a] < dep[b]) swap(a, b);
        int stp1 = dep[a] - dep[b];
        int pos1 = a, pos2 = b;
        for (int j = tot; j >= 0; j--) {
            if (stp1 >= (1LL << j)) {
                stp1 -= (1LL << j);
                pos1 = st[pos1][j];
            }
        }
        //如果移动之后两个重合
        if (pos1 == pos2) {
            cout << pos1 << '\n';
            continue;
        }
        for (int j = tot; j >= 0; j--) {
            if (dep[pos1] - (1LL << j) > 0) {
                if (st[pos1][j] != st[pos2][j]) {
                    pos1 = st[pos1][j];
                    pos2 = st[pos2][j];
                }
            }
        }
        cout << st[pos1][0] << '\n';




    }




    return 0;
}