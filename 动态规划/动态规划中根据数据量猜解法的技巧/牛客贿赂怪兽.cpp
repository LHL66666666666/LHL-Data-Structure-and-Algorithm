//链接：https://www.nowcoder.com/practice/736e12861f9746ab8ae064d4aae2d5a9
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int T;
int n;
int m;
vector<int> a;
vector<int> b;
vector<vector<int>> dp;
//当a[i]之和较小的时候，使用能力值做状态
int dfs(int i, int x) {
    if (i == n) {
        if (x >= a[i]) return 0;
        return b[i];
    }
    if (dp[i][x] != -1) return dp[i][x];
    int ans = dfs(i + 1, x + a[i]) + b[i];
    if (x >= a[i]) ans = min(ans, dfs(i + 1, x));
    dp[i][x] = ans;
    return ans;
}
int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n + 1);
    b.resize(n + 1);
    ll suma = 0, sumb = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        suma += a[i], sumb += b[i];
    }
    if (suma <= sumb) {
        m = suma;
        dp.assign(n + 1, vector<int>(m + 1, -1));
        cout << dfs(1, 0) << '\n';
    }
    else {
        //当b[i]之和较小的时候，使用钱数做状态
        //dp[i][j]表示来到i号怪兽，花费钱数不超过j，取得的最大能力值
        //如果无法通过，设置为-INF
        m = sumb;
        dp.assign(n + 1, vector<int>(m + 1, -INF));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                //两种选择，花钱/不花钱
                if (dp[i - 1][j] >= a[i]) {
                    dp[i][j] = dp[i - 1][j];
                }
                if (j - b[i] >= 0 && dp[i - 1][j - b[i]] != -INF) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - b[i]] + a[i]);
                }
            }
        }
        for (int i = 0; i <= m; i++) {
            if (dp[n][i] != -INF) {
                cout << i << '\n';
                break;
            }
        }
    }
    return 0;
}