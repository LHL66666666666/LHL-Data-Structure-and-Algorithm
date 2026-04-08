class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int ans = 0;
        for (int i = 31; i >= 0; i--)
        {
            int l = (left >> i) & 1, r = (right >> i) & 1;
            if (l == r)
            {
                ans |= (l << i);
            }
            else break;
        }
        return ans;
        //自己的做法：从左向右检查，找公共前缀
    }
};
//对所有数字执行按位与运算的结果是所有对应二进制字符串的公共前缀
//再用零补上后面的剩余位
//那么这个规律是否正确呢？我们可以进行简单的证明。假设对于所有这些二进制串，前 i 位均相同，第 i + 1 位开始不同，由于[m, n] 连续，
//所以第 i + 1 位在[m, n] 的数字范围从小到大列举出来一定是前面全部是 0，后面全部是 1，
//在上图中对应[9, 11] 均为 0，[12, 12] 均为 1。并且一定存在连续的两个数 x 和 x + 1，满足 x 的第 i + 1 位为 0，
//后面全为 1，x + 1 的第 i + 1 位为 1，后面全为 0，对应上图中的例子即为 11 和 12。
//这种形如 0111… 和 1000… 的二进制串的按位与的结果一定为 0000…，因此第 i + 1 位开始的剩余位均为 0，前 i 位由于均相同，因此按位与结果不变。最后的答案即为二进制字符串的公共前缀再用零补上后面的剩余位。
//进一步来说，所有这些二进制字符串的公共前缀也即指定范围的起始和结束数字 m 和 n 的公共前缀（即在上面的示例中分别为 9 和 12）。

//因此，最终我们可以将问题重新表述为：给定两个整数，我们要找到它们对应的二进制字符串的公共前缀。
//优化1：移位
//将left和right逐次右移，直到m==n为止
//记录右移位数，再左移即可
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int shift = 0;
        // 找到公共前缀
        while (m < n) {
            m >>= 1;
            n >>= 1;
            ++shift;
        }
        return m << shift;
    }
};
//进一步优化
//Brian Kernighan 算法
//还有一个位移相关的算法叫做「Brian Kernighan 算法」，它用于清除二进制串中最右边的 1。
//Brian Kernighan 算法的关键在于我们每次对 number 和 number−1 之间进行按位与运算后，
//number 中最右边的 1 会被抹去变成 0。
//基于上述技巧，我们可以用它来计算两个二进制字符串的公共前缀。
//其思想是，对于给定的范围[m, n]（m < n），我们可以对数字 n 迭代地应用上述技巧，
//清除最右边的 1，直到它小于或等于 m，此时非公共前缀部分的 1 均被消去。
//因此最后我们返回 n 即可。
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        while (right > left)
        {
            right = (right & (right - 1));
        }
        return right;
    }
};