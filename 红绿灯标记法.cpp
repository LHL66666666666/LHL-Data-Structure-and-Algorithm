//红绿灯标记法
//命名为模板二
//假设需要查找的元素为大于等于给定目标数字target的最小数字
//将比target小的元素标记为红色
//大于等于target的元素标记为绿色
//这种方法的模板
int isGreen(int arr[], int index, int target)
{
	return arr[index] >= target;
}
int findMinDreenIndex(int arr[], int len, int target)
{
	int l = -1, r = len;
	//因为红色区域和绿色区域是不会重合的，所以结束条件是区间长度为2
	//也就是说,r-l=1

	while (l + 1 < r)
	{
		int mid = (l + r) / 2;
		if (isGreen(arr, mid, target))
		{
			r = mid;
		}
		else l = mid;
	}
	return r;

}