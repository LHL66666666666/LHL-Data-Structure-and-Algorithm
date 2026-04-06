#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
// constexpr ll MOD=1e9+7;
int T;
int n, m;
vector<int> mx;
vector<int> reset;
vector<int> upd;
void up(int i) {
    mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
}
void lazy(int i, int qv) {
    mx[i] = qv;
    reset[i] = qv;
    upd[i] = 1;
}
void down(int i) {
    if (upd[i]) {
        lazy(i << 1, reset[i]);
        lazy(i << 1 | 1, reset[i]);
        upd[i] = 0;
    }
}
void update(int ql, int qr, int qv, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        lazy(i, qv);
        return;
    }
    int mid = (l + r) >> 1;
    down(i);
    if (ql <= mid) {
        update(ql, qr, qv, l, mid, i << 1);
    }
    if (qr > mid) {
        update(ql, qr, qv, mid + 1, r, i << 1 | 1);
    }
    up(i);
}
int query(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return mx[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    int ans = -INF;
    if (ql <= mid) {
        ans = max(ans, query(ql, qr, l, mid, i << 1));
    }
    if (qr > mid) {
        ans = max(ans, query(ql, qr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<int> a(m + 1);
    vector<int> b(m + 1);
    vector<int> pos(1, 0);
    for (int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i];
        //注意这里离散化的时候记得多加几个边界进去，
        //因为直接离散化会使本来不相邻的变成相邻的
        //例如
        //10 3
        //1 10
        //1 4
        //6 10
        //比如5就被跳过了，这样就导致本来1号海报露出来的5位置被覆盖掉了
        pos.emplace_back(a[i]);
        pos.emplace_back(a[i] - 1);
        pos.emplace_back(a[i] + 1);
        pos.emplace_back(b[i]);
        pos.emplace_back(b[i] - 1);
        pos.emplace_back(b[i] + 1);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    n = pos.size();
    mx.assign(n << 2, 0);
    reset.assign(n << 2, 0);
    upd.assign(n << 2, 0);
    for (int i = 1; i <= m; i++) {
        auto s = lower_bound(pos.begin(), pos.end(), a[i]) - pos.begin();
        auto e = lower_bound(pos.begin(), pos.end(), b[i]) - pos.begin();
        update(s, e, i, 1, n, 1);
    }
    set<int> s;
    for (int i = 1; i <= n; i++) {
        int x = query(i, i, 1, n, 1);
        if (x > 0) s.insert(x);
        // cout<<x<<" ";
    }
    cout << s.size() << '\n';
    return 0;
}