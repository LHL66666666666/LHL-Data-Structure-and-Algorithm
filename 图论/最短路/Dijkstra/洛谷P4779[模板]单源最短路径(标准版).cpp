#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, s;
int u, v, w;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    vector<vector<pair<int, int>>> g(n + 1);
    vector<int> dis(n + 1, INT_MAX);
    vector<int> vis(n + 1);
    //建图
    while (m--) {
        cin >> u >> v >> w;
        g[u].push_back({ v,w });
    }
    //建小根堆，按照到源点距离组织,两个参数：点、目前到源点最短距离
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
        };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    //源点入priority_queue
    pq.push({ s,0 });
    dis[s] = 0;
    while (!pq.empty()) {
        int u1 = pq.top().first;
        pq.pop();
        if (vis[u1]) continue;
        vis[u1] = 1;
        //松弛
        for (auto& edge : g[u1]) {
            int v1 = edge.first;
            int w1 = edge.second;
            if (w1 + dis[u1] < dis[v1]) {
                dis[v1] = w1 + dis[u1];
                pq.push({ v1,dis[v1] });
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << ' ';
    }
    cout << '\n';
    return 0;
}