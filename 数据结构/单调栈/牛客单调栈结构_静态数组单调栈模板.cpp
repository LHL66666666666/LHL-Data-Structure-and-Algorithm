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
using std::cin;
using std::cout;
//静态数组实现栈
const int N = 1e6 + 5;
int stack[N];
//size表示栈中元素个数，size=0表示空
//下标从0到size-1
int size = 0;
//判断空
bool isEmpty()
{
	return size == 0;
}
//入栈
void push(int x)
{
	stack[size++] = x;
}
//弹出
void pop()
{
	--size;
}
//查询栈顶元素
int top()
{
	return stack[size - 1];
}
//元素个数
int getsize()
{
	return size;
}
int a[N];
struct node {
	int l, r;
}ans[N];
int main()
{
	//初始化size
	size = 0;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	//第一个阶段：遍历阶段，维护单调栈
	for (int i = 0; i < n; i++)
	{
		while (size > 0 && a[top()] >= a[i])
		{
			//弹出栈中不满足单调的元素并结算答案
			int tmp = top();
			pop();
			ans[tmp].r = i;
			if (!isEmpty())
			{
				ans[tmp].l = top();
			}
			else ans[tmp].l = -1;
		}
		push(i);
	}
	//第二阶段：将栈中的元素结算
	//记得弹出
	while (!isEmpty())
	{
		int tmp = top();
		pop();
		ans[tmp].r = -1;
		if (!isEmpty())
		{
			ans[tmp].l = top();
		}
		else ans[tmp].l = -1;
	}
	//第三阶段：修正阶段,处理相同的元素
	//反向遍历
	for (int i = n - 1; i >= 0; i--)
	{
		if (ans[i].r!=-1 && a[ans[i].r] == a[i])
		{
			ans[i].r = ans[ans[i].r].r;
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << ans[i].l << ' ' << ans[i].r << '\n';
	}
	return 0;
}