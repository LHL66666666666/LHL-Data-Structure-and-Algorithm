#include <vector>
using namespace std;
using ll = long long;
class Solution {
public:
    ll fac(int n)
    {
        ll ans = 1;
        for (int i = 1; i <= n; i++) ans *= 1LL * i;
        return ans;
    }
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) return 1;
        if (n == 1) return 10;
        ll ans = 10;
        //注意0不能作为开头位置
        //这是用组合数计算的方式
        for (int i = 2; i <= n; i++)
        {
            ll tmp = 1LL * fac(10) / fac(10 - i) - 1LL * fac(9) / fac(10 - i);
            ans += tmp;
        }
        return ans;
    }
};

class Solution {
public:
    ll fac(int n)
    {
        ll ans = 1;
        for (int i = 1; i <= n; i++) ans *= 1LL * i;
        return ans;
    }
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) return 1;
        if (n == 1) return 10;
        ll ans = 10;
        //注意0不能作为开头位置
        //考虑2位数及以上，第一位只能是1-9，9种选择
        //第二位只需要与第一位不同，0-9中选择，9种选择
        //第三位要与前面两位不同，8种选择
        //以此类推
        ll tmp = 9;
        for (int i = 2; i <= n; i++)
        {
            tmp *= (9 - i + 2);
            ans += tmp;
        }
        return ans;
    }
};