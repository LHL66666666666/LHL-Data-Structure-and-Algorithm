#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
int T;
int n, m;
int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<vector<pair<int, ll>>> g(n + 1);
    vector<int> in(n + 1, 0);
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        in[v]++;
    }
    //由于要找1为起点，n为终点的最长路
    //先将无用的点的影响排除
    //并不保证只有点1是没有入度的。所以要判断其他没有入度的点。
    //一开始会想到加入队列，那就错了，他们本身是无法到达的点，所以根本不可能会延伸到其他地方，
    //如果加入队列，那么就会导致个别点，甚至所有点的答案错误。
    //那么就是不管他？还是错，如果不管，那么他们延伸出来的点的入度永远大于0，因为还有那些点。
    //以至于发生和上一种方法一样的错误，甚至使终点无法到达，
    //那么解决方法就是找到那些点，再把延伸出来的点的入度 −1，如果这些点入读 −1 后又变成了入度为 0 的点，
    //那么再做同样的处理
    //相当于将无关的路全部剪掉
    queue<int> q;
    for (int i = 2; i <= n; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto& v : g[cur]) {
            --in[v.first];
            if (in[v.first] == 0) q.push(v.first);
        }
    }
    queue<pair<int, ll>> qe;
    vector<ll> dis(n + 1, -INF);
    qe.emplace(1, 0);
    dis[1] = 0;
    while (!qe.empty()) {
        auto cur = qe.front();
        qe.pop();
        int u = cur.first;
        for (auto& v : g[u]) {
            if (dis[v.first] < dis[u] + v.second) dis[v.first] = dis[u] + v.second;
            in[v.first]--;
            if (in[v.first] == 0) qe.emplace(v.first, dis[v.first]);
        }
    }
    if (dis[n] != -INF) cout << dis[n] << '\n';
    else cout << "-1\n";
    return 0;
}