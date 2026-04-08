//典型例子：给定一个长度为n的01数组，和一个整数k，
//求满足子数组和>=k的子数组的个数
int slideWindow(int n, int arr[], int k)
{
	int i = 0, j = -1, ans = 0, sum = 0;
	while (j < n - 1)
	{
		j++;
		sum += arr[j];
		while (sum >= k)
		{
			ans += n - j;
			sum -= arr[i];
			i++;
		}
	}
	return ans;
}