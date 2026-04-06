#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
// constexpr ll MOD=1e9+7;
int T;
int n;
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    //考虑两种策略：
    //考虑当前代价最大的两个人a[i],a[i-1]如何过河花费最小
    //1.代价最小的1号往返，每次带一个代价较大的人
    //2.让a[i],a[i-1]一起过河，只花费一次较大的代价，
    //但是这样做的前提是先将a[1],a[2]送到河对岸，然后a[1]或a[2]把船运回来
    //接着a[i],a[i-1]过河，最后接回来
    //对于n从1到3，策略是固定的
    //n>=3的时候，考虑递推
    //dp[i]表示前i个人过河的最小代价
    vector<ll> dp(n + 1, INF);
    dp[1] = a[1];
    dp[2] = a[2];
    dp[3] = a[2] + a[1] + a[3];
    for (int i = 4; i <= n; i++) {
        //两种策略决策
        dp[i] = min(dp[i], dp[i - 1] + a[1] + a[i]);
        dp[i] = min(dp[i], dp[i - 2] + a[1] + a[i] + a[2] + a[2]);
    }
    cout << dp[n] << '\n';

    return 0;
}