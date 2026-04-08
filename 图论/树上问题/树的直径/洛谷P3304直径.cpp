#include <vector>
#include <map>
#include <set>
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
vector<ll> dis;
vector<int> lst;
int start, ed;
ll len;
void dfs0(int u, int fa) {
    for (auto& e : g[u]) {
        int v = e.first;
        ll w = e.second;
        if (v == fa) continue;
        dis[v] = dis[u] + w;
        dfs0(v, u);
    }
}
void dfs1(int u, int fa) {
    for (auto& e : g[u]) {
        int v = e.first;
        ll w = e.second;
        if (v == fa) continue;
        dis[v] = dis[u] + w;
        lst[v] = u;
        dfs1(v, u);
    }
}
set<int> s;
ll tmp;
void dfs(int u, int fa, ll d) {
    tmp = max(tmp, d);
    for (auto& e : g[u]) {
        int v = e.first;
        ll w = e.second;
        if (v == fa || s.find(v) != s.end()) continue;
        dfs(v, u, d + w);
    }
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    g.assign(n + 1, vector<pair<int, ll>>());
    dis.assign(n + 1, 0);
    lst.assign(n + 1, 0);
    //保证边权都为正
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    dis[1] = 0;
    dfs0(1, 0);
    ll mx0 = 0;
    for (int i = 1; i <= n; i++) {
        if (dis[i] > mx0) {
            mx0 = dis[i];
            start = i;
        }
    }
    dis.assign(n + 1, 0);
    dfs1(start, 0);
    ll mx1 = 0;
    for (int i = 1; i <= n; i++) {
        if (dis[i] > mx1) {
            mx1 = dis[i];
            ed = i;
        }
    }
    len = mx1;
    //现在已知一条直径上的所有点
    for (int p = ed; p != 0; p = lst[p]) {
        s.insert(p);
    }
    //每次计算以p为根，不经过直径上任意一点的最大距离
    //和这个点到start和end的距离比较
    int l = 0, r = 0;
    for (int p = ed; p != 0; p = lst[p]) {
        tmp = 0;
        dfs(p, 0, 0);
        //到start和end的距离
        ll d1 = dis[p], d2 = len - dis[p];
        if (tmp == d2) {
            r = p;
        }
        if (tmp == d1 && l == 0) {
            l = p;
        }
    }
    int cnt = 0;
    for (int p = r; p != l; p = lst[p]) {
        ++cnt;
    }
    cout << len << '\n' << cnt << '\n';
    return 0;
}
/*
要求的是所有直径都经过的边数
所以我们先任意求出一条直径，记录这条直径上的点。
再对每个直径上的点都dfs，求出以这个点为起点的最长链（当然不能包括直径上的其它点），长度用maxdis表示
ls表示这个点到直径左端点的距离
rs表示这个点到直径右端点的距离（左右随意定）
这里画画图更好理解
我们需要找到最靠左的rs==maxdis的点r，以及最靠右的ls==maxdis的点l
从右向左遍历直径上的点(也就是从end向start遍历)
如果这个点rs=maxdis，证明这个点一定是在公共路径上的，我们更新r，r始终更新，取最左侧那个
如果这个点ls=maxdis，证明这个点一定是在公共路径上的，我们更新l，注意l只需要更新一次，即为最右侧的l
计算r到l上的边的条数即可
*/