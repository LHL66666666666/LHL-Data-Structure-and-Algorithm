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
int T;
int n, m;
vector<ll> a;
//区间累加和
vector<ll> sum;
//区间最大值
vector<ll> mx;
//区间最大值的个数
vector<ll> cnt;
//区间严格次大值
vector<ll> sec;
//区间最大值的改变量(懒更新信息)
vector<ll> mxadd;
//区间最大值以外的值的改变量(懒更新信息)
vector<ll> otheradd;
//区间历史最大值
vector<ll> mxhistory;
//区间最大值的历史最大增幅(懒更新信息)
vector<ll> mxaddtop;
//区间最大值以外的值的历史最大增幅(懒更新信息)
vector<ll> otheraddtop;
void up(int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    if (mx[i << 1] > mx[i << 1 | 1]) {
        mx[i] = mx[i << 1];
        cnt[i] = cnt[i << 1];
        sec[i] = max(sec[i << 1], mx[i << 1 | 1]);
    }
    else if (mx[i << 1] < mx[i << 1 | 1]) {
        mx[i] = mx[i << 1 | 1];
        cnt[i] = cnt[i << 1 | 1];
        sec[i] = max(mx[i << 1], sec[i << 1 | 1]);
    }
    else {
        mx[i] = mx[i << 1];
        cnt[i] = cnt[i << 1] + cnt[i << 1 | 1];
        sec[i] = max(sec[i << 1], sec[i << 1 | 1]);
    }
    mxhistory[i] = max(mxhistory[i << 1], mxhistory[i << 1 | 1]);
}
//注意：以下参数的含义仅限于一个懒标记周期内
//addmx:最大值增加量
//addother:其他值增加量
//upmx:本次操作对“最大值部分”的历史最大增幅贡献
//upother:本次操作对“非最大值部分”的历史最大增幅贡献
void lazy(int i, int num, ll addmx, ll addother, ll upmx, ll upother) {
    mxhistory[i] = max(mxhistory[i], mx[i] + upmx);
    mxaddtop[i] = max(mxaddtop[i], mxadd[i] + upmx);
    otheraddtop[i] = max(otheraddtop[i], otheradd[i] + upother);
    sum[i] += cnt[i] * addmx + 1LL * (num - cnt[i]) * addother;
    mx[i] += addmx;
    if (sec[i] != -INF) sec[i] += addother;
    mxadd[i] += addmx;
    otheradd[i] += addother;
}
void down(int i, int ln, int rn) {
    ll tmp = max(mx[i << 1], mx[i << 1 | 1]);
    //在父节点积累的这一系列未下传的操作中，最大值部分最多曾比原始值高出 mxaddtop[i]。
    //现在我把这些操作打包下传给你（子节点），你要用这个信息去更新你的历史最大值
    if (tmp == mx[i << 1]) {
        lazy(i << 1, ln, mxadd[i], otheradd[i], mxaddtop[i], otheraddtop[i]);
    }
    else {
        lazy(i << 1, ln, otheradd[i], otheradd[i], otheraddtop[i], otheraddtop[i]);
    }
    if (tmp == mx[i << 1 | 1]) {
        lazy(i << 1 | 1, rn, mxadd[i], otheradd[i], mxaddtop[i], otheraddtop[i]);
    }
    else {
        lazy(i << 1 | 1, rn, otheradd[i], otheradd[i], otheraddtop[i], otheraddtop[i]);
    }
    //清空懒标记
    mxadd[i] = otheradd[i] = mxaddtop[i] = otheraddtop[i] = 0;
}
void build(int i, int l, int r) {
    if (l == r) {
        sum[i] = a[l];
        mx[i] = a[l];
        cnt[i] = 1;
        sec[i] = -INF;
        mxhistory[i] = a[l];
        return;
    }
    int mid = (r + l) >> 1;
    build(i << 1, l, mid);
    build(i << 1 | 1, mid + 1, r);
    up(i);
}
void setmin(int ql, int qr, ll qv, int i, int l, int r) {
    if (qv >= mx[i]) {
        return;
    }
    if (ql <= l && r <= qr && qv > sec[i]) {
        lazy(i, r - l + 1, qv - mx[i], 0, qv - mx[i], 0);
        return;
    }
    int mid = (r + l) >> 1;
    down(i, mid - l + 1, r - mid);
    if (ql <= mid) {
        setmin(ql, qr, qv, i << 1, l, mid);
    }
    if (qr > mid) {
        setmin(ql, qr, qv, i << 1 | 1, mid + 1, r);
    }
    up(i);
}
void update_add(int ql, int qr, ll qv, int i, int l, int r) {
    if (ql <= l && r <= qr) {
        lazy(i, r - l + 1, qv, qv, qv, qv);
        return;
    }
    int mid = (r + l) >> 1;
    down(i, mid - l + 1, r - mid);
    if (ql <= mid) {
        update_add(ql, qr, qv, i << 1, l, mid);
    }
    if (qr > mid) {
        update_add(ql, qr, qv, i << 1 | 1, mid + 1, r);
    }
    up(i);
}
ll querysum(int ql, int qr, int i, int l, int r) {
    if (ql <= l && r <= qr) return sum[i];
    int mid = (r + l) >> 1;
    down(i, mid - l + 1, r - mid);
    ll ans = 0;
    if (ql <= mid) {
        ans += querysum(ql, qr, i << 1, l, mid);
    }
    if (qr > mid) {
        ans += querysum(ql, qr, i << 1 | 1, mid + 1, r);
    }
    return ans;
}
ll querymax(int ql, int qr, int i, int l, int r) {
    if (ql <= l && r <= qr) return mx[i];
    int mid = (r + l) >> 1;
    down(i, mid - l + 1, r - mid);
    ll ans = -INF;
    if (ql <= mid) {
        ans = max(ans, querymax(ql, qr, i << 1, l, mid));
    }
    if (qr > mid) {
        ans = max(ans, querymax(ql, qr, i << 1 | 1, mid + 1, r));
    }
    return ans;
}
ll queryhistory(int ql, int qr, int i, int l, int r) {
    if (ql <= l && r <= qr) return mxhistory[i];
    int mid = (r + l) >> 1;
    down(i, mid - l + 1, r - mid);
    ll ans = -INF;
    if (ql <= mid) {
        ans = max(ans, queryhistory(ql, qr, i << 1, l, mid));
    }
    if (qr > mid) {
        ans = max(ans, queryhistory(ql, qr, i << 1 | 1, mid + 1, r));
    }
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    sum.assign(n << 2, 0);
    mx.assign(n << 2, 0);
    cnt.assign(n << 2, 0);
    sec.assign(n << 2, 0);
    mxadd.assign(n << 2, 0);
    otheradd.assign(n << 2, 0);
    mxhistory.assign(n << 2, 0);
    mxaddtop.assign(n << 2, 0);
    otheraddtop.assign(n << 2, 0);
    build(1, 1, n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            ll k;
            cin >> l >> r >> k;
            update_add(l, r, k, 1, 1, n);
        }
        else if (op == 2) {
            int l, r;
            ll v;
            cin >> l >> r >> v;
            setmin(l, r, v, 1, 1, n);
        }
        else if (op == 3) {
            int l, r;
            cin >> l >> r;
            cout << querysum(l, r, 1, 1, n) << '\n';
        }
        else if (op == 4) {
            int l, r;
            cin >> l >> r;
            cout << querymax(l, r, 1, 1, n) << '\n';
        }
        else if (op == 5) {
            int l, r;
            cin >> l >> r;
            cout << queryhistory(l, r, 1, 1, n) << '\n';
        }
    }
    return 0;
}