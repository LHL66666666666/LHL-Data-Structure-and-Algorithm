//数组中只有1种数出现次数少于m次，
//其他数都出现了m次，返回出现次数小于m次的那种数
int solve(int arr[],int size,int m)
{
	int a[32] = {0};
	int ans = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			a[j] += (arr[i] >> j) & 1;
		}
	}
	for (int i = 0; i < 32; i++)
	{
		if (a[i]%m!=0)
		{
			ans |= (1 << i);
		}
		
	}
	//出现m次的数，如果某一位上是1，对这一个位置的贡献是m
	//出现m次导致这一位上所有1加起来一定是m的倍数
	return ans;

}
//本题是LeetCode137加强版
/*
给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。
请你找出并返回那个只出现了一次的元素。
你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。
*/
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		int n = nums.size();
		int a[32] = { 0 };
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				a[j] += (nums[i] >> j) & 1;
			}
		}
		for (int j = 0; j < 32; j++)
		{
			if (a[j] % 3 != 0)
			{
				ans |= (1 << j);
			}
		}
		return ans;
	}
};
//这种算法时间复杂度为O(nlogC),C为常数，这里C=2^32
//logC=32
//目标是O(n)的复杂度
//灵茶山艾府的题解
//位运算的魔法：模 3 加法
//图片
//https://pic.leetcode.cn/1697077395-HGUOiR-lc137-c.png
/*
对于异或（模 2 加法）来说，把一个数不断地异或 1，相当于在 0 和 1 之间不断转换，即：

0→1→0→1→⋯
类似地，模 3 加法就是在 0,1,2 之间不断转换，即：

0→1→2→0→1→2→⋯
由于 0,1,2 需要两个比特才能表示，设这两个比特分别为 a 和 b，即：

a=0, b=0 表示数字 0；
a=0, b=1 表示数字 1；
a=1, b=0 表示数字 2。
那么转换规则就是：

(0,0)→(0,1)→(1,0)→(0,0)→(0,1)→(1,0)→⋯
这其中有大量 0 和 1 之间的转换，我们已经知道，这可以用异或运算实现，写成代码就是：
a = a ^ 1
b = b ^ 1

除了两个例外情况：

当 a=0 且 b=0 时，a 必须保持不变，仍然为 0。
当 a=1 时（此时 b 一定是 0），b 必须保持不变，仍然为 0。
换句话说，我们可以在异或运算的基础上，增加一些「约束」：

当 (a | b) == 0 时，把 0 赋值给 a，否则（(a | b) == 1）可以执行异或操作。写成代码就是 a = (a ^ 1) & (a | b)。
当 a == 1 时，把 0 赋值给 b，否则（~a == 1）可以执行异或操作。写成代码就是 b = (b ^ 1) & ~a。
其中 & 运算相当于为异或运算添加了一个约束：当……为 1 时，才执行异或操作。

如果模 3 加法遇到了 0，那么 a 和 b 都应当维持不变。好在把 1 改成 0，我们的代码仍然是正确的，也就是：
// 注意 a 和 b 是同时计算的
a = (a ^ x) & (a | b)
b = (b ^ x) & ~a
该代码在 x=0 和 x=1 的情况下都是成立的（注意 a 和 b 不可能都为 1）。

由于位运算具有「并行计算」的特点，上述运算规则可以推广到多个比特的情况。遍历 nums，利用上式计算出最终的 a 和 b。

最后，由于模 3 加法的结果要么是 0，要么是 1，没有 2，那么根据 b 的定义，这刚好就是 b，所以最后返回 b。

作者：灵茶山艾府
链接：https://leetcode.cn/problems/single-number-ii/solutions/2482832/dai-ni-yi-bu-bu-tui-dao-chu-wei-yun-suan-wnwy/
*/
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		int a = 0, b = 0;
		for (int x : nums) {
			int tmp_a = a;
			//tmp_a记录上一次的a防止改变之后影响结果
			//上面对于a，b的讨论是基于某一位的，但是由于位运算的并行计算特点，
			//也就是说可以一次算所有的位置，因此可以直接计算a，b的每一位
			//实际上这种算法将二进制地异或推广到三进制
			a = (a ^ x) & (a | b);
			b = (b ^ x) & ~tmp_a;
		}
		return b;
	}
};
//另一篇相似的题解
//https://leetcode.cn/problems/single-number-ii/solutions/1/single-number-ii-mo-ni-san-jin-zhi-fa-by-jin407891/?envType=problem-list-v2&envId=bit-manipulation
