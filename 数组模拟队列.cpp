/*
队列（queue）是一种具有「先进入队列的元素一定先出队列」性质的表。
由于该性质，队列通常也被称为先进先出（first in first out）表，简称 FIFO 表。
*/
//洛谷B3616链表模板
/*
请你实现一个队列（queue），支持如下操作：

push(x)：向队列中加入一个数 x。
pop()：将队首弹出。如果此时队列为空，则不进行弹出操作，并输出 ERR_CANNOT_POP。
query()：输出队首元素。如果此时队列为空，则输出 ERR_CANNOT_QUERY。
size()：输出此时队列内元素个数。
*/
#include <iostream>
#include "数组模拟队列.h"
using namespace std;
int a[10005];
int pl = 0, pr = 0;
//pl,pr两个指针模拟队列首尾，队列的范围是[pl,pr)
//空队列：pl==pr
void push(int x)
{
	a[pr++] = x;
}
void pop()
{
	if (pl < pr)
	{
		pl++;
	}
	else cout << "ERR_CANNOT_POP" << endl;
}
void query()
{
	if (pl < pr)
	{
		cout << a[pl] << endl;
	}
	else cout << "ERR_CANNOT_QUERY" << endl;
}
void size()
{
	cout << pr - pl << endl;
}
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int opt;
		cin >> opt;
		if (opt == 1)
		{
			int x;
			cin >> x;
			push(x);
		}
		else if (opt == 2)
		{
			pop();
		}
		else if (opt == 3)
		{
			query();
		}
		else size();
	}
	return 0;
}

//另一实现：
//N代表操作次数的上限
const int N = 1e6 + 5;
int queue[N];
int l = 0, r = 0;
//检查是否为空队列
bool isEmpty()
{
	return l == r;
}
//添加数
void push(int x)
{
	queue[r++] = x;
}
//弹出
int pop()
{
	return queue[l++];
}
//查询队列头部
int head() 
{
	return queue[l];
}
//查询队列尾部
int tail()
{
	return queue[r - 1];
}
//大小
int size()
{
	return r - l;
}
