#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int n;
vector<int> a;
vector<ll> tree;
int lowbit(int x) {
    return x & -x;
}
void add(int pos, int k) {
    while (pos <= n) {
        tree[pos] += k;
        pos += lowbit(pos);
    }
}
ll sum(int pos) {
    ll ans = 0;
    while (pos > 0) {
        ans += tree[pos];
        pos -= lowbit(pos);
    }
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    //先进行离散化，因为要建立值域树状数组，离散化之后值域小于等于n
    map<int, int> mp;
    auto tmp = a;
    sort(tmp.begin() + 1, tmp.end());
    tmp.erase(unique(tmp.begin() + 1, tmp.end()), tmp.end());
    int id = 1;
    for (int i = 1; i < tmp.size(); i++) {
        mp[tmp[i]] = id++;
    }
    for (int i = 1; i <= n; i++) {
        a[i] = mp[a[i]];
    }
    tree.assign(n + 1, 0);
    ll ans = 0;
    for (int i = n; i >= 1; i--) {
        //i位置右侧有多少数字比a[i]更小(就是小于a[i]的数字的词频的前缀和)
        ans += sum(a[i] - 1);
        //增加a[i]的词频
        add(a[i], 1);
    }
    cout << ans << '\n';
    return 0;
}