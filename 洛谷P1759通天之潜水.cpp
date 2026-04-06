#include <iostream>
#include <vector>
#include <string>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int T;
ll m, n, v;
struct node {
    ll a, b, c;
};
vector<vector<ll>> dp;
vector<vector<string>> path;
vector<int> ans;
ll tot;
int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> v >> n;
    vector<node> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].a >> a[i].b >> a[i].c;
    }
    dp.assign(m + 1, vector<ll>(v + 1, 0));
    path.assign(m + 1, vector<string>(v + 1, ""));
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = v; k >= 0; k--) {
                dp[j][k] = dp[j][k];
                path[j][k] = path[j][k];
                if (j - a[i].a >= 0 && k - a[i].b >= 0) {
                    if (dp[j - a[i].a][k - a[i].b] + a[i].c > dp[j][k]) {
                        dp[j][k] = dp[j - a[i].a][k - a[i].b] + a[i].c;
                        path[j][k] = path[j - a[i].a][k - a[i].b] + ' ' + to_string(i);
                    }
                    else if (dp[j - a[i].a][k - a[i].b] + a[i].c == dp[j][k]) {
                        path[j][k] = min(path[j][k], path[j - a[i].a][k - a[i].b] + ' ' + to_string(i));
                    }
                }
            }
        }
    }
    tot = dp[m][v];
    cout << tot << '\n';
    //这里字典序是将整个方案看作一个大的字符串来比较的
    string s = path[m][v];
    int n1 = s.size();
    for (int i = 1; i < n1; i++) cout << s[i];
    cout << '\n';
    return 0;
}