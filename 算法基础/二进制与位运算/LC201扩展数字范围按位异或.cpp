//计算区间 [l, r] 上所有数字的按位异或有一个O(1)的数学方法，不需要循环。
//对于 xor [1, n]，有简洁的公式：
//xor[1,n]=n (n mod 4 = 0)
//xor[1,n]=1 (n mod 4 = 1)
//xor[1,n]=n+1 (n mod 4 = 2)
//xor[1,n]=0 (n mod 4 = 3)
//然后我们利用异或的前缀和性质进行运算即可
//xor[l,r]=xor[1,r] ⊕ xor[1,l-1]
//与其说计算[1,n],我们不如计算[0,n]区间的异或，这样更容易管理k的取值，同时加入0对本身没什么影响

int xor_0_to_n(int n) {
    // F(n) 的规律: [n, 1, n+1, 0] 循环
    int results[] = { n, 1, n + 1, 0 };
    return results[n % 4];
}

int range_xor(int l, int r) {
    return xor_0_to_n(r) ^ xor_0_to_n(l - 1);
}