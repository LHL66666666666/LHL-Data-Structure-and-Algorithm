#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
const int MOD = 998244353;
ll dp[20][11][2][2];
ll dfs(string& s, int id, int lst, int islim, int isnum)
{
	if (id == s.size())
	{
		return isnum;
	}
	if (dp[id][lst][islim][isnum] != -1) return dp[id][lst][islim][isnum];
	ll ans = 0;
	//如果前面没选数字。到这里可以继续不选
	if (isnum == 0)
	{
		ans += dfs(s, id + 1, 0, 0, 0);
	}
	//如果这个位置要选
	//如果被限制
	if (islim)
	{
		//分情况：前面是否选过数字
		//如果选过
		if (isnum)
		{
			for (int i = 0; i < 10; i++)
			{
				if (abs(lst - i) >= 2)
				{
					if (i < s[id] - '0')
					{
						ans += dfs(s, id + 1, i, 0, 1);
					}
					else if (i == s[id] - '0')
					{
						ans += dfs(s, id + 1, i, 1, 1);
					}
				}
			}
		}
		//没选过，不能选0
		else {
			for (int i = 1; i < 10; i++)
			{
				if (i < s[id] - '0')
				{
					ans += dfs(s, id + 1, i, 0, 1);
				}
				else if (i == s[id] - '0')
				{
					ans += dfs(s, id + 1, i, 1, 1);
				}

			}
		}
	}
	//没被限制
	else {
		if (isnum)
		{
			for (int i = 0; i < 10; i++)
			{
				if (abs(lst - i) >= 2)
				{
					ans += dfs(s, id + 1, i, 0, 1);
				}
			}
		}
		//没选过，不能选0
		else {
			for (int i = 1; i < 10; i++)
			{
				ans += dfs(s, id + 1, i, 0, 1);
			}
		}
	}
	dp[id][lst][islim][isnum] = ans;
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll a, b;
	cin >> a >> b;
	string s1, s2;
	while (a)
	{
		s1.push_back('0' + a % 10);
		a /= 10;
	}
	while (b)
	{
		s2.push_back('0' + b % 10);
		b /= 10;
	}
	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());
	memset(dp, -1, sizeof(dp));
	ll ans1 = dfs(s1, 0, 0, 1, 0);
	memset(dp, -1, sizeof(dp));
	ll ans2 = dfs(s2, 0, 0, 1, 0);
	//特判a
	int flag = 1;
	for (int i = 1; i < s1.size(); i++)
	{
		if (abs(s1[i] - s1[i - 1]) < 2) flag = 0;
	}
	ll ans = ans2 - ans1;
	ans += flag;
	cout << ans << '\n';
	return 0;
}