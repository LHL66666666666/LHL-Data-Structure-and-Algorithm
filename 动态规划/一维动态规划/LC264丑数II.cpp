#include <vector>
using namespace std;
class Solution {
public:
    long long dp[1700];
    int nthUglyNumber(int n) {
        //最优解：三指针法
        dp[1] = 1;
        //创建三个指针，分别指向*2,*3,*5
        //由于丑数的因数都是2,3,5，后一个丑数一定由前一个转移来，我们选择最小的那个填入dp表
        int p2 = 1, p3 = 1, p5 = 1;
        for (int i = 2; i <= n; i++)
        {
            int a = dp[p2] * 2;
            int b = dp[p3] * 3;
            int c = dp[p5] * 5;
            int cur = min(min(a, b), c);
            if (cur == a) p2++;
            if (cur == b) p3++;
            if (cur == c) p5++;
            dp[i] = cur;
        }
        return dp[n];
    }
};
//分析的关键点：
//当前位置的丑数依赖于之前最小的那个丑数，所以用了依赖位置的转移方程