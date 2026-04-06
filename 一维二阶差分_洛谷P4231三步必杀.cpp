/*
N 个柱子排成一排，一开始每个柱子损伤度为 0。

接下来勇仪会进行 M 次攻击，每次攻击可以用 4 个参数 l,r,s,e 来描述：

表示这次攻击作用范围为第 l 个到第 r 个之间所有的柱子(包含 l,r)，对第一个柱子的伤害为 s，对最后一个柱子的伤害为 e。

攻击产生的伤害值是一个等差数列。若 l=1,r=5,s=2,e=10，则对第 1∼5 个柱子分别产生 2,4,6,8,10 的伤害。

鬼族们需要的是所有攻击完成之后每个柱子的损伤度。

输入格式
第一行 2 个整数 N,M，用空格隔开，下同。

接下来 M 行，每行 4 个整数 l,r,s,e，含义见题目描述。

数据保证对每个柱子产生的每次伤害值都是整数。

输出格式
由于输出数据可能过大无法全部输出，为了确保你真的能维护所有柱子的损伤度，只要输出它们的异或和与最大值即可。

（异或和就是所有数字按位异或起来的值。）

（异或运算符在 c++ 里为 ^。）
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define ll long long
ll a[10000005];
void set(ll a[], int d, int l,int r,int s, int e)
{
	a[l] += s;
	a[l + 1] += d - s;
	a[r + 1] -= e + d;
	a[r + 2] += e;
}
void build(ll a[], int n)
{
	for (int i = 2; i <= n; i++)
	{
		a[i] += a[i - 1];
	}
	for (int i = 2; i <= n; i++)
	{
		a[i] += a[i - 1];
	}
}
ll max(ll a, ll b)
{
	return a > b ? a : b;
}
int main()
{
	int n, m;
	scanf("%d%d",&n,&m);
	while (m--)
	{
		int l, r, s, e;
		scanf("%d%d%d%d", &l, &r, &s, &e);
		int d = (e - s) / (r - l);
		//公差d，是一个整数
		set(a, d, l, r, s, e);
	}
	build(a, n);
	ll ans = 0, x = a[1];
	for (int i = 1; i <= n; i++)
	{
		ans ^= a[i];
		x = max(x, a[i]);
	}
	cout << ans << ' ' << x;

	
	return 0;
}