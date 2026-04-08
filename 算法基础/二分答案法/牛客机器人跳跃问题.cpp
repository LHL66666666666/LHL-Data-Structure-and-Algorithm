/*
机器人正在玩一个古老的基于DOS的游戏。游戏中有N+1座建筑——从0到N编号，从左到右排列。编号为0的建筑高度为0个单位，编号为i的建筑的高度为H(i)个单位。

起初， 机器人在编号为0的建筑处。每一步，它跳到下一个（右边）建筑。假设机器人在第k个建筑，且它现在的能量值是E, 下一步它将跳到第个k+1建筑。它将会得到或者失去正比于与H(k+1)与E之差的能量。如果 H(k+1) > E 那么机器人就失去 H(k+1) - E 的能量值，否则它将得到 E - H(k+1) 的能量值。

游戏目标是到达第个N建筑，在这个过程中，能量值不能为负数个单位。现在的问题是机器人以多少能量值开始游戏，才可以保证成功完成游戏？
输入描述：
第一行输入，表示一共有 N 组数据.

第二个是 N 个空格分隔的整数，H1, H2, H3, ..., Hn 代表建筑物的高度
输出描述：
输出一个单独的数表示完成游戏所需的最少单位的初始能量
示例1
*/
#include <iostream>
using namespace std;
int h[100005];
//int hd[100005];
int min(int a, int b)
{
    return a < b ? a : b;
}
int max(int c, int d)
{
    return c > d ? c : d;
}
bool check(int h[], int m,int n,int maxh)
{
    //注意：这里如果一直增加的话，增长速度可能是指数级
    for (int i = 1; i <= n; i++)
    {
        if (m >= h[i])
        {
            m += m - h[i];
        }
        else m -= h[i] - m;
        //为了防止溢出，我们查找数组中最大值，
        //只要m大于等于这个最大值，那么就必定可以通关
        if (m >= maxh)
        {
            return true;
        }
        if (m < 0)
        {
            return false;
        }
    }
    return true;
}
int main() {
    int n;
    while (cin >> n)
    {
        //要预先找到最大高度和0，答案一定在这两个数字之间
        //把初始值E也看做一个高度
        //单调性：
        int  maxh = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> h[i];
            maxh = max(maxh, h[i]);
        }
        //开始二分
        int l = 1, r = 1e5, ans = 1e5;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (check(h, mid, n,maxh))
            {
                ans = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        cout << ans << endl;
    }
}
// 64 位输出请用 printf("%lld")