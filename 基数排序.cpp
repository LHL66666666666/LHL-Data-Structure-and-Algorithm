//不基于比较的排序：基数排序和桶排序
//基数排序所使用的两个技巧
//1.前缀分区，每次桶排时，计算每个元素出现次数，
//然后将数字从小到大求前缀和，从后向前遍历数组，
//按照前缀和的大小确定下标，这样保持原来数字相对次序不变，保证稳定性
//基数排序对数据范围有要求，必须全是非负数
 //参数n表示数组大小，bits表示数组arr中最大值在base进制下有几位
#include <string.h>
//base表示进制
const int base = 10;
int cnts[base];
int help[200005];
int arr[200005];
void radixSort(int arr[], int n, int bits)
{
	//循环一共进行bits轮，offset方便获取每一位的数字，
	//避免改变原数组中的数
	int offset = 1;
	for (; bits > 0; bits--)
	{
		memset(cnts, 0, sizeof(cnts));
		//一共最多十位数0到9
		//开一个数组用来存储，下标就代表对应数字，同时进行前缀分块
		for (int i = 0; i < n; i++)
		{
			int idx = (arr[i] / offset) % base;
			cnts[idx]++;
		}
		//前缀和处理
		for (int i = 1; i < base; i++)
		{
			cnts[i] += cnts[i - 1];
		}
		//倒序遍历数组，将桶中的元素倒出来
		for (int i = n - 1; i >= 0; i--)
		{
			int idx = (arr[i] / offset) % base;
			help[cnts[idx] - 1] = arr[i];  // 修正索引
			cnts[idx]--;  // 修正：使用idx而不是arr[i]
		}
		for (int i = 0; i < n; i++)
		{
			arr[i] = help[i];
		}
		offset *= base;
	}
}
//补充：有负数也可以做，只不过需要每个数字减去最小值，
//即加上最小值（负数）的绝对值