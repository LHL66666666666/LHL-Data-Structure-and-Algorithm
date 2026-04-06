//插入排序基于哈希
//只能在数据范围较小时使用，小于10^6都可以
//计数器数组在初始化的时候可以使用memset
//如果数据含有负数，在哈希映射的时候加上一个偏移量，让其修正到索引范围内
void countingSort(int a[], int b[],int sizea,int maxvalue)
{
	//初始化
	for (int i = 0; i <= maxvalue; i++)
	{
		b[i] = 0;
	}
	for (int i = 0; i < sizea; i++)
	{
		b[a[i]]++;
	}
	int idx = 0;
	for (int j = 0; j <= maxvalue; j++)
	{
		for (int k = 0; k < b[j]; k++)
		{
			a[idx++] = j;
		}
	}

}