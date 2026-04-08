#include <iostream>
#include <vector>
#include <deque>
typedef long long ll;
using namespace std;
int n, tot;
struct node {
	int v, w, m;
}a[105];
//原始版本，超时
void solve1()
{
	vector<vector<ll>> dp(n + 1, vector<ll>(tot + 1));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= tot; j++)
		{
			//不要i号位置的物品
			dp[i][j] = dp[i - 1][j];
			//要i号位置的物品，枚举要几个
			for (int k = 1; k <= a[i].m && j >= k * a[i].w; k++)
			{
				if (j - k * a[i].w >= 0)
				{
					dp[i][j] = max(dp[i][j], dp[i - 1][j - k * a[i].w] + k * a[i].v);
				}
			}
		}
	}
	cout << dp[n][tot] << '\n';
}
//二进制分组优化
void solve2()
{
	vector<ll> val(1);
	vector<ll> wei(1);
	//预处理原物品，进行二进制分组
	for (int i = 1; i <= n; i++)
	{
		int tmp = a[i].m;
		for (int k = 1; k <= tmp; k <<= 1)
		{
			val.emplace_back(a[i].v * k);
			wei.emplace_back(a[i].w * k);
			tmp -= k;
		}
		if (tmp > 0)
		{
			val.emplace_back(a[i].v * tmp);
			wei.emplace_back(a[i].w * tmp);
		}
	}
	int n1 = val.size();
	vector<ll> dp(tot+1);
	//跑01背包
	for (int i = 1; i < n1; i++)
	{
		for (int j = tot; j >= 0; j--)
		{
			if (j - wei[i] >= 0) dp[j] = max(dp[j], dp[j - wei[i]] + val[i]);
		}
	}
	cout << dp[tot] << '\n';
}
//单调队列优化
//求指标的函数
int value(int i,int j,vector<vector<ll>>& dp)
{
	return dp[i - 1][j] - j / a[i].w * a[i].v;
}
void solve3()
{
	//第一步按照余数分组：
	//每个货物有重量w，我们处理到dp[i][j]时，只依赖上面一列的dp[i-1][j-w*k]
	//因此，按照余数分组之后，我们每一行按照余数来填即可，每一组分开处理
	//单调队列的思路
	//受数量m的限制，dp表每个格子在填写的时候，依赖于上面一行最多m+1个格子，分别是这个货物取0个到m个
	//且跟到这个格子的距离是相关的，这是一个定长的窗口
	//关键在于如何确定单调队列存储的指标，即按照什么来组织单调队列
	//朴素的想法是：dp[i-1][j-w*k]+a[i].val*k,然而，随着i的变化，k是不断增加的，
	//我们不能将一个随i变化的指标加入队列中，
	//因此我们考虑我们当前枚举的选择i号位置的货物数量即为k,依赖的格子为dp[i-1][lst],
	//有k=(i-lst)/w,对于每个i位置，我们将i/w拆出来作为外面的，变为i/w*a[i].val + dp[i-1][lst]-lst/w*a[i].val
	//容易发现后面的部分之和自己的下标lst有关系，因此我们将后面这个做指标存入单调队列
	//对于每一个i只需要求i/w*a[i].val + max( dp[i-1][lst]-lst/w*a[i].val )即可
	vector<vector<ll>> dp(n + 1, vector<ll>(tot + 1));
	for (int i = 1; i <= n; i++)
	{
		//按照列的余数分组，注意是对重量取余
		for (int mod = 0; mod <= min(tot, a[i].w - 1); mod++)
		{
			deque<int> dq;
			for (int j = mod; j <= tot; j += a[i].w)
			{
				//单调队列，队列中维护我们的"指标"严格单调递减
				while (!dq.empty() && value(i, dq.back(), dp) <= value(i, j, dp))
				{
					dq.pop_back();
				}
				//检查过期元素
				while (!dq.empty() && dq.front()<j-a[i].m*a[i].w)
				{
					dq.pop_front();
				}
				//加入新元素
				dq.push_back(j);
				dp[i][j] = j / a[i].w * a[i].v + value(i, dq.front(), dp);
			}
		}
	}
	cout << dp[n][tot] << '\n';
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> tot;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].v >> a[i].w >> a[i].m;
	}
	solve3();
	return 0;
}