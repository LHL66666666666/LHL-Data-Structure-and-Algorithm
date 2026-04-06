//给定n个数形成的一个序列a，
//现定义如果一个连续子序列包含序列
//a 中所有不同元素，则该连续子序列便为蓝桥序列，
//现在问你，该蓝桥序列长度最短为多少？
//例如 1 2 2 2 3 2 2 1，包含
//3 个不同的数
//1, 2, 3，而 3 2 2 1 符合题目要求，因此答案为4
//第一行输入一个整数 n，表示序列长度。
//第二行输入n个元素。
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int arr[100005];
int h[1005];
int ans[1005];
bool check(int h[],int ans[])
{
	for (int i = 1; i <= 1000; i++)
	{
		if (ans[i]==0 && h[i]!=0)
		{
			return false;
		}
	}
	return true;
}
int min(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d",&arr[i]);
			h[arr[i]]++;
			//h是一个哈希表，存储1-1000的数字
	}
	//数据保证arr[i]在1-1000
	//用哈希表存储
	//使用滑动窗口枚举子数组
	int i = 0, j = 0, ret = n;
	while (j < n)
	{
		ans[arr[j]]++;
		while (check(h, ans))
		{
			ret = min(ret, j - i + 1);
			ans[arr[i]]--;
			i++;
		}
		j++;
	}
	cout << ret << endl;
	return 0;
}
//还可以进一步优化，
//我的方法每次检查窗口中元素个数时都要遍历一遍，时间开销大
//实际上只需要根据哈希表更新数组中不同元素的总个数，
//将整个数组的总个数与滑动窗口的总个数比较，相等即为合法子数组
#include <iostream>
#include <cstring>
using namespace std;

// 滑动窗口函数 参数 n 为序列元素个数
int slideWindow(int n, int* a) {
    // 滑动窗口的两个边界
    int i = 0, j = -1;
    // 哈希表 存储滑动窗口元素出现的次数
    int count[1001] = { 0 };
    // need 整个序列不同元素的个数;     tot 滑动窗口中的不同元素的个数
    int need = 0, tot = 0;
    // ret 初始化为 n 
    int ret = n;

    // 遍历计算整个序列不同元素的个数
    for (int i = 0; i < n; ++i) {
        // 自增 a[i] 的元素个数之后 检查是否为 1 ，即检查是否为新元素，若是则增加整个序列不同元素的个数
        if (++count[a[i]] == 1) {
            need++;
        }
    }

    // 重新初始化哈希表
    memset(count, 0, sizeof(count));
    // 滑动窗口
    while (j++ < n - 1) {
        // 自增 a[j] 的个数之后 检查是否为 1 ，即检查是否为新元素，若是则增加窗口中不同元素的个数
        if (++count[a[j]] == 1) {
            tot++;
        }
        // 当 窗口不同元素个数 = 整个序列不同元素的个数 
        while (tot == need) {
            // [i, j] 这个子序列是蓝桥序列
            ret = min(ret, j - i + 1);
            // 向前缩小窗口的范围，自减 a[i] 的元素个数之后 检查是否为 0，即检查是否失去新元素
            if (--count[a[i]] == 0) {
                tot--;
            }
            i++;
        }
    }
    return ret;
}
/*
滑动窗口    哈希表

求得蓝桥序列长度最短值 minLen

每次遇到一个新的数 计数加一

    1 2 2 2 3 2 2 1

idx 0 1 2 3 4 5 6 7

通过一开始输入的时候得知这个序列总共有多少个数字

i  j        a[i]  a[j]    元素个数计数
0  -1         1   NULL          1
0  0          1     2     new   2
0  1          1     2           2
0  2          1     2           2
0  3          1     2           2
0  4          1     3     new   3       符合条件 更新值 minLen = j - i + 1      满足条件 i 往前缩小窗口
1  4          2     3     div1  2       更新滑动窗口(子序列) 使得 1 的个数变为了 0  不满足条件 i 要停
...
2  7          2     1     new   3       符合条件 判断是否更新值 minLen
3  7          2     1           3       符合条件 判断是否更新值 minLen
4  7          3     1           3       符合条件 判断是否更新值 minLen
5  7          2     1     div3  2       更新滑动窗口(子序列) 使得 1 的个数变为了 0  不满足条件 i 要停
此时 j 已经到了尽头，所以此时的 minLen 就是正确答案
*/