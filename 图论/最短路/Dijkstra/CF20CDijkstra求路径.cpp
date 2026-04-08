//#include <bits/stdc++.h>
//typedef long long ll;
//using namespace std;
//int n, m;
//int ui, vi, wi;
//auto cmp = [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
//    return a.second > b.second;
//    };
//constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
//int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cin >> n >> m;
//    vector<vector<pair<int, int>>> g(n + 1);
//    while (m--) {
//        cin >> ui >> vi >> wi;
//        g[ui].push_back({ vi,wi });
//        g[vi].push_back({ ui,wi });
//    }
//    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, decltype(cmp)> pq(cmp);
//    vector<ll> dis(n + 1, INF);
//    vector<int> vis(n + 1, 0);
//    //pre记录最后一次被谁更新
//    vector<int> pre(n + 1);
//    dis[1] = 0;
//    pq.push({ 1,0 });
//    while (!pq.empty()) {
//        ll u = pq.top().first, cur = pq.top().second;
//        pq.pop();
//        if (vis[u]) continue;
//        vis[u] = 1;
//        if (u == n) {
//            break;
//        }
//        for (auto& i : g[u]) {
//            ll v = i.first, w = i.second;
//            if (!vis[v] && w + cur < dis[v]) {
//                dis[v] = w + cur;
//                //更新dis[v]的是u这一条边
//                pre[v] = u;
//                pq.push({ v,w + cur });
//            }
//        }
//    }
//    // cout<<dis[n]<<'\n';
//    if (dis[n] == INF) {
//        cout << -1 << '\n';
//        return 0;
//    }
//    vector<int> ans;
//    ans.emplace_back(n);
//    for (int i = pre[n]; i != 1;) {
//        ans.emplace_back(i);
//        i = pre[i];
//    }
//    ans.emplace_back(1);
//    reverse(ans.begin(), ans.end());
//    for (auto& i : ans) {
//        cout << i << ' ';
//    }
//    cout << '\n';
//    return 0;
//}