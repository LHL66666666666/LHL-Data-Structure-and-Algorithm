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
int n;
ll p, k;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p >> k;
    vector<int> a(n + 1);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    //先预处理出前缀积数组pre以及前缀数组的逆元，
    //然后每次计算a[i]的逆元即1/a[i]
    //有:pre[i]/pre[i-1]=a[i]
    //1/a[i]=pre[i-1]/pre[i]
    //除以pre[i-1]就相当于乘inv[pre[i-1]]
    //计算pre数组的逆元可以线性递推，先求出invpre[n]
    //依次向前乘a[i]即可递推
    vector<ll> pre(n + 1);
    vector<ll> invpre(n + 1);
    pre[0] = 1, invpre[0] = 1;
    for (int i = 1; i <= n; i++) {
        pre[i] = 1LL * pre[i - 1] * a[i] % p;
    }
    invpre[n] = qpow(pre[n], p - 2);
    for (int i = n - 1; i >= 1; i--) {
        invpre[i] = invpre[i + 1] * a[i + 1] % p;
    }
    ll pk = 1;
    for (int i = 1; i <= n; i++) {
        pk = pk * k % p;
        ll inva = pre[i - 1] * invpre[i] % p;
        ans = (ans + pk * inva % p) % p;
    }
    cout << ans << '\n';

    return 0;
}