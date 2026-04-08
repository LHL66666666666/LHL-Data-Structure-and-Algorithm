#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//结果始终为正：最大公约数定义为正数，无论输入参数的正负

//循环
int gcd1(int a, int b)
{
	if (a == 0 && b == 0)
	{
		return 0;
	}
	a = abs(a);
	b = abs(b);
	//先转成正数再找
	int min = a;
	if (a > b)
	{
		min = b;
	}
	for (int i = min; i > 0; i--)
	{
		if (a % i == 0 && b % i == 0)
		{
			return i;
		}
	}
}

//辗转相除（欧几里得算法）
//原理：两个整数的最大公约数等于其中较小的那个数和两数相除余数的最大公约数
//简单证明：设a=kb+r
//			(1)令d是a,b的一个公约数,有a=md,b=nd
//			则r=a-kb=(m-kn)d,则d也是r的因数，d是b,r的公约数
//			(2)同理令e是b,r的一个公约数,有b=pe,r=qe
//			则a=kb+r=(kp+q)e,则e也是a的因数，e是a,b的公约数
//现在取最大公约数d=gcd(a,b),e=gcd(b,r)
//根据(1)d是e的一个因子，设e=pd；同理根据(2)：e是d的一个因子，设d=qe。
//结合两点可知d=qpd，则qp=1，由于p、q均为正整数，所以p=q=1。进而可得d=e。

//更好理解的证明
// 设d = gcd(a, b)，则d | a且d | b，故d | (a - bq) = r。
// 所以d是b和r的公约数。现在设e是b和r的任意公约数，
// 则e | b且e | r，故e | (bq + r) = a。因此e也是a和b的公约数。
// 由于d是a和b的最大公约数，故e | d。这表明d是b和r的最大公约数，
// 即gcd(a, b) = gcd(b, r)

//写的时候不用管大小关系，取余会自动转过来
//迭代
int gcd2(int a, int b)
{
	if (a == 0 && b == 0)
	{
		return 0;
	}
	a = abs(a);
	b = abs(b);
	while (b > 0)
	{
		int temp = b;
		b = a % b;
		a = temp;
	}
	//最后一定是b==0,a!=0
	return a;
}

//递归
int gcd3(int a, int b)
{
	if (a == 0 && b == 0)
	{
		return 0;
	}
	if (b == 0)
	{
		return a;
	}
	a = abs(a);
	b = abs(b);

	return gcd3(b, a % b);
}

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d", gcd2(a, b));
	return 0;
}
