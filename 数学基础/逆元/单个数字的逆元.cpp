/*
如果你想计算：a / b，然后 % MOD结果
1) 必须保证a/b可以整除，每次有除法的时候，都需要保证绝对能整除
2) 必须保证MOD是质数，求逆元的原理是费马小定理，要求MOD是质数，比如1000000007
3) 必须保证b和MOD的最大公约数为1，也就是b和MOD互质

题目给定的数据一定会满足上面三点，那么就有如下的结论，直接记住，证明略，不用多问为什么
先求 1/b 的乘法同余数，也就是b的逆元，b的逆元 = b的(MOD-2)次方 % MOD
然后，(a / b) % MOD的结果，等于，((a % MOD) * (b的逆元)) % MOD的结果

*/
using ll = long long;
constexpr ll MOD = 998244353;
ll qpow(ll a, ll b)
{
	ll res = 1;
	ll base = a;
	while (b)
	{
		if (b & 1)
		{
			res = (res % MOD * base % MOD) % MOD;
		}
		base = (base % MOD * base % MOD) % MOD;
		b >>= 1;
	}
	return res;
}
ll f(ll x, ll y)
{
	ll inv = qpow(y, MOD - 2) % MOD;
	return (x % MOD) * inv % MOD;
}