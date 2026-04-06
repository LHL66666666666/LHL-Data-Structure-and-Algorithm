//两个整数之间的 汉明距离 指的是这两个数字对应二进制位不同的位置的数目
//给你两个整数 x 和 y，计算并返回它们之间的汉明距离。
int hammingDistance(int x, int y) {
	int ret = x ^ y;
	//异或运算，得到的ret二进制位上是1的即为两数不同位置的记录
	int ans = 0;
	while (ret)
	{
		ret &= (ret - 1);
		//每次消除二进制上最低位的1
		ans++;
	}
	return ans;
}
//Brian Kernighan 算法
//这个算法的意思是，对任何一个数 n，n&(n−1)的结果是
//n的比特位最右端的1变为0的结果。
//我们可以使用 Brian Kernighan 算法进行优化，具体地，该算法可以被描述为这样一个结论：
//记 f(x) 表示 x 和 x−1 进行与运算所得的结果（即 f(x)=x & (x−1)），
//那么 f(x) 恰为 x 删去其二进制表示中最右侧的 1 的结果。
//基于该算法，当我们计算出 s = x⊕y，只需要不断让 s = f(s)，直到 s = 0 即可。/
//这样每循环一次，s 都会删去其二进制表示中最右侧的 1，最终循环的次数即为 s 的二进制表示中 1 的数量。


//进一步优化：分治的思想
//左程云的思路  详见  算法讲解031【必备】位运算的骚操作
class Solution {
public:
	int hammingDistance(int x, int y) {
		int ret = x ^ y;
		ret = (ret & 0x55555555) + ((ret >> 1) & 0x55555555);
		ret = (ret & 0x33333333) + ((ret >> 2) & 0x33333333);
		ret = (ret & 0x0f0f0f0f) + ((ret >> 4) & 0x0f0f0f0f);
		ret = (ret & 0x00ff00ff) + ((ret >> 8) & 0x00ff00ff);
		ret = (ret & 0x0000ffff) + ((ret >> 16) & 0x0000ffff);
		return ret;
	}
};
