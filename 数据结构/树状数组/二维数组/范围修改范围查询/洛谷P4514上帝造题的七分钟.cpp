#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int n, m;
//维护四个差分信息的树状数组
//sum(n,m)=∑(i=1,n)∑(j=1,m) d[i][j]*(n-i+1)*(m-j+1)=
//(n+1)*(m+1)*∑(i=1,n)∑(j=1,m) d[i][j] -
//(m+1)*∑(i=1,n)∑(j=1,m) (d[i][j]*i) -
//(n+1)*∑(i=1,n)∑(j=1,m) (d[i][j]*j) +
//∑(i=1,n)∑(j=1,m) (d[i][j]*i*j)
//维护d[i][j]
vector<vector<ll>> tree1;
//维护d[i][j]*i
vector<vector<ll>> tree2;
//维护d[i][j]*j
vector<vector<ll>> tree3;
//维护d[i][j]*i*j
vector<vector<ll>> tree4;
int lowbit(int x) {
    return x & -x;
}
//add实际上就是对差分数组的树状数组单点修改
void add(int x, int y, ll k) {
    ll v1 = k;
    ll v2 = k * x;
    ll v3 = k * y;
    ll v4 = k * x * y;
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= m; j += lowbit(j)) {
            tree1[i][j] += v1;
            tree2[i][j] += v2;
            tree3[i][j] += v3;
            tree4[i][j] += v4;
        }
    }
}
//sum(x,y)表示原始数组(1,1)到(x,y)的累加和
ll sum(int x, int y) {
    ll ans = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            ans += 1LL * (x + 1) * (y + 1) * tree1[i][j] - 1LL * (y + 1) * tree2[i][j] - 1LL * (x + 1) * tree3[i][j] + 1LL * tree4[i][j];
        }
    }
    return ans;
}
ll query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    char c0;
    cin >> c0;
    cin >> n >> m;
    tree1.assign(n + 1, vector<ll>(m + 1, 0));
    tree2.assign(n + 1, vector<ll>(m + 1, 0));
    tree3.assign(n + 1, vector<ll>(m + 1, 0));
    tree4.assign(n + 1, vector<ll>(m + 1, 0));
    char op;
    while (cin >> op) {
        if (op == 'L') {
            int a, b, c, d;
            ll k;
            cin >> a >> b >> c >> d >> k;
            add(a, b, k);
            add(a, d + 1, -k);
            add(c + 1, b, -k);
            add(c + 1, d + 1, k);
        }
        else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            cout << query(a, b, c, d) << '\n';
        }
    }
    return 0;
}