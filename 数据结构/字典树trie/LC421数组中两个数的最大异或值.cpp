/*
给你一个整数数组 nums ，
返回 nums[i] XOR nums[j] 的最大运算结果，其中 0 ≤ i ≤ j < n 。
*/
/*
示例 1：
输入：nums = [3,10,5,25,2,8]
输出：28
解释：最大运算结果是 5 XOR 25 = 28.

示例 2：
输入：nums = [14,70,53,83,49,91,36,80,92,51,66,70]
输出：127

提示：
1 <= nums.length <= 2 * 10^5
0 <= nums[i] <= 2^31 - 1
*/
//按位异或，也就是说我们希望两个数字的二进制字符串尽量不同，而且尽量在高位上不同
//所以我们需要找两个数字最大相异的前缀
//比如01110001
//希望10001110
//这样得到的结果最大
//找两个数字最大相异的前缀，可以取反找公共前缀
#include <vector>
#include <string>
#include <set>
//1.使用字典树的做法
class Solution {
public:
	int tree[3000005][2];
	int end[3000005];
	int pass[3000005];
	//cnt记录申请节点的编号
	int cnt;
	//high记录最高位是1的位置
	int high;
	//初始化
	void build(std::vector<int>& nums) {
		cnt = 1;
		//这里有一个优化，可以先找到一个最大值，从而就避免了将所有数字的前导0插入字典树
		//节约空间
		int max_num = INT_MIN;
		for (auto num : nums)
		{
			max_num = std::max(max_num, num);
		}
		for (int i = 31; i >= 0; i--)
		{
			if ((max_num >> i) & 1)
			{
				high = i + 1;
				break;
			}
		}
	}
	//增
	void insert(std::string s) {
		//从头节点开始，首先在头节点+1表示经过了头节点
		//cur表示当前的节点是哪个
		int cur = 1;
		pass[cur]++;
		for (int i = 0; i < s.size(); i++) {
			//path表示下一步的路径
			int path = s[i] - '0';
			if (tree[cur][path] == 0) {
				//分配新的内存编号
				tree[cur][path] = ++cnt;
			}
			//更新当前的节点
			cur = tree[cur][path];
			//经过下一个位置
			pass[cur]++;
		}
		//遍历完之后，将现在在的节点end值+1
		end[cur]++;
	}

	//清空数组，避免数据污染
	void clear() {
		for (int i = 1; i <= cnt; i++) {
			//因为我们最多用了cnt行
			memset(tree[i], 0, sizeof(tree[i]));
			end[i] = 0;
			pass[i] = 0;
		}
	}

	//计算最大的xor
	int maxXor(int num)
	{
		int cur = 1;
		int ans = 0;
		//我们拆二进制的每一位，希望找到相异的路，然后算这个位置对于答案的贡献
		for (int i = high - 1; i >= 0; i--)
		{
			int path = ((num >> i) & 1);
			//即如果该位是1，找0，如果该位是0，找1
			if (tree[cur][1 - path] != 0)
			{
				ans |= (1LL << i);
				cur = tree[cur][1 - path];
			}
			else cur = tree[cur][path];
		}
		return ans;
	}

    int findMaximumXOR(std::vector<int>& nums) {
		high = 0;
		build(nums);
		for (auto num : nums)
		{
			std::string s;
			//将数字转为二进制字符串
			//从high位开始
			for (int i = high - 1; i >= 0; i--)
			{
				int tmp = ((num >> i) & 1);
				s.push_back(tmp + '0');
			}
			insert(s);
		}
		//前缀树建完之后开始查询每一个
		//我们要查询的是相异的前缀
		int ans = 0;
		for (auto num : nums)
		{
			ans = std::max(ans,maxXor(num));
		}
		clear();
		return ans;
    }
};

//2.使用哈希表的做法
class Solution {
public:
	int high;
	int findMaximumXOR(std::vector<int>& nums) {
		high = 0;
		int max_num = INT_MIN;
		for (auto num : nums)
		{
			max_num = std::max(max_num, num);
		}
		for (int i = 31; i >= 0; i--)
		{
			if ((max_num >> i) & 1)
			{
				high = i;
				break;
			}
		}
		int ans = 0;
		//讨论每一位能否达成1
		std::set<int> a;
		//接下来讨论的位置移位从high-1开始
		for (int i = high; i >= 0; i--)
		{
			//每次讨论时，已经实现的ans是31位到i+1位置的目标，不管是达成了1还是未达成1而保持0
			int better = (ans | (1LL << i));	//期望达成的目标
			a.clear();
			//期望找到better
			//也就是说x^x'=better,对于想要的x'我们要查询的就是better^x
			for (auto num : nums)
			{
				//保留31位到i位置的二进制位，其余低位变成0
				num = ((num >> i) << i);
				a.insert(num);
				if (a.count(num ^ better) > 0)
				{
					ans = better;
					break;
				}
			}
		}
		return ans;
	}
};
/*
哈希set解法不容易想通的是，虽然不同位上能异或得到的better的数在数组中很有可能不是同一个，
但是位for循环后面的位找到的符合条件的数至少必须保证它的前面所有位的0，1情况
是与已经得到的ans的异或结果是一致的(低位的better包含了之前所有位的ans信息)，
然后再去判断这个位上是不是也能符合better的要求。
也就是说这个算法实际上是通过逐位确认ans上的理想状态，
按位不断缩小答案在数组上的搜索范围(应该也不能说缩小，搜不到的话ans就不更新了)
首先贪心越高位上是1的答案就越优
根据要求每一个符合条件的数字的前缀必须等于better，不断缩小搜索范围，就确定了一个唯一的数字
*/