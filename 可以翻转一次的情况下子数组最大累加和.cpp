//可以翻转一次的情况下求子数组最大累加和
//给定数组nums
//允许随意选择数组中的任意一段进行翻转，也就是子数组逆序的调整
//比如：反转数组[1,2,3,4,5,6]的[2~4]范围，得到[1,2,5,4,3,6]
//求必须随意翻转一次的情况下，子数组最大累加和
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
ll f(vector<ll>& nums)
{
	int n = nums.size();
	if (n == 1) return nums[0];
	//我们从翻转范围与翻转之后得到的答案范围的关系入手
	//首先排除翻转范围与翻转之后得到的答案范围具有相互包含关系
	//原因：
	//首先给出断言：翻转不影响翻转区域内部子数组的连续性
	//1）假设翻转范围包含翻转之后的答案范围，由于子数组连续性不改变，相当于未翻转
	//2）假设翻转之后的答案范围包含翻转范围，同样相当于未翻转
	//由此我们得出：翻转范围与翻转之后得到的答案范围是：交叉关系
	//那么：必定存在一个划分点x，使得x+1及其之后的保持原数组，x及其之前的为经过翻转的子数组
	//根据断言：翻转不影响翻转区域内部子数组的连续性，我们只需找到[0..x]子数组最大累加和，可保证翻转之后一定与x+1相接
	//因此，我们遍历每一个划分点x，找到x+1为开头位置的子数组最大累加和，再加上[0..x]上子数组最大累加和，取一个最大值即可
	//1.求每个位置结尾的子数组最大累加和，并对其求前缀最大值数组
	ll sum = -INF;
	vector<ll> dp(n);
	dp[0] = nums[0];
	for (int i = 1; i < n; i++)
	{
		dp[i] = max(nums[i], dp[i - 1] + nums[i]);
	}
	//计算不反转的情况
	for (int i = 0; i < n; i++) sum = max(sum, dp[i]);
	vector<ll> pre(n);
	pre[0] = dp[0];
	for (int i = 1; i < n; i++)
	{
		pre[i] = max(pre[i - 1], dp[i]);
	}
	//2.求每个位置开头的子数组最大累加和
	vector<ll> dp2(n);
	dp2[n - 1] = nums[n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		dp2[i] = max(nums[i], dp2[i + 1] + nums[i]);
	}
	//3.枚举分割点
	for (int i = 0; i < n - 1; i++)
	{
		sum = max(sum, pre[i] + dp2[i + 1]);
	}
	return sum;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ll> nums = { -1,-1,-4,-5,-1,-4 };
	cout << f(nums) << '\n';
	return 0;
}
//总结一下：本题的关键点：
//1.找出反转区域与最终答案区域的关系
//2.断言：翻转不影响翻转区域内部子数组的连续性
//3.记得考虑不反转的情况