#include <iostream>
using namespace std;
#define ll long long
ll a[1005][1005];
ll ini[1005][1005];
void set(ll a[][1005], int x1, int y1, int x2, int y2,int k)
{
	a[x1][y1]+=k;
	a[x2 + 1][y2 + 1]+=k;
	a[x2 + 1][y1]-=k;
	a[x1][y2 + 1]-=k;
}
void build(ll a[][1005])
{
	for (int i = 1; i < 1005; i++)
	{
		for (int j = 1; j < 1005; j++)
		{
			a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + a[i][j];
		}
	}
}
int main() {
    int n, m, q;
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> ini[i][j];
		}
	}
	while (q--)
	{
		int x1, y1, x2, y2, k;
		cin >> x1 >> y1 >> x2 >> y2 >> k;
		set(a, x1, y1, x2, y2, k);
	}
	build(a);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cout << a[i][j] + ini[i][j] << ' ';
		
		}
		cout << endl;
	}

}
// 64 Î»Êä³öÇëÓÃ printf("%lld")