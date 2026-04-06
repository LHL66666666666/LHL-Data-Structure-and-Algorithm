/*
如图，九连环由一个架子和九个环组成，可以进行如下操作：

第一个环可以从架上取下或放到架上；
第 k (k>1) 个环可以被取下（放上），如果第 k−1 个环是它前面唯一一个在架上的环。

那么对于环数更少或更多的 n 连环，游戏方式是类似的。「Zeratul」想知道，最快将一个所有环都在架上的 n 连环拆下来需要怎么做，请你帮帮他。

为了帮助没有玩过九连环的同学们理解这道题，现将此题用数学语言重新翻译（二进制表示的最低位称为第 0 位，次低位称为第 1 位，以此类推）：

输入一个正整数 n，你将获得一个所有位全是 1 的 n 位二进制数 status，你可以对其进行如下操作之一：

将 status 二进制表示的最低位取反；
将 status 二进制表示的第 k (k>0) 位翻转，如果 status 的二进制表示的最后一个 1 在第 k−1 位。

现在请你求出使用最少次操作将 status 的值变为 0 的方法。

输入格式
一个正整数 n (1≤n≤15)，表示环数。

输出格式
共 p 行，其中 p 为最小步数。

每行一个自然数 status，表示执行完这一步操作后连环的状态（即 status 的十进制值）。status 的 n 位二进制表示中，对于每一位而言，1 表示该环在架上，0 表示该环在架下。

显然，最后一个自然数应该是 0。

输入样例
3
输出样例
6
2
3
1
0

样例解释
第一步，将第 1 个环取下，status = (110)₂ = 6；
第二步，将第 3 个环取下，status = (010)₂ = 2；
第三步，将第 1 个环放上，status = (011)₂ = 3；
第四步，将第 2 个环取下，status = (001)₂ = 1；
第五步，将第 1 个环取下，status = (000)₂ = 0。

Hint
显然，将一个被拆下来的连环全部放上架子的操作和将其从架子上取下的操作是反向的。

想要取下 n 连环，可以先取下 n−2 连环，再取下第 n 个环，再放上 n−2 连环，再取下 n−1 连环。可以证明，这是最快的方法。
*/
#include <stdio.h>
int status;
int steps[1 << 15];  // 最大步数不会超过2^n
int step_count = 0;
//反转第k位
void toggle(int k) {
    status ^= (1 << k);
    steps[step_count++] = status;
}
void remove_rings(int m);
//install是安装环
void install(int m) {
    if (m == 1) {
        toggle(0);
    }
    else if (m > 1) {
        install(m - 1);
        remove_rings(m - 2);
        toggle(m - 1);
        install(m - 2);
    }
}
//remove是卸下环
void remove_rings(int m) {
    if (m == 1) {
        toggle(0);
    }
    else if (m > 1) {
        remove_rings(m - 2);
        toggle(m - 1);
        install(m - 2);
        remove_rings(m - 1);
    }
}
//install和remove是相反过程
int main() {
    int n;
    scanf("%d", &n);

    status = (1 << n) - 1;  // 初始全1
    steps[step_count++] = status;  // 记录初始状态
    remove_rings(n);
    //输出
    for (int i = 1; i < step_count; i++) {
        printf("%d\n", steps[i]);
    }

    return 0;
}