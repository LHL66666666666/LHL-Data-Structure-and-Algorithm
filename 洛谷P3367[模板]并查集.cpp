#include <iostream>
#include <stack>
const int MAXN = (int)2e5 + 5;
int n, m;
//装父节点的数组
int father[MAXN];
//初始化
void build()
{
	//本题要求下标索引从1开始
	for (int i = 1; i <= n; i++)
	{
		father[i] = i;
	}
}
//find方法，查询集合的代表元素
int find(int i)
{
	if (i != father[i])
	{
		//注意这里一遍调递归一遍修改了父节点
		father[i] = find(father[i]);
	}
	return father[i];
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
	father[find(a)] = find(b);
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
		if (op == 2)
		{
			if (isSameSet(x, y))
			{
				printf("Y\n");
			}
			else printf("N\n");
		}
		else if (op == 1)
		{
			Union(x, y);
		}
	}
	return 0;
}
//这是并查集最经典的写法，只需要进行扁平化优化，不需要小挂大