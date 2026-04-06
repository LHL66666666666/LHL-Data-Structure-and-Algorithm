#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
const int MOD = 1e9+7;
ll dp[1005][11][11][2][2][2];
ll dfs(string& s, int id, int lst1, int lst2, int islim, int isnum,int ispal)
{
	if (id == s.size())
	{
		return (isnum && ispal);
	}
	if (dp[id][lst1][lst2][islim][isnum][ispal] != -1) return dp[id][lst1][lst2][islim][isnum][ispal];
	ll ans = 0;
	//如果前面没选数字。到这里可以继续不选
	if (isnum == 0)
	{
		ans += dfs(s, id + 1, 10, 10, 0, 0, 0);
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
				if (i < s[id] - '0')
				{
					//判回文
					//如果新形成回文，强行转ispal为1
					if (i == lst1 || i == lst2)
					{
						ans += dfs(s, id + 1, i, lst1, 0, 1, 1);
					}
					//否则继承上一个的
					else ans += dfs(s, id + 1, i, lst1, 0, 1, ispal);
				}
				else if (i == s[id] - '0')
				{
					if (i == lst1 || i == lst2)
					{
						ans += dfs(s, id + 1, i, lst1, 1, 1, 1);
					}
					else ans += dfs(s, id + 1, i, lst1, 1, 1, ispal);
				}
			}
		}
		//没选过，不能选0
		else {
			for (int i = 1; i < 10; i++)
			{
				if (i < s[id] - '0')
				{
					if (i == lst1 || i == lst2)
					{
						ans += dfs(s, id + 1, i, lst1, 0, 1, 1);
					}
					else ans += dfs(s, id + 1, i, lst1, 0, 1, ispal);
				}
				else if (i == s[id] - '0')
				{
					if (i == lst1 || i == lst2)
					{
						ans += dfs(s, id + 1, i, lst1, 1, 1, 1);
					}
					else ans += dfs(s, id + 1, i, lst1, 1, 1, ispal);
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
				if (i == lst1 || i == lst2)
				{
					ans += dfs(s, id + 1, i, lst1, 0, 1, 1);
				}
				else ans += dfs(s, id + 1, i, lst1, 0, 1, ispal);
			}
		}
		//没选过，不能选0
		else {
			for (int i = 1; i < 10; i++)
			{
				if (i == lst1 || i == lst2)
				{
					ans += dfs(s, id + 1, i, lst1, 0, 1, 1);
				}
				else ans += dfs(s, id + 1, i, lst1, 0, 1, ispal);
			}
		}
	}
	ans %= MOD;
	dp[id][lst1][lst2][islim][isnum][ispal] = ans;
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string l, r;
	cin >> l >> r;
	//实际上，只需要出现长度为2的或长度为3的回文，后续就可以随意选择
	memset(dp, -1, sizeof(dp));
	ll ans1 = dfs(l, 0, 10, 10, 1, 0, 0);
	memset(dp, -1, sizeof(dp));
	ll ans2 = dfs(r, 0, 10, 10, 1, 0, 0);
	ll ans = (ans2 - ans1+MOD)%MOD;
	//特判l
	int flag = 0;
	for (int i = 0; i < l.size(); i++)
	{
		if (i - 1 >= 0 && l[i] == l[i - 1]) flag = 1;
		if (i - 2 >= 0 && l[i] == l[i - 2]) flag = 1;
	}
	ans += flag;
	ans %= MOD;
	cout << ans << '\n';
	return 0;
}