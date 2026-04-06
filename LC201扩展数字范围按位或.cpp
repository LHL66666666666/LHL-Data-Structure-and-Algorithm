//H
//给定两个数l,r,求区间[l,r]上各个数字的按位或
#include <stdio.h>
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int l, r, ans;
        scanf("%d %d", &l, &r);
        //本题再求连续区间l到r的所有数的位或
        //不能暴力枚举
        //实际上本题与求区间内所有数字的按位与是一样的
        //先找两个二进制字符串的最大公共前缀，然后后面全部补1
        //结论是显然的
        //证明：在最大公共前缀后面，假设到第i位都是公共序列，
        //第i+1位既然是非公共，那么一定有0有1，既然有1，那么第i+1位到最后一位最少是10000..
        //那么10000...必定由01111...+1变来，因此后面按位或一定全得到1
        //l,r在int内
        //先假定有公共前缀
        int cnt = 0;
        while (r != l) {
            r >>= 1;
            l >>= 1;
            cnt++;
        }
        int mask = 0;
        for (int i = 0; i < cnt; i++) {
            mask |= (1 << i);
        }
        l <<= cnt;
        ans = (l | mask);
        printf("%d\n", ans);
    }
    return 0;
}
//使用了一种更可靠的方法：计算l和r的异或，
//然后生成一个掩码，将最高不同位之后的低位全部置1，最后将r与该掩码按位或
//这样的思路本质上也是找公共前缀
#include <stdio.h>
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int l, r;
        scanf("%d %d", &l, &r);
        // 将l和r转换为无符号整数以避免移位问题
        unsigned int ul = l, ur = r;
        // 计算l和r的异或，找到不同的位
        unsigned int diff = ul ^ ur;
        // 生成掩码，将最高不同位之后的低位全部置1
        unsigned int mask = 0;
        while (diff) {
            mask = (mask << 1) | 1;
            diff >>= 1;
        }
        // 计算按位或结果
        unsigned int uans = ur | mask;
        // 将结果转换回有符号整数（位模式不变）
        int ans = uans;
        printf("%d\n", ans);
    }
    return 0;
}
//另一种算法：
//提供一种算法：每次将一个数字的二进制表示的最低位的0转为1
//t=t|(t+1)
//可以验证，这样将二进制最低位的0转为1
//我们和数字范围按位与一样，转换直到公共前缀为止
//code
int or_sum(int l, int r)
{
    while (r > l)
    {
        l |= (l + 1);
    }
    return l;
}