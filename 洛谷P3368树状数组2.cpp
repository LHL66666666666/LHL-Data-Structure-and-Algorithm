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
vector<int> tree;
int lowbit(int x) {
    return x & -x;
}
void add(int i, int x) {
    while (i <= n) {
        tree[i] += x;
        i += lowbit(i);
    }
}
int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}
int query(int l, int r) {
    return sum(r) - sum(l - 1);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    //范围修改，单点查询，利用差分数组构建树状数组即可
    tree.assign(n + 1, 0);
    int pre = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        add(i, x - pre);
        pre = x;
    }
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            add(x, k);
            add(y + 1, -k);
        }
        else {
            int x;
            cin >> x;
            cout << query(1, x) << '\n';
        }
    }
    return 0;
}