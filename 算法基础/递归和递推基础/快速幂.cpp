#define ll long long
//非递归，基于位运算
long long fastpow(long long a, long long b, int mod)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1)
		{
			ans =(ans*a)%mod;
		}
		a = (a*a)%mod;
		b /= 2;
	}
	return ans;
}
//递归，基于分治
ll fastpow2(ll a, ll b, int mod)
{
	if (b == 0)
	{
		return 1;
	}
	if (b == 1)
	{
		return a % mod;
	}
	ll m = fastpow2(a, b / 2, mod);
	if (b & 1)
	{
		return ((m % mod * m % mod) * a % mod) % mod;
	}
	else return (m % mod) * (m % mod) % mod;
}