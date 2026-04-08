/*
现有2N 个红色木棍和N 个蓝色木棍。
红色木棍的集合由一个长度为
N 的正整数序列A 表示，序列中每存在一个
Ai表示有2 个长度为Ai​的红色木棍；
蓝色木棍的集合由一个长度为
N 的正整数序列B表示，序列中每存在一个
Bi表示有1 个长度为Bi​的蓝色木棍；
现在要求用
3 个木棍组成一个等腰三角形，
每个三角形中要包含2 个红色木棍以及
1 个蓝色木棍，并且要求
2 个红色木棍的长度相等。
求最多可以组成多少个这样的三角形。
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[200005];
int b[200005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]);
    }
    //可能要用到分离双指针
    //构成三角形的条件，记红色长度为a，蓝色为b
    //只需要满足2a>b即可
    //贪心一下
    //想要组成的等腰三角形最多，需要小的a尽量和小的b组合，a越大，能组合的b就越多
    //先排序
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    int p1 = 1, p2 = 1,count = 0;
    while (p1 <= n && p2 <= n)
    {
        if (a[p1] * 2 > b[p2])
        {
            count++;
            p1++;
            p2++;
        }
        else if (a[p1] * 2 <= b[p2])
        {
            p1++;
        }
    }
    cout << count << endl;

    return 0;
}