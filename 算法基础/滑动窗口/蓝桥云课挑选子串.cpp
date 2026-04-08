#include <iostream>
using namespace std;
int arr[2005];
int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	//用滑动窗口
	//记得考虑一下边界情况
	int i = 0, j = -1, ans = 0, cnt = 0;
	while (j < n - 1)
	{
		j++;
		if (arr[j] >= m)
		{
			cnt++;
		}
		while (cnt >= k)
		{
			ans += n - j;
			if (arr[i] >= m)
			{
				cnt--;
			}
			i++;
		}
	}
	cout << ans << endl;

	return 0;
}
//AC了，还有一种思路可以转化为前面的问题
//开一个新的数组，如果原数组的元素大于等于m，赋值为1
//小于m赋值为0
//下面查找新数组中 和大于等于k的子串即可
//也可以用前缀和，用前缀和枚举每一个子区间的和即可
