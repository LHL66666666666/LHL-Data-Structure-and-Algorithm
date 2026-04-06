#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
constexpr int INF = 0x3f3f3f3f;
vector<vector<int>> dp;
int dfs(string& s, int l, int r)
{
	if (l == r)
	{
		return 1;
	}
	if (dp[l][r] != -1) return dp[l][r];
	//枚举每种颜色
	int ans = INF;
	//情况1:端点颜色相同
	if (s[l] == s[r])
	{
		//实际上这里不需要二者取最小，因为二者等价!!
		ans = min(dfs(s, l + 1, r), dfs(s, l, r - 1));
	}
	//情况2：端点处颜色不同
	//枚举分割点
	for (int i = l; i < r; i++)
	{
		ans = min(ans, dfs(s, l, i) + dfs(s, i + 1, r));
	}
	dp[l][r] = ans;
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	int n = s.size();
	//显然要枚举最开始时涂色的区域
	/*
	首先我们想想可以把涂色过程归类为几种策略：
	先涂一个大区间，然后一个小区间包含在大区间内。
	AAABBBBAAA
	涂两个并列且没有交集的区间。（如果有交集会互相覆盖，又相当于没有交集了，所以不用考虑）
	AAAABBBB
	*/
	//关键：在遍历到一个区间时，我们先处理边缘的颜色一定不会让答案更差
	//我们基于边界颜色展开讨论
	//我们定义dp[i][j]为区间[i,j]上达成目标所需的最少染色次数
	//那么根据上面两种染色策略，我们考虑区间端点是否有相同的颜色
	//1.如果端点颜色相同,s[i]==s[j],那么我们可以使用策略1
	//转移方程为dp[i][j]=dp[i][j-1]或dp[i+1][j],含义就是本次操作以左/右端点为基准涂色
	//后续只需要考虑排除这个基准点的情况
	//2.不管两端点处颜色是否相同，我们都可以采取策略2，枚举分割点，分成两个区间来递归
	dp.assign(n + 1, vector<int>(n + 1, -1));
	cout << dfs(s, 0, n - 1) << '\n';
	return 0;
}