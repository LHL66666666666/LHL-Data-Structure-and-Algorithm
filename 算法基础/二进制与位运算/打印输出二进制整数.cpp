#include <iostream>
using namespace std;
//如何打印输出二进制数
void print_binary(int a)
{
	for (int i = 31; i >= 0; i--)
	{
		if (a & (1LL << i))
		{
			cout << 1;
			//这里1默认是整型
			//如果是long long 要写1LL
		}
		else cout << 0;
	}
}
int main()
{
	print_binary(20);
	return 0;
}