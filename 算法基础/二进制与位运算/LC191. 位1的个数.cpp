//给定一个正整数 n，编写一个函数，
//获取一个正整数的二进制形式并返回其二进制表达式中 设置位 的个数（也被称为汉明重量）。
//方法一：循环检查二进制位
int hammingWeight(int n) {
	int count = 0;
	for (int i = 0; i < 32; i++)
	{
		if ((n >> i) & 1)
		{
			count++;
		}
	}
	return count;
}
//方法二：位运算优化(积累一下思路)
//算式n&(n-1),每一次把n二进制的最低位的1变成0,其余不变，循环此操作直到n变为0，每次操作将次数加一
int hammingWeight(int n) {
	int count = 0;
	while (n > 0)
	{
		count++;
		n = (n & (n - 1));
	}
	return count;
}