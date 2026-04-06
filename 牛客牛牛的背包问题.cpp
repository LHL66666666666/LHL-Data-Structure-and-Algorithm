/*
牛牛准备参加学校组织的春游, 出发前牛牛准备往背包里装入一些零食, 牛牛的背包容量为w。
牛牛家里一共有n袋零食, 第i袋零食体积为v[i]。
牛牛想知道在总体积不超过背包容量的情况下,他一共有多少种零食放法(总体积为0也算一种放法)。
输入描述：
输入包括两行
第一行为两个正整数n和w(1 <= n <= 30, 1 <= w <= 2 * 10^9),表示零食的数量和背包的容量。
第二行n个正整数v[i](0 <= v[i] <= 10^9),表示每袋零食的体积。
输出描述：
输出一个正整数, 表示牛牛一共有多少种零食放法。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
ll v[35];
vector<ll> l;
vector<ll> r;
ll n, w;
void dfs(int idx, int end, ll sum, int f) {
    if (sum > w)
    {
        //小剪枝
        return;
    }
    if (idx > end) {
        if (f == 0) l.emplace_back(sum);
        else r.emplace_back(sum);
        return;
    }
    dfs(idx + 1, end, sum + v[idx], f);
    dfs(idx + 1, end, sum, f);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    //将数组分为两半，分别dfs展开，最后合并
    if (n == 1) {
        if (v[1] <= w) cout << 2 << '\n';
        else cout << 1 << '\n';
        return 0;
    }
    int m = n / 2;
    dfs(1, m, 0, 0);
    dfs(m + 1, n, 0, 1);
    //合并
    int n1 = l.size();
    int n2 = r.size();
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    int p1 = 0, p2 = n2 - 1;
    ll ans = 0;
    for (; p1 < n1; p1++) {
        while (p2 >= 0 && l[p1] + r[p2] > w) {
            --p2;
        }
        ans += p2 + 1;
    }
    cout << ans << '\n';
    return 0;
}