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
class CountIntervals {
public:
    const int N = 2e6 + 5;
    int cnt;
    vector<int> sum;
    vector<int> upd;
    vector<int> ls;
    vector<int> rs;
    void up(int i) {
        sum[i] = sum[ls[i]] + sum[rs[i]];
    }
    void lazy(int i, int num) {
        sum[i] = num;
        upd[i] = 1;
    }
    void down(int i, int l, int r) {
        if (upd[i] != 0) {
            int mid = (l + r) >> 1;
            if (ls[i] == 0) {
                ls[i] = ++cnt;
            }
            if (rs[i] == 0) {
                rs[i] = ++cnt;
            }
            lazy(rs[i], r - mid);
            lazy(ls[i], mid - l + 1);
            upd[i] = 0;
        }
    }
    void update(int ql, int qr, int i, int l, int r) {
        if (ql <= l && r <= qr) {
            lazy(i, r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        down(i, l, r);
        if (ql <= mid) {
            if (ls[i] == 0) {
                ls[i] = ++cnt;
            }
            update(ql, qr, ls[i], l, mid);
        }
        if (qr > mid) {
            if (rs[i] == 0) {
                rs[i] = ++cnt;
            }
            update(ql, qr, rs[i], mid + 1, r);
        }
        up(i);
    }
    int query(int ql, int qr, int i, int l, int r) {
        if (ql <= l && r <= qr) {
            return sum[i];
        }
        int mid = (l + r) >> 1;
        down(i, l, r);
        int ans = 0;
        if (ql <= mid) {
            if (ls[i] != 0) {
                ans += query(ql, qr, ls[i], l, mid);
            }
        }
        if (qr > mid) {
            if (rs[i] != 0) {
                ans += query(ql, qr, rs[i], mid + 1, r);
            }
        }
        return ans;
    }
    CountIntervals() {
        cnt = 1;
        sum.assign(N, 0);
        upd.assign(N, 0);
        ls.assign(N, 0);
        rs.assign(N, 0);
    }
    void add(int l, int r) {
        update(l, r, 1, 1, 1e9);
    }
    int count() {
        return sum[1];
    }
};