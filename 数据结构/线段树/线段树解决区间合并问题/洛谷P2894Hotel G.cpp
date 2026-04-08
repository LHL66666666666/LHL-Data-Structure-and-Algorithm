//#include <vector>
//#include <map>
//#include <algorithm>
//#include <queue>
//#include <iostream>
//using namespace std;
//using ll = long long;
//constexpr int INF = 0x3f3f3f3f;
//constexpr ll MOD = 998244353;
//// constexpr ll MOD=1e9+7;
//int n, m;
//struct node {
//    int pre, suf, len, pos;
//};
//vector<int> pre;
//vector<int> suf;
//vector<int> len;
//vector<int> reset;
//vector<int> upd;
////加一条信息：区间上最长连续1的开头位置
//vector<int> pos;
//void up(int i, int l, int r) {
//    int mid = (l + r) >> 1;
//    if (pre[i << 1] == mid - l + 1) {
//        pre[i] = pre[i << 1] + pre[i << 1 | 1];
//    }
//    else pre[i] = pre[i << 1];
//    if (suf[i << 1 | 1] == r - mid) {
//        suf[i] = suf[i << 1] + suf[i << 1 | 1];
//    }
//    else suf[i] = suf[i << 1 | 1];
//    int mx = max({ len[i << 1],len[i << 1 | 1],suf[i << 1] + pre[i << 1 | 1] });
//    len[i] = mx;
//    if (mx == len[i << 1]) {
//        pos[i] = pos[i << 1];
//    }
//    else if (mx == suf[i << 1] + pre[i << 1 | 1]) {
//        pos[i] = mid - suf[i << 1] + 1;
//    }
//    else if (mx == len[i << 1 | 1]) {
//        pos[i] = pos[i << 1 | 1];
//    }
//}
//void lazy(int i, int qv, int l, int r) {
//    int num = r - l + 1;
//    if (qv == 1) {
//        pre[i] = suf[i] = len[i] = num;
//        pos[i] = l;
//        reset[i] = 1;
//        upd[i] = 1;
//    }
//    else if (qv == 0) {
//        pre[i] = suf[i] = len[i] = 0;
//        pos[i] = 0;
//        reset[i] = 0;
//        upd[i] = 1;
//    }
//}
//void down(int i, int l, int r) {
//    int mid = (l + r) >> 1;
//    if (upd[i]) {
//        lazy(i << 1, reset[i], l, mid);
//        lazy(i << 1 | 1, reset[i], mid + 1, r);
//        upd[i] = 0;
//    }
//}
//void update(int ql, int qr, int qv, int l, int r, int i) {
//    if (ql <= l && r <= qr) {
//        lazy(i, qv, l, r);
//        return;
//    }
//    int mid = (l + r) >> 1;
//    down(i, l, r);
//    if (ql <= mid) {
//        update(ql, qr, qv, l, mid, i << 1);
//    }
//    if (qr > mid) {
//        update(ql, qr, qv, mid + 1, r, i << 1 | 1);
//    }
//    up(i, l, r);
//}
//node query(int ql, int qr, int l, int r, int i) {
//    if (ql <= l && r <= qr) {
//        return { pre[i],suf[i],len[i],pos[i] };
//    }
//    int mid = (l + r) >> 1;
//    down(i, l, r);
//    if (ql > mid) {
//        return query(ql, qr, mid + 1, r, i << 1 | 1);
//    }
//    if (qr <= mid) {
//        return query(ql, qr, l, mid, i << 1);
//    }
//    auto left = query(ql, qr, l, mid, i << 1);
//    auto right = query(ql, qr, mid + 1, r, i << 1 | 1);
//    node ans{};
//    if (left.len == mid - max(ql, l) + 1) {
//        ans.pre = left.pre + right.pre;
//    }
//    else ans.pre = left.pre;
//    if (right.len == min(qr, r) - mid) {
//        ans.suf = left.suf + right.suf;
//    }
//    else ans.suf = right.suf;
//    int mx = max({ left.len,right.len,left.suf + right.pre });
//    ans.len = mx;
//    if (mx == left.len) {
//        ans.pos = left.pos;
//    }
//    else if (mx == left.suf + right.pre) {
//        ans.pos = mid - left.suf + 1;
//    }
//    else if (mx == right.len) {
//        ans.pos = right.pos;
//    }
//    return ans;
//}
//void build(int l, int r, int i) {
//    if (l == r) {
//        pre[i] = suf[i] = len[i] = 1;
//        pos[i] = l;
//        return;
//    }
//    int mid = (l + r) >> 1;
//    build(l, mid, i << 1);
//    build(mid + 1, r, i << 1 | 1);
//    up(i, l, r);
//}
//int main() {
//    // ifstream cin("input.txt");
//    // ofstream cout("output.txt");
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cin >> n >> m;
//    pre.assign(n << 2, 0);
//    suf.assign(n << 2, 0);
//    len.assign(n << 2, 0);
//    pos.assign(n << 2, 0);
//    reset.assign(n << 2, 0);
//    upd.assign(n << 2, 0);
//    build(1, n, 1);
//    while (m--) {
//        int op;
//        cin >> op;
//        if (op == 1) {
//            int x;
//            cin >> x;
//            if (len[1] < x) {
//                cout << 0 << '\n';
//            }
//            else {
//                //这里需要找到第一个大于等于x的段，而非最长段
//                //考虑二分找到位置
//                int l = 1, r = n;
//                int ans = -1;
//                while (l <= r) {
//                    int mid = (l + r) >> 1;
//                    if (query(1, mid, 1, n, 1).len >= x) {
//                        ans = mid;
//                        r = mid - 1;
//                    }
//                    else l = mid + 1;
//                }
//                int p = query(1, ans, 1, n, 1).pos;
//                cout << p << '\n';
//                update(p, p + x - 1, 0, 1, n, 1);
//            }
//        }
//        else {
//            int x, y;
//            cin >> x >> y;
//            update(x, x + y - 1, 1, 1, n, 1);
//        }
//    }
//    return 0;
//}



//写法2：更优秀的查询策略
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
vector<int> pre;
vector<int> suf;
vector<int> len;
vector<int> reset;
vector<int> upd;
void up(int i, int l, int r) {
    int mid = (l + r) >> 1;
    if (pre[i << 1] == mid - l + 1) {
        pre[i] = pre[i << 1] + pre[i << 1 | 1];
    }
    else pre[i] = pre[i << 1];
    if (suf[i << 1 | 1] == r - mid) {
        suf[i] = suf[i << 1] + suf[i << 1 | 1];
    }
    else suf[i] = suf[i << 1 | 1];
    int mx = max({ len[i << 1],len[i << 1 | 1],suf[i << 1] + pre[i << 1 | 1] });
    len[i] = mx;
}
void lazy(int i, int qv, int l, int r) {
    int num = r - l + 1;
    if (qv == 1) {
        pre[i] = suf[i] = len[i] = num;
        reset[i] = 1;
        upd[i] = 1;
    }
    else if (qv == 0) {
        pre[i] = suf[i] = len[i] = 0;
        reset[i] = 0;
        upd[i] = 1;
    }
}
void down(int i, int l, int r) {
    int mid = (l + r) >> 1;
    if (upd[i]) {
        lazy(i << 1, reset[i], l, mid);
        lazy(i << 1 | 1, reset[i], mid + 1, r);
        upd[i] = 0;
    }
}
void update(int ql, int qr, int qv, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        lazy(i, qv, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    down(i, l, r);
    if (ql <= mid) {
        update(ql, qr, qv, l, mid, i << 1);
    }
    if (qr > mid) {
        update(ql, qr, qv, mid + 1, r, i << 1 | 1);
    }
    up(i, l, r);
}
//递归遵循的潜台词：[l,r]范围上一定存在len>=x的连续段
int query(int x, int l, int r, int i) {
    if (l == r) {
        //base case长度为1
        return l;
    }
    int mid = (l + r) >> 1;
    down(i, l, r);
    if (len[i << 1] >= x) {
        return query(x, l, mid, i << 1);
    }
    if (suf[i << 1] + pre[i << 1 | 1] >= x) {
        return mid - suf[i << 1] + 1;
    }
    if (len[i << 1 | 1] >= x) {
        return query(x, mid + 1, r, i << 1 | 1);
    }
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
    cin >> n >> m;
    pre.assign(n << 2, 0);
    suf.assign(n << 2, 0);
    len.assign(n << 2, 0);
    reset.assign(n << 2, 0);
    upd.assign(n << 2, 0);
    build(1, n, 1);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            if (len[1] < x) {
                cout << 0 << '\n';
            }
            else {
                int p = query(x, 1, n, 1);
                cout << p << '\n';
                update(p, p + x - 1, 0, 1, n, 1);
            }
        }
        else {
            int x, y;
            cin >> x >> y;
            update(x, x + y - 1, 1, 1, n, 1);
        }
    }
    return 0;
}