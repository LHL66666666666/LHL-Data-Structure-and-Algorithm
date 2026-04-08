#include <iostream>
#define eleType int
using namespace std;
int arr[10005];
int main()
{
	int n;
	while (cin >> n)
	{
		int ans = 1;
		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;
			arr[i] = x;

		}
		for (int i = 0; i < n; i++)
		{
			if (arr[i] % 2 == 1)
			{
				ans *= arr[i];
			}
		}
		cout << ans << endl;

	}


	return 0;
}
//给你n个整数，求他们中所有奇数的乘积。