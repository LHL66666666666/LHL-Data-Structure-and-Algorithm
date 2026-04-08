#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 19650827;
int n;
vector<int> a;
vector<vector<vector<int>>> dp;
//先尝试递归
ll dfs(int l, int r, int f)
{
	if (dp[l][r][f] != -1) return dp[l][r][f];
	if (l == r)
	{
		return 1;
	}
	if (r - l == 1)
	{
		if (f == 0)
		{
			if (a[r] > a[l])
			{
				return 2;
			}
			else return 0;
		}
		if (f == 1 || f == 2)
		{
			if (a[l] < a[r]) return 1;
			else return 0;
		}

	}
	//f=0表示可以从两侧来取
	//f=1表示只能从左侧来取
	//f=2表示只能从右侧来取
	ll ans = 0;
	//从左侧取
	if (f == 1 || f == 0)
	{
		int le = a[l];
		if (le < a[l + 1] && le < a[r])
		{
			ans += dfs(l + 1, r, 0);
		}
		else if (le<a[r] && le>a[l + 1])
		{
			ans += dfs(l + 1, r, 2);
		}
		ans %= MOD;
	}
	//从右侧取
	if (f == 2 || f == 0)
	{
		int ri = a[r];
		if (a[r] > a[l] && a[r] > a[r - 1])
		{
			ans += dfs(l, r - 1, 0);
		}
		if (a[r] > a[l] && a[r] < a[r - 1])
		{
			ans += dfs(l, r - 1, 1);
		}
		ans %= MOD;
	}
	dp[l][r][f] = ans;
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//对于初始的队形，每个元素排布位置只与前一个元素有关
	cin >> n;
	a.resize(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	//来到某一状态的数组，我们考虑从他的左侧或者右侧拿元素，
	//拿走之后剩下的两个端点就是可能作为这个数字前一个位置的元素
	//注意：数组中的元素各不相同
	dp.assign(n + 1, vector<vector<int>>(n + 1, vector<int>(3,-1)));
	cout << dfs(1, n, 0) << '\n';
	return 0;
}