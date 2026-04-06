/*
给你一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。
找出只出现一次的那两个元素。你可以按 任意顺序 返回答案。
你必须设计并实现线性时间复杂度的算法且仅使用常量额外空间来解决此问题。
*/
//加强：找出出现奇数次的数字
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> ret;
        int n = nums.size();
        long long xor1 = 0, xor2 = 0;
        for (int i = 0; i < n; i++)
        {
            xor1 ^= nums[i];
        }
        //假设a，b是出现奇数次的数
        //xor1=a^b
        //a不等于b，证明a，b至少在一个二进制位上不相等
        //找到那个不相等的二进制位分为两类
        //只需要获取到xor1的最低位即可
        //注意：-xor1可能超过有符号整数
        //记得把xor1和xor2开long long！！！！！！
        //Brian Kernighan 算法，提取二进制位最右侧的1
        int tmp = (xor1 & (-xor1));
        for (int i = 0; i < n; i++)
        {
            if (nums[i] & tmp)
            {
                xor2 ^= nums[i];
            }
        }
        ret.push_back(xor2);
        ret.push_back(xor2^xor1);
        return ret;
    }
};

/*
假设数组 nums 中只出现一次的元素分别是 x1和x2​
如果把 nums 中的所有元素全部异或起来，得到结果 x，那么一定有：
x=x1⊕x2​
其中 ⊕ 表示异或运算。这是因为 nums 中出现两次的元素都会因为异或运算的性质 
a⊕b⊕b=a 抵消掉，那么最终的结果就只剩下 x1和 x2的异或和。
x 显然不会等于 0，因为如果 x=0，那么说明 x1=x2，这样 x1 和 x2
​ 就不是只出现一次的数字了。因此，我们可以使用位运算 x & -x
取出 x 的二进制表示中最低位那个 1，设其为第 l 位，那么 x1
​和x2中的某一个数的二进制表示的第 l 位为 0，
另一个数的二进制表示的第 l 位为 1。在这种情况下，x1⊕x2 的二进制表示的第 l 位才能为 1。
这样一来，我们就可以把 nums 中的所有元素分成两类，其中一类包含所有二进制表示的第 l 位为 0 的数，
另一类包含所有二进制表示的第 l 位为 1 的数。可以发现：
对于任意一个在数组 nums 中出现两次的元素，该元素的两次出现会被包含在同一类中；
对于任意一个在数组 nums 中只出现了一次的元素，即 x1和 x2 ，它们会被包含在不同类中。
因此，如果我们将每一类的元素全部异或起来，那么其中一类会得到 x1，另一类会得到 x2
这样我们就找出了这两个只出现一次的元素。

*/
//题解
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int xorsum = 0;
        for (int num : nums) {
            xorsum ^= num;
        }
        // 防止溢出
        int lsb = (xorsum == INT_MIN ? xorsum : xorsum & (-xorsum));
        int type1 = 0, type2 = 0;
        for (int num : nums) {
            if (num & lsb) {
                type1 ^= num;
            }
            else {
                type2 ^= num;
            }
        }
        return { type1, type2 };
    }
};
