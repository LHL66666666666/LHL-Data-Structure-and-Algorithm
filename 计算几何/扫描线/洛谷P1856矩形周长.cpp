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
int n;
struct node {
    ll x1, y1, x2, y2;
};
vector<ll> x = { -INF };
vector<ll> y = { -INF };
//注意：在对扫描的每次查询做排序的时候，
//如果遇到了矩形边界重合的情况，一定要先加后减
//否则如果先减，会导致多算一块减掉的线段
//hack数据
//2
//0 0 1 1
//1 0 2 1
struct linex {
    ll x, d;
    ll y1, y2;
    bool operator<(const linex& o) const {
        if (x != o.x) return x < o.x;
        return d > o.d;
    }
};
struct liney {
    ll y, d;
    ll x1, x2;
    bool operator<(const liney& o) const {
        if (y != o.y) return y < o.y;
        return d > o.d;
    }
};
vector<linex> qx;
vector<liney> qy;
//线段树
vector<ll> len;
vector<ll> cover;
vector<ll> cnt;
void up(int i, int l, int r) {
    if (cnt[i] > 0) {
        cover[i] = len[i];
    }
    else if (l == r) {
        cover[i] = 0;
    }
    else cover[i] = cover[i << 1] + cover[i << 1 | 1];
}
void build_y(int i, int l, int r) {
    if (l == r) {
        len[i] = y[r + 1] - y[l];
    }
    else {
        len[i] = y[r + 1] - y[l];
        int mid = (l + r) >> 1;
        build_y(i << 1, l, mid);
        build_y(i << 1 | 1, mid + 1, r);
    }
    up(i, l, r);
}
void build_x(int i, int l, int r) {
    if (l == r) {
        len[i] = x[r + 1] - x[l];
    }
    else {
        len[i] = x[r + 1] - x[l];
        int mid = (l + r) >> 1;
        build_x(i << 1, l, mid);
        build_x(i << 1 | 1, mid + 1, r);
    }
    up(i, l, r);
}
void update(int ql, int qr, ll qv, int i, int l, int r) {
    if (ql <= l && r <= qr) {
        cnt[i] += qv;
        up(i, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        update(ql, qr, qv, i << 1, l, mid);
    }
    if (qr > mid) {
        update(ql, qr, qv, i << 1 | 1, mid + 1, r);
    }
    up(i, l, r);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<node> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i].x1 >> v[i].y1 >> v[i].x2 >> v[i].y2;
        x.emplace_back(v[i].x1);
        x.emplace_back(v[i].x2);
        y.emplace_back(v[i].y1);
        y.emplace_back(v[i].y2);
        qx.emplace_back(v[i].x1, 1, v[i].y1, v[i].y2);
        qx.emplace_back(v[i].x2, -1, v[i].y1, v[i].y2);
        qy.emplace_back(v[i].y1, 1, v[i].x1, v[i].x2);
        qy.emplace_back(v[i].y2, -1, v[i].x1, v[i].x2);
    }
    //横着，竖着各来一次扫描线
    //发现来到一个位置之后，增加的周长等于这一时刻总覆盖长度-上一时刻总覆盖长度的绝对值
    //离散化
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end());
    int nx = x.size(), ny = y.size();
    x.emplace_back(x.back());
    y.emplace_back(y.back());
    sort(qx.begin(), qx.end());
    sort(qy.begin(), qy.end());
    //扫x
    ll sumx = 0, prex = 0;
    len.assign(ny << 2, 0);
    cover.assign(ny << 2, 0);
    cnt.assign(ny << 2, 0);
    build_y(1, 1, ny - 1);
    for (int i = 0; i < 2 * n; i++) {
        //先更改，再结算答案
        auto lo = lower_bound(y.begin(), y.end(), qx[i].y1) - y.begin();
        auto hi = lower_bound(y.begin(), y.end(), qx[i].y2) - y.begin();
        update(lo, hi - 1, qx[i].d, 1, 1, ny - 1);
        sumx += abs(prex - cover[1]);
        prex = cover[1];
    }
    //扫y
    ll sumy = 0, prey = 0;
    len.assign(nx << 2, 0);
    cover.assign(nx << 2, 0);
    cnt.assign(nx << 2, 0);
    build_x(1, 1, nx - 1);
    for (int i = 0; i < 2 * n; i++) {
        //先更改，再结算答案
        auto lo = lower_bound(x.begin(), x.end(), qy[i].x1) - x.begin();
        auto hi = lower_bound(x.begin(), x.end(), qy[i].x2) - x.begin();
        update(lo, hi - 1, qy[i].d, 1, 1, nx - 1);
        sumy += abs(prey - cover[1]);
        prey = cover[1];
    }
    cout << sumx + sumy << '\n';
    return 0;
}