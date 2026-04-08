#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
const int N = 1e5 + 5;
int n;
vector<int> a;
vector<ll> tree1;
vector<ll> tree2;
int lowbit(int x) {
    return x & -x;
}
void add(vector<ll>& tree, int pos, ll k) {
    while (pos <= N) {
        tree[pos] += k;
        pos += lowbit(pos);
    }
}
ll sum(vector<ll>& tree, int pos) {
    ll ans = 0;
    while (pos > 0) {
        ans += tree[pos];
        pos -= lowbit(pos);
    }
    return ans;
}
ll query(vector<ll>& tree, int l, int r) {
    return sum(tree, r) - sum(tree, l - 1);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n + 1);
    tree1.assign(N + 1, 0);
    tree2.assign(N + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    ll ans = 0;
    // //这种写法是定义up1[i]表示以i为起点的上升1元组的数量,tree1是up1的树状数组
    // //up2[i]表示以i为起点的上升2元组的数量,tree2是up2的树状数组
    // for (int i=n;i>=1;i--) {
    //     ans+=query(tree2,a[i]+1,N);
    //     ll tmp=query(tree1,a[i]+1,N);
    //     add(tree1,a[i],1);
    //     add(tree2,a[i],tmp);
    // }
    //------------------------------------------------
    // 这种写法是定义up1[i]表示以i为结束位置的上升1元组的数量,tree1是up1的树状数组
    // up2[i]表示以i为结束位置的上升2元组的数量,tree2是up2的树状数组
    for (int i = 1; i <= n; i++) {
        ans += sum(tree2, a[i] - 1);
        ll tmp = sum(tree1, a[i] - 1);
        add(tree1, a[i], 1);
        add(tree2, a[i], tmp);
    }
    cout << ans << '\n';
    return 0;
}