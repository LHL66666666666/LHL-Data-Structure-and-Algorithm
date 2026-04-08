#include <iostream>
#include <vector>
typedef long long ll;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
struct node {
	int w, c;
}a[105];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, h;
	cin >> n >> h;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].w >> a[i].c;
	}
	//dp[i][j]表示前i个任意买，要得到j重量的最小开销
	vector<vector<ll>> dp(n + 1, vector<ll>(h + 5001, -INF));
	//base case
	//dp[0][0]为0,其余dp[0][j]为-INF不可达
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= h + 5000; j++)
		{
			dp[i][j] = dp[i - 1][j];
			int lst = j - a[i].w;
			if (lst >= 0 && dp[i][lst] != -INF)
			{
				if (dp[i][j] == -INF) dp[i][j] = dp[i][lst] + a[i].c;
				else dp[i][j] = min(dp[i][j], dp[i][lst] + a[i].c);
			}
		}
	}
	ll ans = INF;
	for (int i = h; i <= h + 5000; i++)
	{
		if (dp[n][i] > 0)
		{
			ans = min(ans, dp[n][i]);
		}
	}
	cout << ans << '\n';
	return 0;
}