#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
ll n, m;
//区间修改，区间查询
//当我们要计算原始数组范围累加和时
//a[1]  +a[2]       +...+a[k] =
//(d[1])+(d[1]+d[2])+...+(d[1]+d[2]+...d[k]) =
//k*∑d[i]-∑d[i]*(i-1)   其中i均为[1,k]
//需要两个树状数组维护
//tree1维护差分数组d[i]
vector<ll> tree1;
//tree2维护(i-1)*d[i]
vector<ll> tree2;
int lowbit(int x) {
    return x & -x;
}
void add(int i, ll x) {
    while (i <= n) {
        tree1[i] += x;
        i += lowbit(i);
    }
}
void add2(int i, ll x) {
    while (i <= n) {
        tree2[i] += x;
        i += lowbit(i);
    }
}
ll sum(vector<ll>& tree, int i) {
    ll ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}
ll query(int l, int r) {
    ll x = 1LL * r * sum(tree1, r) - 1LL * sum(tree2, r);
    ll y = 1LL * (l - 1) * sum(tree1, l - 1) - 1LL * sum(tree2, l - 1);
    return x - y;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    //范围修改，单点查询，利用差分数组构建树状数组即可
    tree1.assign(n + 1, 0);
    tree2.assign(n + 1, 0);
    ll pre = 0;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        add(i, x - pre);
        add2(i, (x - pre) * (i - 1));
        pre = x;
    }
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            ll k;
            cin >> x >> y >> k;
            add(x, k);
            add(y + 1, -k);
            add2(x, k * (x - 1));
            add2(y + 1, -k * y);
        }
        else {
            int x, y;
            cin >> x >> y;
            cout << query(x, y) << '\n';
        }
    }
    return 0;
}