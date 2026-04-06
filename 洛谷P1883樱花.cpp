#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
int tot,n;
struct node {
	int t, c, p;
}a[10005];
int main()
{
	//实际上，那些可以看无限的数量的也不是完全无线，跟据总时间限制，可以变成有限次数
	//就变成多重背包问题
	int hh1, hh2;
	int mm1, mm2;
	scanf_s("%d:%d %d:%d", &hh1, &mm1, &hh2, &mm2);
	//cout << hh1 << ' ' << mm1 << ' ' << hh2 << ' ' << mm2;
	tot = (hh2 - hh1) * 60 + mm2 - mm1;
	//cout << tot << '\n';
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].t >> a[i].c >> a[i].p;
		if (a[i].p == 0)
		{
			a[i].p = tot / a[i].t + 1;
		}
	}
	//变成多重背包
	//使用二进制分组优化
	vector<int> val(1);
	vector<int> wei(1);
	for (int i = 1; i <= n; i++)
	{
		int tmp = a[i].p;
		for (int k = 1; k <= tmp; k <<= 1)
		{
			val.emplace_back(k * a[i].c);
			wei.emplace_back(k * a[i].t);
			tmp -= k;
		}
		if (tmp > 0)
		{
			val.emplace_back(tmp * a[i].c);
			wei.emplace_back(tmp * a[i].t);
		}
	}
	int n1 = val.size();
	//跑01背包
	vector<int> dp(tot + 1);
	for (int i = 1; i < n1; i++)
	{
		for (int j = tot; j >= 0; j--)
		{
			if (j - wei[i] >= 0)
			{
				dp[j] = max(dp[j], dp[j - wei[i]] + val[i]);
			}
		}
	}
	cout << dp[tot] << '\n';
	return 0;
}