int min(int x, int y)
{
	return x < y ? x : y;
}
//归并排序模板(递归写法)
int a[100000];
int tmp[100000];
void merge(int a[], int l, int m, int r)
{
	//问题就变成了合并两个有序数组,一个从l到m，另一个从m+1到r
	for (int i = l; i <= r; i++)
	{
		tmp[i] = a[i];
	}
	int p1 = l, p2 = m + 1;
	int idx = l;
	while (p1 <= m && p2 <= r)
	{
		if (tmp[p1] <= tmp[p2])
		{
			a[idx++] = tmp[p1++];
		}
		else {
			a[idx++] = tmp[p2++];
		}
	}
	while (p1 <= m)
	{
		a[idx++] = tmp[p1++];
	}
	while (p2 <= r)
	{
		a[idx++] = tmp[p2++];
	}
}
void mergeSort(int a[], int l, int r)
{
	if (l >= r)
	{
		return;
	}
	int m = l + (r - l) / 2;
	mergeSort(a, l, m);
	mergeSort(a, m+1, r);
	// 如果已经有序，避免不必要的合并
	if (a[m] <= a[m + 1]) return;
	merge(a, l, m, r);
}



//归并排序模板(非递归写法)
//步长：1，2，4，8...
void mergeSort1(int a[],int n)
{
	//一共发生O(logn)次
	//跟据步长，每次先进行1v1,再2v2,再4v4，直到所有数据有序
	for (int step = 1; step < n; step <<= 1)
	{
		//内部分组merge，时间复杂度O(n)
		int l = 0;
		while (l < n)
		{
			int mid = l + step - 1;
			//注意这里mid一定不会越界
			//如果越界就被下面的mid>=n-1特判跳出循环了
			//有可能mid是数组的尾部，那么已经标志着排序完成，
			//右侧没有数字，此时需要特判
			if (mid + 1 >= n)
			{
				break;
			}
			//如果存在右侧，找右边界
			int r = min(n - 1, l + 2 * step - 1);
			//对mid左右两侧进行merge，因为已经有序
			merge(a, l, mid, r);
			//l需要继续移动找下一组的
			//l...m,m+1,...r
			//				 l...m,m+1,...r
			//								l...m,m+1,...r
			l = r + 1;
		}

	}
}