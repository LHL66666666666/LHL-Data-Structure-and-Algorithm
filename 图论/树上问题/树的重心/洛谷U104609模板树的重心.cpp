//解法1
//利用性质：以某个节点为根时，最大子树的节点数最少，那么这个节点是重心
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
vector<vector<int>> g;
vector<int> siz;
int rt1, sz1, rt2, sz2;
void dfs(int u, int fa) {
    siz[u] = 1;
    int tmp = 0;
    for (auto& v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        tmp = max(tmp, siz[v]);
        siz[u] += siz[v];
    }
    tmp = max(tmp, n - siz[u]);
    if (tmp < sz1) {
        rt2 = rt1;
        sz2 = sz1;
        sz1 = tmp;
        rt1 = u;
    }
    else if (tmp < sz2) {
        rt2 = u;
        sz2 = tmp;
    }
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    g.assign(n + 1, vector<int>());
    siz.assign(n + 1, 0);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    rt1 = 0, rt2 = 0;
    sz1 = INF, sz2 = INF;
    dfs(1, 0);
    if (sz1 == sz2) {
        if (rt1 > rt2) swap(rt1, rt2);
        cout << rt1 << ' ' << rt2 << '\n';
    }
    else {
        cout << rt1 << '\n';
    }

    return 0;
}


//解法2
//利用性质：以某个节点为根时，最大子树的节点数最少，那么这个节点是重心
//#include <bits/stdc++.h>
//using namespace std;
//using ll = long long;
//using i128 = __int128;
//constexpr int INF = 0x3f3f3f3f;
//constexpr ll MOD = 998244353;
//// constexpr ll MOD=1e9+7;
//int n;
//vector<vector<int>> g;
//vector<int> siz;
//int rt1, rt2;
//void dfs(int u, int fa) {
//    siz[u] = 1;
//    int tmp = 0;
//    for (auto& v : g[u]) {
//        if (v == fa) continue;
//        dfs(v, u);
//        tmp = max(tmp, siz[v]);
//        siz[u] += siz[v];
//    }
//    tmp = max(tmp, n - siz[u]);
//    if (tmp <= n / 2) {
//        if (rt1 == 0) rt1 = u;
//        else rt2 = u;
//    }
//}
//int main() {
//    // ifstream cin("input.txt");
//    // ofstream cout("output.txt");
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cin >> n;
//    g.assign(n + 1, vector<int>());
//    siz.assign(n + 1, 0);
//    for (int i = 1; i <= n - 1; i++) {
//        int u, v;
//        cin >> u >> v;
//        g[u].emplace_back(v);
//        g[v].emplace_back(u);
//    }
//    rt1 = 0, rt2 = 0;
//    dfs(1, 0);
//    if (rt1 != 0 && rt2 != 0) {
//        if (rt1 > rt2) swap(rt1, rt2);
//        cout << rt1 << ' ' << rt2 << '\n';
//    }
//    else cout << rt1 << '\n';
//    return 0;
//}