#include <iostream>
#include <cstdlib>
#include <ctime>
//我们随机出来的数字在数组中一定存在，
//partition找到随机数应该的位置并进行划分
//<=x的数字放在左边，>x的数字放在右边，
//并且确保划分完成之后小于等于x的区域的最后一个元素是x
int partition(int a[], int l, int r, int x)
{
	int p1 = l, p2 = l;
	//p1标记小于等于x的区域的越界位置
	//p2进行遍历，遇到满足小于等于x的就交换
	int xi = l;
	//xi记录等于x的数的位置，最后交换到分界点上
	while (p2 <= r)
	{
		if (a[p2] <= x)
		{
			//交换
			int tmp = a[p1];
			a[p1] = a[p2];
			a[p2] = tmp;
			if (a[p1] == x)
			{
				xi = p1;
			}
			p1++;
			p2++;
		}
		else {
			p2++;
		}
	}
	int tmp = a[p1 - 1];
	a[p1 - 1] = a[xi];
	a[xi] = tmp;
	return p1 - 1;

}
void quickSort(int a[], int l, int r)
{
	if (l >= r)
	{
		//区间只有一个元素时
		return;
	}
	//随机数生成
	std::srand(std::time(nullptr));
	int ran = l + std::rand() % (r - l + 1);
	int x = a[ran];
	//进行分区。partition的作用是返回生成的随机位置的数字应该被放到的下标
	//也就是划分点，下面再在划分点的两侧进行递归调用即可
	int mid = partition(a, l, r, x);
	quickSort(a, l, mid-1);
	quickSort(a, mid + 1, r);
}



//优化：荷兰国旗问题，将每次等于划分点的数字都放在中间，
//小于的放在左侧，大于的放在右侧
//已知arr[l,r]范围上一定有x这个值
//划分数组<x在左侧，==x在中间,>x在右侧
//将全局变量first，last更新为==x区域的左右边界
int first,last;
//为什么这里用全局变量，
//因为要返回要改变的新区域的区间端点就是first-1,last+1
void partition2(int a[], int l, int r, int x)
{
	first = l;
	last = r;
	int p = l;
	while (p <= last)
	{
		if (a[p] < x)
		{
			//交换元素，将小于区域的边界右移
			int tmp = a[first];
			a[first] = a[p];
			a[p] = tmp;
			p++;
			first++;
		}
		else if (a[p] > x)
		{
			//交换元素，指针p不移动，继续处理刚交换过来的元素
			int tmp = a[last];
			a[last] = a[p];
			a[p] = tmp;
			last--;
		}
		else {
			p++;
		}
	}
}
void quickSort(int a[], int l, int r)
{
	if (l >= r)
	{
		//区间只有一个元素时
		return;
	}
	//随机数生成
	std::srand(std::time(nullptr));
	int ran = l + std::rand() % (r - l + 1);
	int x = a[ran];
	//进行分区。partition的作用是返回生成的随机位置的数字应该被放到的下标
	//也就是划分点，下面再在划分点的两侧进行递归调用即可
	partition2(a, l, r, x);
	int left = first;
	int right = last;
	//这里必须拷贝一份全局变量，防止更新全局变量时对递归调用产生影响
	quickSort(a, l, left - 1);
	quickSort(a, right + 1, r);
}
//为什么全局变量可行
/*
// 假设初始状态：first=3, last=4

// 步骤1：值拷贝
int left = first;   // left = 3 (拷贝数值)
int right = last;   // right = 4 (拷贝数值)

// 步骤2：第一次递归调用
quickSort(a, l, left - 1);  // 调用 quickSort(a, l, 2)

// 在递归调用中：
// - 可能会修改全局变量 first 和 last
// - 比如把 first 改成 1, last 改成 2

// 步骤3：第二次递归调用时
// 此时：first=1, last=2 (全局变量被修改了)
// 但是：left=3, right=4 (局部变量保持不变)
quickSort(a, right + 1, r);  // 调用 quickSort(a, 5, r) ✓
*/