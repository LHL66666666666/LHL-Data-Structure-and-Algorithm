//一棵完全二叉树
//每个非叶子节点都有左右孩子
//用数组模拟完全二叉树时，下标关系：
//父节点的下标：(i-1)/2
//左孩子的下标：i*2+1
//右孩子的下标：i*2+2
//如果计算出的下标超过size，那么表示这个节点不存在
//堆结构
//完全二叉树和数组前缀范围来对应，大小，单独的变量size来控制
//i的父亲节点：(i - 1) / 2，i的左孩子：i * 2 + 1，i的右孩子：i * 2 + 2
//堆的定义（大根堆、小根堆），本节课讲解按照大根堆来讲解，小根堆是同理的。
//堆的调整：heapInsert（向上调整）、heapify（向下调整）
//heapInsert、heapify方法的单次调用，时间复杂度O(log n)，完全二叉树的结构决定的


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