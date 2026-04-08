#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr ll MOD = 998244353;
// constexpr ll MOD=1e9+7;
int t, n;
struct node {
    ll a, b, c, id;
};
bool cmp(const node& x, const node& y) {
    return x.b * y.c > x.c * y.b;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t >> n;
    vector<node> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].a;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i].b;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i].c;
        a[i].id = i;
    }
    //dp[i][j]表示来到第i个物品，花费时间不超过j的情况下，取得的最大价值
    //但是因为选择的顺序会对价值造成影响，因此最好先排个序
    //实际上，在经历t时间之后，每个元素都平等地被减掉t*b[i]
    //排出优先级顺序
    //考虑两个相邻物品x,y，假设现在已经花费p时间
    //先做x:a[x]-(c[x]+p)*b[x] + a[y]-(c[x]+c[y]+p)*b[y]  (1)
    //先做y:a[y]-(c[y]+p)*b[y] + a[x]-(c[x]+c[y]+p)*b[x]  (2)
    //(1)>(2) -> b[x]*c[y] > b[y]*c[x]
    sort(a.begin() + 1, a.end(), cmp);
    vector dp(n + 1, vector<ll>(t + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= t; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - a[i].c >= 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i].c] + a[i].a - j * a[i].b);
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= t; i++) {
        ans = max(ans, dp[n][i]);
    }
    cout << ans << '\n';


    return 0;
}