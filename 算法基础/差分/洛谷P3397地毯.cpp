/*
在 n×n 的格子上有 m 个地毯。

给出这些地毯的信息，问每个点被多少个地毯覆盖。

输入格式
第一行，两个正整数 n,m。意义如题所述。

接下来 m 行，每行两个坐标 (x1​,y1​) 和 (x2​,y2​)，代表一块地毯，
左上角是 (x1​,y1 )，右下角是 (x2​,y2​)。

输出格式
输出 n 行，每行 n 个正整数。

第 i 行第 j 列的正整数表示 (i,j) 这个格子被多少个地毯覆盖。
*/
#include <iostream>
using namespace std;
int a[1002][1002];
void set(int a[][1002], int x1, int y1, int x2, int y2)
{
	a[x1][y1] ++;
	a[x2 + 1][y2 + 1] ++;
	a[x2 + 1][y1]--;
	a[x1][y2 + 1]--;
}
void build(int a[][1002])
{
	for (int i = 1; i < 1002; i++)
	{
		for (int j = 1; j < 1002; j++)
		{
			a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + a[i][j];
		}
	}
}
int main()
{
	int n, m;
	cin >> n >> m;
	while (m--)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		set(a, x1, y1, x2, y2);
	}
	build(a);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}