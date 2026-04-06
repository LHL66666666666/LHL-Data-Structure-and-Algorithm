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
vector<vector<ll>> tree;
int lowbit(int x) {
    return x & -x;
}
void add(int x, int y, ll k) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= m; j += lowbit(j)) {
            tree[i][j] += k;
        }
    }
}
ll sum(int x, int y) {
    ll ans = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            ans += tree[i][j];
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
    cin >> n >> m;
    tree.assign(n + 1, vector<ll>(m + 1, 0));
    int op;
    while (cin >> op) {
        if (op == 1) {
            int x, y;
            ll k;
            cin >> x >> y >> k;
            add(x, y, k);
        }
        else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            cout << query(a, b, c, d) << '\n';
        }
    }
    return 0;
}