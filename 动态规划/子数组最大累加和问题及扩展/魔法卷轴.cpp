//魔法卷轴
//给定数组nums，其中可能含有正数，负数和0，
//每个魔法卷轴可以将nums中连续的一段全变为0
//i希望最大化数组整体累加和
//卷轴是否使用，使用多少随意，但是只有两个卷轴
//返回最大累加和
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
ll dp_prefix[200005];
ll dp_suffix[200005];
//预处理前缀和的前缀最大值
ll pre[200005];
ll premax[200005];
//预处理后缀和的后缀最大值
ll suf[200005];
ll sufmax[200005];
ll f(vector<ll>& nums)
{
	int n = nums.size();
	if (n == 1) return max(0LL, nums[0]);
	//预处理：前缀和的前缀最大值，后缀和的后缀最大值
	//注意：我们将一个都不取时也视作前缀/后缀
	//先算前缀和and后缀和
	pre[0] = nums[0];
	for (int i = 1; i < n; i++)
	{
		pre[i] = pre[i - 1] + nums[i];
	}
	suf[n - 1] = nums[n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		suf[i] = suf[i + 1] + nums[i];
	}
	//处理前缀和的前缀最大值，后缀和的后缀最大值
	//我们将一个都不取时也视作前缀/后缀
	premax[0] = max(0LL, pre[0]);
	for (int i = 1; i < n; i++)
	{
		premax[i] = max(premax[i - 1], pre[i]);
	}
	sufmax[n - 1] = max(0LL, suf[n - 1]);
	for (int i = n - 2; i >= 0; i--)
	{
		sufmax[i] = max(sufmax[i + 1], suf[i]);
	}
	//一共分三种情况：
	//1）不使用卷轴，答案即为累加和
	//2）使用一个卷轴
	//3）使用两个卷轴
	//又用到了处理前缀和后缀的技巧
	//情况1)，不使用卷轴
	ll p1 = 0;
	for (int i = 0; i < n; i++) p1 += nums[i];
	//情况2：使用一个卷轴
	//状态定义：
	//dp_prefix[i] 实际上表示：在 [0..i] 区间上，使用至多一次卷轴的最大和
	//状态转移：讨论当前位置的元素是否被卷轴刷成0
	//1.如果没被刷为0，为prefix[i-1]+nums[i]
	//2.如果被刷为0，由于卷轴操作的是子数组，此时这个位置的答案应为：到这个位置的所有前缀和的前缀最大值
	//原因：因为这个位置处在被操作的子数组内，也就是说i向左推一部分都被刷为0
	//我们要找最大的前缀和，就是操作之后前面的最大值，
	//两种情况取较大者
	//注意：可能全是负数，我们要留一个0作为：什么都没有的前缀和
	//0位置必须是0，因为要求必须使用1次
	dp_prefix[0] = 0LL;
	for (int i = 1; i < n; i++)
	{
		dp_prefix[i] = max(dp_prefix[i - 1] + nums[i], premax[i]);
	}
	ll p2 = dp_prefix[n - 1];
	//情况3：使用两个卷轴
	//我们将这两个卷轴分为前半部分和后半部分
	//前半部分和后半部分可以分离，也可以有重合，有重合相当于用了一个
	//我们只需压迫枚举分割数组的分割点x，计算[0..x-1]上用一次的最大值和[x...n-1]上用一次的最大值
	//二者相加即为答案
	//枚举分割点，找到最优分割即可
	//prefix[i]表示数组[i...n-1]位置上，必须使用一次卷轴，得到的最大累加和
	dp_suffix[n - 1] = 0LL;
	for (int i = n - 2; i >= 0; i--)
	{
		dp_suffix[i] = max(dp_suffix[i + 1] + nums[i], sufmax[i]);
	}
	//枚举分割点
	ll p3 = 0;
	for (int i = 1; i < n; i++)
	{
		p3 = max(p3, dp_prefix[i - 1] + dp_suffix[i]);
	}
	return p3;
	//实际上这里p3就是包含了所有情况
	//dp_prefix[i] 实际上表示：在 [0..i] 区间上，使用至多一次卷轴的最大和
	//dp_suffix[i]同理
	//p3 包含了：两个卷轴都在前半部分（第二个卷轴刷空区间）
	//p3 包含了：两个卷轴都在后半部分（第一个卷轴刷空区间）
	//p3 包含了：一个在前半部分，一个在后半部分
	//return max(p1, max(p2, p3));
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ll> nums = { 1,2,3,-4,5 };
	cout << f(nums) << '\n';
	return 0;
}