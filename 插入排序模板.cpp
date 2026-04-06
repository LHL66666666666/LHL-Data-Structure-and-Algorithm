//插入排序的模板(标准)
void insertionSort(int a[], int size)
{
	//这里size代表数组a的长度
	for (int i = 1; i < size; i++)
	{
		int tmp = a[i];
		//记住这里必须用一个临时变量来记录a[i]，否则会因为后面的操作而被覆盖掉
		//导致出错
		int j = i - 1;
		while (j >= 0 && tmp<a[j])
		{
			//只有tmp>a[j]时才将a[j]向后移动
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = tmp;
	}
}