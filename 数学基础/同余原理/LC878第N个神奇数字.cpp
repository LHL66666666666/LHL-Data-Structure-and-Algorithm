/*
一个正整数如果能被 a 或 b 整除，那么它是神奇的。
给定三个整数 n , a , b ，返回第 n 个神奇的数字。因为答案可能很大，
所以返回答案 对 109 + 7 取模 后的值。
*/
//答案范围可估计
//[1,n*min(a,b)]
//具有单调性，一个数字越小，那么他前面的神奇数字就越少
//我们找到一个满足条件的神奇数字
#include <algorithm>
class Solution {
public:
    const int N = 1e9 + 7;
    int gcd(int a, int b)
    {
        while (b)
        {
            int tmp = a % b;
            a = b;
            b = tmp;
        }
        return a;
    }
    long long lcm(int a, int b)
    {
        return (long long)a * b / gcd(a, b);
    }
    bool check(long long tar,int n,int a,int b)
    {
        //如果这个数字以及前面的数字的神奇数字数量大于等于n
        //返回1
        if (tar / a + tar / b - tar / lcm(a, b) >= n)
        {
            return true;
        }
        return false;
    }
    int nthMagicalNumber(int n, int a, int b) {
        //我们用二分答案
        long long tmp = std::min((long long)a * n, (long long)b * n);
        long long l = 1, r = tmp;
        long long ans = -1;
        while (l <= r)
        {
            long long mid = l + (r - l) / 2;
            if (check(mid, n, a, b))
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return ans % N;
    }
};