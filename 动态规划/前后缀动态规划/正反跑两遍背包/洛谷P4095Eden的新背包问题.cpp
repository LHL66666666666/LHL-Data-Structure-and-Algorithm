#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
const int MOD = 998244353;
int T, n, q;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    //正反跑两遍多重背包
    vector<int> cnt(n + 1);
    vector<int> x(1);
    vector<int> cost(1);
    vector<int> val(1);
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        int cnt1 = 0;
        for (int k = 1; k <= c; k <<= 1) {
            c -= k;
            x.emplace_back(k);
            cost.emplace_back(k * a);
            val.emplace_back(k * b);
            ++cnt1;
        }
        if (c > 0) {
            x.emplace_back(c);
            cost.emplace_back(c * a);
            val.emplace_back(c * b);
            ++cnt1;
        }
        cnt[i] = cnt1;
    }
    for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
    // for (auto i:cnt) cout<<i<<" ";
    // cout<<'\n';
    //正向
    int n1 = x.size() - 1;
    // cout<<n1<<'\n';
    vector<vector<ll>> dp(n1 + 2, vector<ll>(1001, 0));
    for (int i = 1; i <= n1; i++) {
        for (int j = 0; j <= 1000; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - cost[i] >= 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - cost[i]] + val[i]);
            }
        }
    }
    //逆向
    vector<vector<ll>> dp2(n1 + 2, vector<ll>(1001, 0));
    for (int i = n1; i >= 1; i--) {
        for (int j = 0; j <= 1000; j++) {
            dp2[i][j] = dp2[i + 1][j];
            if (j - cost[i] >= 0) {
                dp2[i][j] = max(dp2[i][j], dp2[i + 1][j - cost[i]] + val[i]);
            }
        }
    }
    cin >> q;
    while (q--) {
        int d, e;
        cin >> d >> e;
        //下标对齐
        d++;
        int l = cnt[d - 1], r = cnt[d] + 1;
        // cout<<l<<' '<<r<<'\n';
        ll ans = 0;
        for (int j = 0; j <= e; j++) {
            ans = max(ans, dp[l][j] + dp2[r][e - j]);
        }
        cout << ans << '\n';
    }
    return 0;
}