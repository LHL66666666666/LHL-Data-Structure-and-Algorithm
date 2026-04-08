#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
// constexpr ll MOD=1e9+7;
int n, m;
vector<int> st;
vector<int> ed;
void update1(int ql, int qr, int qv, int l, int r, int i) {
    if (l == r) {
        st[i]++;
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        update1(ql, qr, qv, l, mid, i << 1);
    }
    if (qr > mid) {
        update1(ql, qr, qv, mid + 1, r, i << 1 | 1);
    }
    st[i] = st[i << 1] + st[i << 1 | 1];
}
void update2(int ql, int qr, int qv, int l, int r, int i) {
    if (l == r) {
        ed[i]++;
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        update2(ql, qr, qv, l, mid, i << 1);
    }
    if (qr > mid) {
        update2(ql, qr, qv, mid + 1, r, i << 1 | 1);
    }
    ed[i] = ed[i << 1] + ed[i << 1 | 1];
}
int query1(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return st[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (ql <= mid) {
        ans += query1(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        ans += query1(ql, qr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}
int query2(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return ed[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (ql <= mid) {
        ans += query2(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        ans += query2(ql, qr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    st.assign(n << 2, 0);
    ed.assign(n << 2, 0);
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            update1(l, l, 1, 1, n, 1);
            update2(r, r, 1, 1, n, 1);
        }
        else if (op == 2) {
            int res1 = query1(1, r, 1, n, 1);
            int res2 = query2(1, l - 1, 1, n, 1);
            cout << res1 - res2 << '\n';
        }
    }







    return 0;
}