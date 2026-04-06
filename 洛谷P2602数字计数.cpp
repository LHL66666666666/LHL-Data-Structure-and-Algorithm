#include <vector>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
using ll = long long;
vector<ll> ans;
ll dp[10][15][15][2][2];
ll dfs(string& s, int x, int id, int cnt, int islim, int isnum)
{
	if (id == s.size())
	{
		if (isnum) return cnt;
		else return 0;
	}
	if (dp[x][id][cnt][islim][isnum] != -1) return dp[x][id][cnt][islim][isnum];
	ll ans = 0;
	if (isnum == 0)
	{
		ans += dfs(s, x, id + 1, 0, 0, 0);
	}
	if (islim)
	{
		if (isnum)
		{
			for (int i = 0; i < 10; i++)
			{
				int nxt = cnt + (i == x);
				if (i + '0' == s[id])
				{
					ans += dfs(s, x, id + 1, nxt, 1, 1);
				}
				else if (i + '0' < s[id])
				{
					ans += dfs(s, x, id + 1, nxt, 0, 1);
				}
			}
		}
		else {
			for (int i = 1; i < 10; i++)
			{
				int nxt = cnt + (i == x);
				if (i + '0' == s[id])
				{
					ans += dfs(s, x, id + 1, nxt, 1, 1);
				}
				else if (i + '0' < s[id])
				{
					ans += dfs(s, x, id + 1, nxt, 0, 1);
				}
			}
		}
	}
	else {
		if (isnum)
		{
			for (int i = 0; i < 10; i++)
			{
				int nxt = cnt + (i == x);
				ans += dfs(s, x, id + 1, nxt, 0, 1);
			}
		}
		else {
			for (int i = 1; i < 10; i++)
			{
				int nxt = cnt + (i == x);
				ans += dfs(s, x, id + 1, nxt, 0, 1);
			}
		}
	}
	dp[x][id][cnt][islim][isnum] = ans;
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string a, b;
	cin >> a >> b;
	ans.assign(10, 0);
	for (int i = 0; i < 10; i++)
	{
		memset(dp, -1, sizeof(dp));
		ans[i] += dfs(b, i, 0, 0, 1, 0);
	}
	for (int i = 0; i < 10; i++)
	{
		memset(dp, -1, sizeof(dp));
		ans[i] -= dfs(a, i, 0, 0, 1, 0);
	}
	for (int i = 0; i < a.size(); i++)
	{
		ans[a[i] - '0']++;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << ans[i] << ' ';
	}
	cout << '\n';
	return 0;
}