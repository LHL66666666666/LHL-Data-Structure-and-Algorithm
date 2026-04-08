#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr ll MOD = 998244353;
// constexpr ll MOD=1e9+7;
int n, m;
//单点修改，无需懒标记
vector<int> sum;
vector<int> a;
void up(int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}
void update(int ql, int qr, int qv, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        sum[i] = qv;
        return;
    }
    int mid = (l + r) >> 1;
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
        return sum[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (ql <= mid) {
        ans += query(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        ans += query(ql, qr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}
int right(int p) {
    if (query(p, n, 1, n, 1) == 0) {
        return n + 1;
    }
    int tar = query(1, p, 1, n, 1) + 1;
    int l = p, r = n;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (query(1, mid, 1, n, 1) >= tar) {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return ans;
}
int left(int p) {
    if (query(1, p, 1, n, 1) == 0) {
        return 0;
    }
    int tar = query(1, p, 1, n, 1);
    int l = 1, r = p;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (query(1, mid, 1, n, 1) >= tar) {
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
    cin >> n >> m;
    a.assign(n + 1, 0);
    sum.assign(n << 2, 0);
    vector<int> lst;
    while (m--) {
        char op;
        cin >> op;
        if (op == 'D') {
            int x;
            cin >> x;
            lst.emplace_back(x);
            update(x, x, 1, 1, n, 1);
            a[x] = 1;
        }
        else if (op == 'R') {
            if (!lst.empty()) {
                auto x = lst.back();
                lst.pop_back();
                update(x, x, 0, 1, n, 1);
                a[x] = 0;
            }
        }
        else if (op == 'Q') {
            int x;
            cin >> x;
            if (a[x] == 1) {
                cout << 0 << '\n';
            }
            else {
                int l = left(x), r = right(x);
                cout << r - l - 1 << '\n';
            }
        }
    }




    return 0;
}