#include <cstdlib>
#include <ctime>
//我们要找到数组中第k小或第k大的数字，基于快排的思路(荷兰国旗优化版本)
//下面的例子是求数组中从小到大第idx个元素的
int first, last;
void partition(int a[], int l, int r, int x)
{
	first = l, last = r;
	//维护三个指针
	int p = l;
	while (p <= last)
	{
		if (a[p] < x)
		{
			int tmp = a[p];
			a[p] = a[first];
			a[first] = tmp;
			first++;
			p++;
		}
		else if (a[p] > x)
		{
			int tmp = a[p];
			a[p] = a[last];
			a[last] = tmp;
			last--;
		}
		else p++;

	}


}
int quickSortbasedrandomselect(int a[], int size,int l,int r,int idx)
{
	int n = size;
	if (l >= r)
	{
		//base case,当只有一个元素认为有序
		return a[l];
	}
	//随机数生成
	std::srand(std::time(nullptr));
	int ran = l + std::rand() % (r - l + 1);
	int x = a[ran];
	//进行分区划分
	partition(a, l,r , x);
	//根据要选择的元素进行判断
	//拷贝一份全局变量
	int left = first, right = last;
	if (idx >= first && idx <= last)
	{
		return x;
	}
	else if (idx < first)
	{
		return quickSortbasedrandomselect(a, n, l, left - 1, idx);
	}
	else {
		return quickSortbasedrandomselect(a, n, right + 1, r, idx);
	}
}