#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
// constexpr ll MOD=1e9+7;3;
// constexpr ll MOD=1e9+7;
int T;
int n, m;
//线段树查询区间累加和
vector<int> seg;
vector<int> reset;
vector<int> upd;
void up(int i) {
    seg[i] = seg[i << 1] + seg[i << 1 | 1];
}
void lazy(int qv, int i, int num) {
    seg[i] = qv * num;
    reset[i] = qv;
    upd[i] = 1;
}
void down(int i, int ln, int rn) {
    if (upd[i]) {
        lazy(reset[i], i << 1, ln);
        lazy(reset[i], i << 1 | 1, rn);
        upd[i] = 0;
    }
}
void update(int ql, int qr, int qv, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        lazy(qv, i, r - l + 1);
        return;
    }
    int mid = (r + l) >> 1;
    down(i, mid - l + 1, r - mid);
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
        return seg[i];
    }
    int mid = (r + l) >> 1;
    down(i, mid - l + 1, r - mid);
    int ans = 0;
    if (ql <= mid) {
        ans += query(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        ans += query(ql, qr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}
//二分查找区间上第k个0的位置
int find0(int start, int k) {
    int ans = 0;
    int l = start, r = n;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (mid - start + 1 - query(start, mid, 1, n, 1) >= k) {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        seg.assign(n << 2, 0);
        reset.assign(n << 2, 0);
        upd.assign(n << 2, 0);
        while (m--) {
            int op;
            cin >> op;
            if (op == 1) {
                int l, f;
                cin >> l >> f;
                ++l;
                //先查询0的个数，判断最多放几个
                int cnt0 = n - l + 1 - query(l, n, 1, n, 1);
                if (cnt0 == 0) {
                    cout << "Can not put any one.\n";
                    continue;
                }
                //最多放几个
                int cnt = min(cnt0, f);
                //查询第1个0和第cnt个0的位置
                int pos1 = find0(l, 1), pos2 = find0(l, cnt);
                cout << pos1 - 1 << ' ' << pos2 - 1 << '\n';
                update(pos1, pos2, 1, 1, n, 1);
            }
            else {
                int l, r;
                cin >> l >> r;
                int cnt = query(l + 1, r + 1, 1, n, 1);
                cout << cnt << '\n';
                update(l + 1, r + 1, 0, 1, n, 1);
            }
        }
        cout << '\n';
    }
    return 0;
}