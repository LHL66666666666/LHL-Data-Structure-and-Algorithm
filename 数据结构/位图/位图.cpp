/*
位图原理
其实就是用bit组成的数组来存放值，用bit状态1、0代表存在、不存在，取值和存值操作都用位运算
限制是必须为连续范围且不能过大。好处是极大的节省空间，因为1个数字只占用1个bit的空间。

位图的实现
Bitset(int n)：初始化位图的大小，只支持0~n-1所有数字的增删改查
void add(int num)：把num加入到位图
void remove(int num)：把num从位图中删除
void reverse(int num)：如果位图里没有num，就加入；如果位图里有num，就删除
boolean contains(int num)：查询num是否在位图中

*/
#include <iostream>
//位图的实现
const int N = 2000005;
int bitset[N];
const int mask = 0xffffffff;
//每一个int占8个字节，有32个二进制位，我们需要假设表示x个数字
//表示0到n-1这些数字
//我们需要x/32向上取整个整数来表示

//加入元素
void add(int num)
{
	//num的位置在num/32索引的数字上
	int idx = num / 32;
	//在idx位置的数字的第num%32的二进制位上
	int bit_idx = num % 32;
	//加入这个数字
	bitset[idx] |= (1 << bit_idx);
}

//删除元素
void remove(int num)
{
	//num的位置在num/32索引的数字上
	int idx = num / 32;
	//在idx位置的数字的第num%32的二进制位上
	int bit_idx = num % 32;
	//删除这个数字
	//创建一个掩码方便计算
	int mask1 = mask ^ (1 << bit_idx);
	bitset[idx] &= mask1;
	//还有另一种写法,取反也可以
	//bitset[idx]&=(~(1<<bit_idx))
}

//改变某一位的状态
//将这一位的状态反转
void reverse(int num)
{
	//num的位置在num/32索引的数字上
	int idx = num / 32;
	//在idx位置的数字的第num%32的二进制位上
	int bit_idx = num % 32;
	//反转
	bitset[idx] ^= (1 << bit_idx);
}

//查询num在位图中是否存在
bool contains(int num)
{
	//num的位置在num/32索引的数字上
	int idx = num / 32;
	//在idx位置的数字的第num%32的二进制位上
	int bit_idx = num % 32;
	//类似于查询二进制位的某一位是否为1
	return (bitset[idx] >> bit_idx) & 1;
}
int main()
{
	int x;
	std::cin >> x;
	int n = (x + 31) / 32;
}