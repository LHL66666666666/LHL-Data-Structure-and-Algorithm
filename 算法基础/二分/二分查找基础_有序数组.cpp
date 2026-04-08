//前提：首先是一个有序数组，才能使用二分查找
//这种方法命名为模板一
#include <iostream>
#include <cstdio>
//例一：查找数组中是否存在目标元素target
bool binsearch(int arr[], int target,int len)
{
	if (len == 0)
	{
		return false;
	}
	int l = 0, r = len - 1,mid=0;
	while (l <= r)
	{
		int mid = l + (r - l) / 2;  // 防止整数溢出
		//int mid = (l + r) / 2;最好不这么写，防止l.r很大的时候爆int
		if (arr[mid] == target)
		{
			return true;
		}
		else if (arr[mid] > target)
		{
			r = mid - 1;
		}
		else if (arr[mid] < target)
		{
			l = mid + 1;
		}
	}
	return false;
}
//例二：给定一个数字，查找有序数组中大于等于这个数字的最小数字
//有序数组中查找>=num的最左位置
int binserech2(int arr[], int target, int len)
{
	if (len == 0 || arr==NULL)
	{
		return -1;
	}
	int l = 0, r = len - 1, ans;
	if (target > arr[r])
	{
		return -1;
	}
	while (l <= r)
	{
		int mid = l + (r - l) / 2;
		if (arr[mid] >= target)
		{
			ans = mid;
			r = mid - 1;
		}
		else if (arr[mid] < target)
		{
			l = mid + 1;
		}

	}
	return ans;
}
//例三：查找有序数组中<=num的最左侧的位置
int binserech3(int arr[], int target, int len)
{
	if (len == 0 || arr == NULL)
	{
		return -1;
	}
	if (target < arr[0])
	{
		return -1;
	}
	int l = 0, r = len - 1, ans = -1;
	while (l <= r)
	{
		int mid = l + ((r - l) >> 1);
		if (arr[mid] > target)
		{
			r = mid - 1;
		} else {
			ans = mid;
			l = mid + 1;
		}
	}
	return ans;
}

//测试
int main() {
	int arr[] = { 1, 3, 3, 3, 5, 7, 9, 11 };
	int len = 8;

	printf("查找 <= 0: %d\n", binserech3(arr, 0, len));    // -1
	printf("查找 <= 3: %d\n", binserech3(arr, 3, len));    // 3 (最后一个3的位置)
	printf("查找 <= 4: %d\n", binserech3(arr, 4, len));    // 3 (最后一个<=4的位置)
	printf("查找 <= 11: %d\n", binserech3(arr, 11, len));  // 7
	printf("查找 <= 12: %d\n", binserech3(arr, 12, len));  // 7

	return 0;
}




//红绿灯标记法
//假设需要查找的元素为大于等于给定目标数字target的最小数字
//将比target小的元素标记为红色
//大于等于target的元素标记为绿色
//这种方法的模板
int isGreen(int arr[], int index,int target)
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
		if (isGreen(arr,mid,target))
		{
			r = mid;
		}
		else l = mid;
	}
	return r;
	
}