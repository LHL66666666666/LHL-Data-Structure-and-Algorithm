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
//普通的dp做法
class Solution {
public:
    int tot;
    int n1;
    int k1;
    vector<vector<ll>> dp1;
    //来到i，一共用了j种
    ll dfs1(int i, int j) {
        if (i > tot) {
            return j == n1;
        }
        if (dp1[i][j] != -1) return dp1[i][j];
        ll ans = 0;
        //选之前用过的，但是有k个不能选
        if (j - k1 >= 0) ans = ((j - k1) % MOD * dfs1(i + 1, j)) % MOD;
        //选之前没用过的
        if (n1 - j >= 0) ans = (ans + 1LL * (n1 - j) % MOD * dfs1(i + 1, j + 1) % MOD) % MOD;
        return dp1[i][j] = ans;
    }
    int numMusicPlaylists(int n, int goal, int k) {
        //相同元素出现必须间隔至少k个其他元素
        //因此，每k+1个连续的必须都是不同的
        dp1.assign(goal + 2, vector<ll>(n + 2, -1));
        tot = goal, n1 = n, k1 = k;
        ll ans = dfs1(1, 0);
        return ans;
    }
};

//使用容斥原理
const int N = 200;
vector<ll> fac(N), inv(N);
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
    if (m < 0 || m > n) return 0;
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}
class Solution {
public:
    ll f(int n, int l, int k) {
        return fac[n] * inv[n - k] % MOD * qpow(n - k, l - k) % MOD;
    }
    int numMusicPlaylists(int n, int goal, int k) {
        //相同元素出现必须间隔至少k个其他元素
        //因此，每k+1个连续的必须都是不同的
        //如果只有第二个条件，我们计算出f(n,l,k)表示
        //使用i首歌，组成长度为goal的列表，相同元素间至少k个间隔
        //由于每k+1个连续的必须都是不同的，我们先让前k+1个自由选，即A(n,k+1)
        //后面来到每个位置的方案数量都*(n-k)，因为只有k个是不能用的
        //因此f(n,l,k)=A(n,k+1)*(n-k)^(l-k-1)
        //再考虑条件1，我们计算出全部情况，因为所有元素至少出现1次，
        //只需要减去每种元素不用的情况
        //考虑容斥：总情况-(不用1的情况)-(不用2的情况)...-(不用n的情况)    C(n,1)种
        //+(不用1且不用2的情况)++(不用1且不用3的情况)...                C(n,2)种
        //...
        //直到C(n,n)种,减掉即可
        init();
        ll ans = 0;
        for (int i = 0; i <= n; i++) {
            if (n - i - k < 0) continue;
            if (i & 1) {
                ans = ((ans - comb(n, i) * f(n - i, goal, k)) % MOD + MOD) % MOD;
            }
            else {
                ans = (ans + comb(n, i) * f(n - i, goal, k)) % MOD;
            }
        }
        return ans;
        //这种做法在模拟这种列表时是一个常见的结论
    }
};