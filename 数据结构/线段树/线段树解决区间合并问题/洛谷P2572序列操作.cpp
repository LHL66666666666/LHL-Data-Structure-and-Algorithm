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
vector<int> a;
struct node {
    int len, pre, suf;
};
//线段树维护信息:
//连续1的最长子串长度(len1)
//连续1的最长前缀长度(pre1)
//连续1的最长后缀长度(suf1)
//连续0的最长子串长度(len0)
//连续0的最长前缀长度(pre0)
//连续0的最长后缀长度(suf0)
//对于查询3:还需要维护区间累加和
vector<int> sum;
vector<int> len1;
vector<int> pre1;
vector<int> suf1;
vector<int> len0;
vector<int> pre0;
vector<int> suf0;
vector<int> reset;
vector<int> upd;
vector<int> rev;
void up(int l, int r, int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    len1[i] = max({ len1[i << 1],len1[i << 1 | 1],suf1[i << 1] + pre1[i << 1 | 1] });
    len0[i] = max({ len0[i << 1],len0[i << 1 | 1],suf0[i << 1] + pre0[i << 1 | 1] });
    int mid = (l + r) >> 1;
    //处理1的信息
    if (sum[i << 1] == mid - l + 1) {
        //左侧全为1
        pre1[i] = pre1[i << 1] + pre1[i << 1 | 1];
    }
    else {
        //左侧不全为1
        pre1[i] = pre1[i << 1];
    }
    if (sum[i << 1 | 1] == r - mid) {
        //右侧全为1
        suf1[i] = suf1[i << 1 | 1] + suf1[i << 1];
    }
    else {
        //右侧不全为1
        suf1[i] = suf1[i << 1 | 1];
    }
    //处理0的信息
    if (sum[i << 1] == 0) {
        //左侧全为0
        pre0[i] = pre0[i << 1] + pre0[i << 1 | 1];
    }
    else {
        //左侧不全为0
        pre0[i] = pre0[i << 1];
    }
    if (sum[i << 1 | 1] == 0) {
        //右侧全为0
        suf0[i] = suf0[i << 1 | 1] + suf0[i << 1];
    }
    else {
        //右侧不全为0
        suf0[i] = suf0[i << 1 | 1];
    }
}
void lazy(int i, int num, int op) {
    //op==0变为0,op==1变为1,op==2翻转
    if (op == 0) {
        sum[i] = 0;
        reset[i] = 0;
        upd[i] = 1;
        rev[i] = 0;
        //加工连续1,0的信息
        pre1[i] = 0;
        suf1[i] = 0;
        len1[i] = 0;
        pre0[i] = num;
        suf0[i] = num;
        len0[i] = num;
    }
    else if (op == 1) {
        sum[i] = num;
        reset[i] = 1;
        upd[i] = 1;
        rev[i] = 0;
        //加工连续1,0的信息
        pre1[i] = num;
        suf1[i] = num;
        len1[i] = num;
        pre0[i] = 0;
        suf0[i] = 0;
        len0[i] = 0;
    }
    else if (op == 2) {
        sum[i] = num - sum[i];
        rev[i] ^= 1;
        if (rev[i] == 1 && upd[i] != 0) {
            rev[i] = 0;
            reset[i] ^= 1;
        }
        //加工连续1,0的信息
        swap(len1[i], len0[i]);
        swap(pre1[i], pre0[i]);
        swap(suf1[i], suf0[i]);
    }
}
void down(int i, int ln, int rn) {
    if (upd[i] != 0) {
        lazy(i << 1, ln, reset[i]);
        lazy(i << 1 | 1, rn, reset[i]);
        upd[i] = 0;
    }
    if (rev[i] != 0) {
        lazy(i << 1, ln, 2);
        lazy(i << 1 | 1, rn, 2);
        rev[i] = 0;
    }
}
void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = a[l];
        len1[i] = a[l];
        pre1[i] = a[l];
        suf1[i] = a[l];
        len0[i] = !a[l];
        pre0[i] = !a[l];
        suf0[i] = !a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, i << 1 | 1);
    up(l, r, i);
}
void update_reset(int ql, int qr, int qv, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        lazy(i, r - l + 1, qv);
        return;
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    if (ql <= mid) {
        update_reset(ql, qr, qv, l, mid, i << 1);
    }
    if (qr > mid) {
        update_reset(ql, qr, qv, mid + 1, r, i << 1 | 1);
    }
    up(l, r, i);
}
void update_reverse(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        lazy(i, r - l + 1, 2);
        return;
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    if (ql <= mid) {
        update_reverse(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        update_reverse(ql, qr, mid + 1, r, i << 1 | 1);
    }
    up(l, r, i);
}
int query1(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    int ans = 0;
    if (ql <= mid) {
        ans += query1(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        ans += query1(ql, qr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}
node query2(int ql, int qr, int l, int r, int i) {
    if (ql <= l && r <= qr) {
        return { len1[i],pre1[i],suf1[i] };
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    node left = { -1,-1,-1 };
    node right = { -1,-1,-1 };
    node ans = { -1,-1,-1 };
    if (ql <= mid) {
        left = query2(ql, qr, l, mid, i << 1);
    }
    if (qr > mid) {
        right = query2(ql, qr, mid + 1, r, i << 1 | 1);
    }
    if (left.len != -1 && right.len != -1) {
        //注意这里max(ql,l)是为了找到左孩子被查询范围覆盖的区域
        //圈定合法范围
        if (left.len == mid - max(ql, l) + 1) {
            //左侧全为1
            ans.pre = left.pre + right.pre;
        }
        else {
            ans.pre = left.pre;
        }
        if (right.len == min(qr, r) - mid) {
            //右侧全为1
            ans.suf = right.suf + left.suf;
        }
        else ans.suf = right.suf;
        ans.len = max({ left.len,right.len,left.suf + right.pre });
    }
    else if (left.len != -1) {
        ans = left;
    }
    else if (right.len != -1) {
        ans = right;
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
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sum.assign(n << 2, 0);
    len1.assign(n << 2, 0);
    pre1.assign(n << 2, 0);
    suf1.assign(n << 2, 0);
    len0.assign(n << 2, 0);
    pre0.assign(n << 2, 0);
    suf0.assign(n << 2, 0);
    reset.assign(n << 2, 0);
    upd.assign(n << 2, 0);
    rev.assign(n << 2, 0);
    build(1, n, 1);
    while (m--) {
        int op;
        int l, r;
        cin >> op;
        cin >> l >> r;
        //l,r是0-based
        if (op == 0) {
            update_reset(l + 1, r + 1, 0, 1, n, 1);
        }
        else if (op == 1) {
            update_reset(l + 1, r + 1, 1, 1, n, 1);
        }
        else if (op == 2) {
            //特别注意：两次反转会抵消
            //另外：重置操作的优先级大于反转的
            update_reverse(l + 1, r + 1, 1, n, 1);
        }
        else if (op == 3) {
            int ans = query1(l + 1, r + 1, 1, n, 1);
            cout << ans << '\n';
        }
        else if (op == 4) {
            //查询时，只关注被查询范围影响到的信息
            //query2表示被查询范围影响到的{连续1的最长子串长度，连续1的最长前缀长度，连续1的最长后缀长度}
            auto ans = query2(l + 1, r + 1, 1, n, 1);
            cout << ans.len << '\n';
        }
    }
    return 0;
}