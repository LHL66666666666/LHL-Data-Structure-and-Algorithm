#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;
int a[100005];
int b[100005];
int main()
{
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d",&a[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (a[i] == b[j] && a[j] == b[i])
			{
				cnt++;
			}
		}
	}
	cout << cnt << endl;
	//暴力算法TLE
	//要使用哈希表优化
	return 0;
}