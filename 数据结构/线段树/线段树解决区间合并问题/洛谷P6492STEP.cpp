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
int n, q;
//需要维护的信息是：
//区间上最大交替前缀，最大交替后缀，最大交替子串
vector<int> a;
vector<int> pre;
vector<int> suf;
vector<int> len;
struct node {
    int pre, suf, len;
};
void up(int i, int l, int r) {
    int mid = (l + r) >> 1;
    if (pre[i << 1] == mid - l + 1 && a[mid] ^ a[mid + 1]) {
        //左侧全是交替，且左右能连起来
        pre[i] = pre[i << 1] + pre[i << 1 | 1];
    }
    else pre[i] = pre[i << 1];
    if (suf[i << 1 | 1] == r - mid && a[mid] ^ a[mid + 1]) {
        //有侧全是交替，且左右能连起来
        suf[i] = suf[i << 1] + suf[i << 1 | 1];
    }
    else suf[i] = suf[i << 1 | 1];
    if (a[mid] ^ a[mid + 1]) {
        len[i] = max({ len[i << 1],len[i << 1 | 1],suf[i << 1] + pre[i << 1 | 1] });
    }
    else len[i] = max(len[i << 1], len[i << 1 | 1]);
}
void update(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        pre[i] = 1, suf[i] = 1, len[i] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        update(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        update(ql, qr, mid + 1, r, i << 1 | 1);
    }
    up(i, l, r);
}
node query(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return { pre[i],suf[i],len[i] };
    }
    int mid = (l + r) >> 1;
    auto left = query(ql, qr, l, mid, i << 1);
    auto right = query(ql, qr, mid + 1, r, i << 1 | 1);
    node ans = { 0,0,0 };
    if (left.pre == mid - l + 1 && a[mid] ^ a[mid + 1]) {
        ans.pre = left.pre + right.pre;
    }
    else ans.pre = left.pre;
    if (right.suf == r - mid && a[mid] ^ a[mid + 1]) {
        ans.suf = left.suf + right.suf;
    }
    else ans.suf = right.suf;
    if (a[mid] ^ a[mid + 1]) {
        ans.len = max({ left.len,right.len,left.suf + right.pre });
    }
    else ans.len = max(left.len, right.len);
    return ans;
}
void build(int l, int r, int i) {
    if (l == r) {
        pre[i] = suf[i] = len[i] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, i << 1 | 1);
    up(i, l, r);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    a.assign(n + 1, 0);
    pre.assign(n << 2, 0);
    suf.assign(n << 2, 0);
    len.assign(n << 2, 0);
    build(1, n, 1);
    while (q--) {
        int x;
        cin >> x;
        a[x] ^= 1;
        update(x, x, 1, n, 1);
        auto ans = query(1, n, 1, n, 1);
        cout << ans.len << '\n';
    }
    return 0;
}