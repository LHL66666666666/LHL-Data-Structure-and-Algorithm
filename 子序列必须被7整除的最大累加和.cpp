//本题目为面试题，无在线测试链接
//给定非负整数数组nums,
//可以选择任意子序列，要求子序列累加和被7整除，返回满足要求的最大累加和
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
ll dp[200005][7];
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
ll f1(vector<ll>& nums)
{
	memset(dp, -1, sizeof(dp));
	int n = nums.size();
	//子序列是删除一些元素剩下的
	//二维dp数组：dp[i][j]表示来0-i位置的数组，对7取余为j的最大累加和
	//要求dp[n-1][0]
	//注意：dp表中-1的数值表示在这个位置不存在这样的子序列，
	//我们在继承的时候可能无法继承的是一个不可达的序列，此时不要继承
	if (n == 1)
	{
		if (nums[0] % 7 == 0) return nums[0];
		return 0;
	}
	//先填base case第0行
	dp[0][nums[0] % 7] = nums[0];
	for (int i = 1; i <= n - 1; i++)
	{
		int tmp = nums[i] % 7;
		//我的状态定义
		//继承前面的，或者从自己开始变成一个新的子序列
		//继承
		for (int j = 0; j < 7; j++)
		{
			ll can1 = dp[i - 1][j];
			ll can2 = -1;
			if (dp[i - 1][(j - tmp + 7) % 7] != -1)
			{
				can2 = dp[i - 1][(j - tmp + 7) % 7] + nums[i];
			}
			dp[i][j] = max(can1, can2);
		}
		//还要考虑自己单独成为一个序列
		dp[i][tmp] = max(dp[i][tmp], nums[i]);
	}
	if (dp[n - 1][0] != -1) return dp[n - 1][0];
	else return 0;
}
//修改：允许空序列的存在
//dp[0][0]表示：考虑0个元素时，只有空子序列，
//这样定义可以避免还要讨论自己单独出来做子序列的情况，
//因为dp[i][tmp]一定可以由转移dp[i-1][0]转移而来
//也就是说dp[i][0]一直是有定义的
// 状态定义：
// dp[i][j] : nums[0...i-1]
// nums前i个数形成的子序列一定要做到，子序列累加和%7 == j
// 注意：这里i表示考虑了前i个元素，索引从1开始
//注意前i个元素，下标应该是i-1
int f2(vector<ll>& nums)
{
	int n = nums.size();
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 1; i < 7; i++) dp[0][i] = -1;
	for (int i = 1; i <= n; i++)
	{
		//注意这里是i-1
		int tmp = nums[i-1] % 7;
		for (int j = 0; j < 7; j++)
		{
			//不要i位置的数字
			dp[i][j] = dp[i - 1][j];
			//合法的情况下，要i位置的数字
			if (dp[i - 1][(j - tmp + 7) % 7] != -1)
			{
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][(j - tmp + 7) % 7] + nums[i-1]);
			}
		}
	}
	return dp[n][0];
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ll> nums = { 1,1,1,1,1,1 };
	cout << f1(nums) << '\n';
	return 0;
}