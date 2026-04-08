//和牛客牛牛的背包问题一模一样
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
ll v[40];
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
        //特判一下，以免出现无限DFS
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