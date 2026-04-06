//删除1个数字后长度为k的子数组最大累加和
//给定数组nums，求必须删除一个数字之后的数组中
//长度为k的子数组最大累加和
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <deque>
using namespace std;
typedef long long ll;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
//显然用单调队列维护长度为k+1的窗口最小值
//再维护滑动窗口的和即可
ll f(vector<ll>& nums, int k)
{
	int n = nums.size();
	if (n == 1) return 0;
	ll ans = -INF;
	//维护单调增的单调队列
	deque<int> dq;
	ll sum = 0;
	//初始化一下(k+1)的窗口
	for (int i = 0; i <= k; i++)
	{
		sum += nums[i];
		while (!dq.empty() && nums[dq.back()] > nums[i])
		{
			dq.pop_back();
		}
		dq.push_back(i);
	}
	ans = max(ans, sum - nums[dq.front()]);
	//滑动窗口
	for (int i = 1; i <= n - k - 1; i++) {
		int nxt = i + k;
		sum -= nums[i - 1];
		sum += nums[nxt];
		//记得先把过期元素弹出
		while (!dq.empty() && dq.front() < i) {
			dq.pop_front();
		}
		while (!dq.empty() && nums[dq.back()] > nums[nxt]) {
			dq.pop_back();
		}
		dq.push_back(nxt);
		ans = max(ans, sum - nums[dq.front()]);
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ll> nums = { 1,1,-4,5,1,4 };
	cout << f(nums, 3) << '\n';
	return 0;
}