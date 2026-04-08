//堆结构的实现
//i位置的数字，向上调整大根堆
//arr[i]=x,x是新加入的元素，一直向上看父节点的值，
//直到不比父亲大，或者来到顶部
void heapInsert(int arr[], int i)
{
	//i->父节点：(i-1)/2
	while (arr[i] > arr[(i - 1) / 2])
	{
		//交换
		int tmp = arr[i];
		arr[i] = arr[(i - 1) / 2];
		arr[(i - 1) / 2] = tmp;
		//变为父节点的位置
		i = (i - 1) / 2;
	}
}

//i位置的数字改变（变小），向下调整大根堆
//当前堆的大小为size,下标范围是[0,size-1]
void heapify(int arr[], int i, int size)
{
	int l = i * 2 + 1;
	while (l < size)
	{
		//有左孩子
		//右孩子l+1
		int best;
		//选出左右孩子值更大的一个
		if (l + 1 < size && arr[l + 1] > arr[l])
		{
			//如果有右孩子且右孩子较大
			best = l + 1;
		}
		else best = l;
		//下面比较当前的数字和左右孩子最大数哪个更大
		if (arr[best] < arr[i])
		{
			best = i;
		}
		if (best == i)
		{
			//也就是说左右孩子都比这个数字小
			break;
		}
		else {
			int tmp = arr[i];
			arr[i] = arr[best];
			arr[best] = tmp;
			i = best;
			l = i * 2 + 1;
		}
	}
}
//经典堆排序
//从顶到底建立大根堆
//整体时间复杂度O(nlogn)
void heapSort(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		heapInsert(arr, i);
	}
	int size = n;
	while (size > 1)
	{
		//交换，将堆顶的数字换到数组末尾，同时size-1
		int tmp = arr[0];
		arr[0] = arr[size - 1];
		arr[size - 1] = tmp;
		size--;
		heapify(arr, 0, size);
	}
}

//优化建堆过程
//核心思想：自底向上建堆
//优化后的堆排序
void heapSort2(int arr[], int n) {
	// 更高效的建堆方式：从最后一个非叶子节点开始向下调整
	// 每一次调整的时候它的子树都是一个大根堆，因此从底部到顶部建堆是可行的
	// 有种递归的思想
	// 换一种理解方法，每次「合并」两个已经调整好的堆，这说明了正确性
	// 注意到向下调整的复杂度，为 𝑂(log⁡𝑛 −𝑘)
	// O(log n - k)，另外注意到叶节点无需调整，
	// 因此可从序列约 n / 2 的位置开始调整，
	// 可减少部分常数但不影响复杂度
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(arr, i, n);
	}

	int size = n;
	while (size > 1) {
		// 交换堆顶和末尾元素
		int tmp = arr[0];
		arr[0] = arr[size - 1];
		arr[size - 1] = tmp;
		size--;
		heapify(arr, 0, size);
	}
}
//额外空间复杂度O(1)