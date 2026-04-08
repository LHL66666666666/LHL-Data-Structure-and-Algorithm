//求a的b次幂最后三位数表示的整数
//其中(1<=a,b<=10000)
#include <iostream>
using namespace std;
int main()
{
	int a, b;
	cin >> a >> b;
	int ans = 1;
	for (int i=0;i<b;i++)
	{
		ans = (ans * a) % 1000;
	}
	cout << ans << endl;
	return 0;
}
//方案2：快速幂算法（更高效）
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    int ans = 1;
    int base = a % 1000;

    while (b > 0) {
        if (b % 2 == 1) {
            ans = (ans * base) % 1000;
        }
        base = (base * base) % 1000;
        b /= 2;
    }

    cout << ans << endl;
    return 0;
}