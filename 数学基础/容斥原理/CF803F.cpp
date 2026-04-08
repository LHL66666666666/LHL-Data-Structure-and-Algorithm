#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
// constexpr ll MOD=998244353;
constexpr ll MOD = 1e9 + 7;
int n;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<int> a(n + 1);
    vector<int> cnt(100005);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    int n1 = *max_element(a.begin(), a.end());
    //由于a[i]的范围最大到1e5
    //整个序列的非空子序列个数为2^n-1
    //考虑容斥，gcd为1的子序列个数=2^n-1-gcd大于1的子序列个数
    //dp[i]表示以i作为最大公约数的子序列的个数
    //来到每一个数字，我们只需要遍历它的倍数，
    //倒序枚举因子i，记录下来序列中i的倍数总数sum,得到的2^sum-1是以i,2i,3i...xi作为gcd的子序列的个数
    //因为对于i的倍数而言，它们构成的序列也有可能是以i的倍数作为gcd的，
    //所以这里也算一个小容斥，需要枚举i的倍数j，然后从dp[i]中减去dp[j]这样才能得到不会重复的结果
    vector<ll> dp(n1 + 1);
    //从大往小推
    for (int i = n1; i >= 1; i--) {
        ll cnt1 = 0;
        ll sum = 0;
        for (int j = i; j <= n1; j += i) {
            cnt1 = (cnt1 + cnt[j]) % MOD;
            if (j > i) sum = (sum + dp[j]) % MOD;
        }
        dp[i] = ((qpow(2, cnt1) - 1 - sum) % MOD + MOD) % MOD;
    }
    cout << dp[1] << '\n';
    return 0;
}