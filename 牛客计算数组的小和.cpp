#include <iostream>
using namespace std;
int a[100005];
int tmp[100005];
typedef long long ll;
ll merge(int a[], int l, int m, int r);
//smallSum返回的是从l到r范围上的小和的累加和，同时排序
ll smallSum(int a[], int l, int r)
{
	if (l >= r)
	{
		return 0;
	}
	int m = l + (r - l) / 2;
	return smallSum(a, l, m) + smallSum(a, m + 1, r) + merge(a, l, m, r);
	//merge返回跨左右产生的小和，同时合并（归并排序的过程）
	//当这个范围上只有两个元素的时候，merge就统计了这个范围(两个数字)上的小和
}
ll merge(int a[], int l, int m, int r)
{
	//统计
	//因为我们已经排好了顺序，到merge这里只需要计算左跨右的小和的累加和即可
	//可以二分查找，也可以双指针扫一遍
	ll ans = 0;
	int pl = l;
	ll sum = 0;
	for (int j = m + 1; j <= r; j++)
	{
		while (pl <= m && a[pl] <= a[j])
		{
			sum += a[pl++];
		}
		ans += sum;
	}
	//还要完成merge
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
	return ans;
}
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	cout << smallSum(a, 1, n);
	
}
// 64 位输出请用 printf("%lld")