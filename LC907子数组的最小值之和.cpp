/*
给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。

由于答案可能很大，因此 返回答案模 10^9 + 7 。
*/
#include <vector>
#include <stack>
using namespace std;
class Solution {
public:
    const int MOD = 1e9 + 7;
	struct node {
		//这里的l,r指的是下标
		int l, r;
	}b[30005];
    int sumSubarrayMins(vector<int>& arr) {
		int n = arr.size();
        //我们可以维护一个单调栈，大压小
		stack<int> stk;
		//维护单调栈
		for (int i = 0; i < n; i++)
		{
			if (stk.empty())
			{
				stk.push(i);
			}
			else {
				//维护的单调栈必须严格大于
				if (arr[stk.top()] < arr[i])
				{
					//如果大于，直接push
					stk.push(i);
				}
				else {
					//弹出栈顶直到满足单调性
					//结算被弹出的元素的答案
					while (!stk.empty() && arr[stk.top()] >= arr[i])
					{
						int tmp = stk.top();
						stk.pop();
						if (!stk.empty())
						{
							b[tmp].l = stk.top();
						}
						else b[tmp].l = -1;
						b[tmp].r = i;
					}
					//a[i]压入栈
					stk.push(i);
				}
			}
		}
		//结算阶段,结算遍历完之后剩余元素
		//此时栈中的元素没有那个元素会使它弹出，所以他们的右侧不存在小于他们的数字
		//r都是-1
		while (!stk.empty())
		{
			int tmp = stk.top();
			stk.pop();
			b[tmp].r = -1;
			if (!stk.empty())
			{
				b[tmp].l = stk.top();
			}
			else b[tmp].l = -1;
		}
		//注意这里不要修正！！！修正会导致重复算
		//统计答案
		long long ans = 0;
		for (int i = 0; i < n; i++)
		{
			int cur_min = arr[i];
			int left, right;
			if (b[i].l != -1)
			{
				left = b[i].l + 1;
			}
			else left = 0;
			if (b[i].r != -1)
			{
				right = b[i].r - 1;
			}
			else right = n - 1;
			ans += (long long)(i - left + 1) * (right - i + 1) * cur_min;
			ans %= MOD;
		}
		return ans;
    }
};

/*
1. 问题重述
给定数组 arr，求所有连续子数组的最小值之和。

目标：用单调栈方法，以每个元素为最小值，计算它在多少个子数组中作为最小值，然后乘上该元素值，求和。要求不重不漏。

2. 单调栈方法设定
我们定义：

left[i] = 在 i 左边第一个 < arr[i] 的索引，如果没有则为 -1

right[i] = 在 i 右边第一个 <= arr[i] 的索引，如果没有则为 n

这样设计是为了让相同数值的元素在分配子数组时不重叠。

3. 辐射范围与计数
对于 arr[i]，它能作为最小值的子数组满足：

左端点 l 在 (left[i], i] 之间，即 left[i] + 1 <= l <= i

右端点 r 在 [i, right[i] - 1] 之间，即 i <= r <= right[i] - 1

这样的子数组个数 = (i - left[i]) × (right[i] - i)

每个这样的子数组的最小值 = arr[i]（因为范围内 arr[i] 是最小的，且边界外第一个左/右元素比它小或等于它，所以子数组包含 arr[i] 且它最小）。

4. 不重性证明
假设某个子数组 arr[l..r] 被两个不同的位置 i 和 j（i < j）都统计了。

如果 arr[i] != arr[j]：
不可能，因为一个子数组只能有一个最小值。

如果 arr[i] = arr[j]：
由于 i < j，考虑 right[i] 的定义：它是右边第一个 <= arr[i] 的位置。
因为 arr[j] = arr[i] 且 j > i，所以 right[i] <= j。
如果 right[i] <= j，那么对于 i 来说，右端点最多到 right[i] - 1，因此 r < j。
但是子数组要包含 j（因为 j 也统计它），则 r >= j，矛盾。
所以 i 和 j 不可能同时统计同一个子数组。

因此不重。

5. 不漏性证明
对任意子数组 arr[l..r]，设它的最小值为 m，可能有多个位置等于 m，取最右边的那个位置为 k（即 arr[k] = m 且 k 是 l..r 中等于 m 的最大索引）。

我们要证明：这个子数组会被 k 统计。

因为 k 是子数组中的最右边的 m，所以 k 右边的元素（若在子数组内）都 > m（否则与最右最小值矛盾）。
所以 right[k] > r（因为 right[k] 是右边第一个 <= m 的位置，必须在 r 右边或 r+1）。

因为 k 是子数组中的最小值，且左边可能还有等于 m 的，但 left[k] 是左边第一个 < m 的位置，所以 left[k] 必须在 l 左边或 l-1，即 left[k] < l。

因此：

l > left[k] → l >= left[k] + 1

l <= k（因为 k 在子数组内）

r >= k

r < right[k]

所以 (l, r) 在 k 的辐射范围内，会被 k 统计。

因此不漏。

6. 关键点总结
不重：因为对于相同值，右边界 right[i] 遇到等号就停止，所以相同值不会重复统计同一子数组。

不漏：每个子数组取它的最右最小值位置，这个位置一定可以统计到该子数组。

我们计算时并不需要显式找“最右最小值位置”，而是按上述 left/right 定义后，自然每个子数组被其最右最小值位置统计。
*/