//逆元相当于模意义下的倒数
//也就是说，我们求出100!的逆元，在计算的时候相当于乘上1/100!
//因此阶乘逆元的线性递推:要求1/99!，我们只需要1/100! * 100即可
#include <vector>
using ll = long long;
constexpr ll MOD = 998244353;
const int N = 2e5 + 5;
std::vector<ll> fac(N), inv(N);
ll qpow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}
void init() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
    inv[N - 1] = qpow(fac[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
}
ll comb(int n, int m) {
    if (m<0 || m>n) return 0;
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}