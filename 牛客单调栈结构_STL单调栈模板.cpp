/*
描述
给定一个可能含有重复值的数组 arr，找到每一个 i 位置左边和右边离 i 位置最近且值比 arr[i] 小的位置。返回所有位置相应的信息。
输入描述：
第一行输入一个数字 n，表示数组 arr 的长度。
以下一行输入 n 个数字，表示数组的值
输出描述：
输出n行，每行两个数字 L 和 R，如果不存在，则值为 -1，下标从 0 开始。
*/
//1≤n≤1000000
//−1000000≤arr[i]​≤1000000
#include <iostream>
#include <stack>
using namespace std;
int a[1000005];
struct node {
	//这里的l,r指的是下标
	int l, r;
}b[1000005];
int main() {
	//先使用STL stack实现一下
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
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
			if (a[stk.top()] < a[i])
			{
				//如果大于，直接push
				stk.push(i);
			}
			else {
				//弹出栈顶直到满足单调性
				//结算被弹出的元素的答案
				while (!stk.empty() && a[stk.top()] >= a[i])
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
	//修正阶段，因为可能出现相同的元素
	//l一定是对的，因为我们维护了严格单调的单调栈
	//检查每个元素的r
	//反向遍历，因为如果有相同数字，正确答案出现在后面
	for (int i = n - 1; i >= 0; i--)
	{
		if ( b[i].r!=-1 && a[i] == a[b[i].r])
		{
			//修正
			b[i].r = b[b[i].r].r;
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << b[i].l << ' ' << b[i].r << '\n';
	}
	return 0;
}
