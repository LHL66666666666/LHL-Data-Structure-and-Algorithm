//快速幂模板
#define int long long
//递归实现：
//计算a的n次幂
//数学原理：a^n=(a^2)^(n/2)
int fastPower(int a, int n)
{
	int ans;
	if (n == 0)
	{
		ans = 1;  //结束条件
	}
	else {
		ans = fastPower(a*a, n / 2);  //递归调用
		if (n % 2 == 1)
		{
			ans *= a;  //如果n为奇数
		}
	}
	return ans;
}
//非递归实现：循环实现
int fastPower2(int a, int n)
{
	int ans = 1;
	while (n)
	{
		if (n & 1)
		{
			ans *= a;
		}
		a *= a;
		n = n >> 1;  //就是n/=2
	}
	return ans;
}