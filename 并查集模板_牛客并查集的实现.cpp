#include <iostream>
#include <stack>
const int MAXN = 1e6 + 5;
int n, m;
//装父节点的数组
int father[MAXN];
//装这个节点所在的集合的大小(只有代表元素的size才认为是有效的
int size[MAXN];
//初始化
void build()
{
	//本题要求下标索引从1开始
	for (int i = 1; i <= n; i++)
	{
		father[i] = i;
		size[i] = 1;
	}
}
//find方法，查询集合的代表元素
int find(int i)
{
	//这里同时实现扁平化(路径压缩)
	std::stack<int> stk;
	while (i != father[i])
	{
		//当这个元素不是自己指向自己时
		stk.push(i);
		//迭代
		i = father[i];
	}
	//退出循环代表已经是自己指向自己,即为代表元素
	//扁平化
	while (!stk.empty())
	{
		int tmp = stk.top();
		stk.pop();
		//父亲节点直接指向代表元素i
		father[tmp] = i;
	}
	return i;
}
//isSameset方法，查询是否是同一集合
bool isSameSet(int a, int b)
{
	//只需查询代表元素
	return find(a) == find(b);
}
//union方法，把a所在的集合与b所在的集合合并在一起
void Union(int a, int b)
{
	//先找到代表元素，判断是否本来就在一个集合
	int fa = find(a);
	int fb = find(b);
	if (fa != fb)
	{
		//小挂大
		if (size[fa] >= size[fb])
		{
			father[fb] = fa;
			size[fa] += size[fb];
		}
		else {
			father[fa] = fb;
			size[fb] += size[fa];

		}
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	build();
	while (m--)
	{
		int op;
		std::cin >> op;
		int x, y;
		std::cin >> x >> y;
		if (op == 1)
		{
			if (isSameSet(x, y))
			{
				printf("Yes\n");
			}
			else printf("No\n");
		}
		else if (op == 2)
		{
			Union(x, y);
		}
	}
	return 0;
}