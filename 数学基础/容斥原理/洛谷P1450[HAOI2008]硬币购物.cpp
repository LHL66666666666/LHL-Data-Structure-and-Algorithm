#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr ll MOD = 998244353;
// constexpr ll MOD=1e9+7;
array<int, 5> c;
array<int, 5> d;
int n;
int s;
int dig(int x) {
    int res = 0;
    while (x) {
        x &= (x - 1);
        ++res;
    }
    return res;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 1; i <= 4; i++) cin >> c[i];
    cin >> n;
    //二进制分组跑多重背包是不对的
    //如果某种硬币的数量在二进制拆分后，产生多个面值相同的组
    //计数的时候就会重复，因为这些面值相同的组实际上是一种情况
    //修正思路
    //先预处理出来dp[i]表示每种硬币数量无限，价值总和为i的方案数
    //就是一个完全背包问题
    vector<ll> dp(100005);
    dp[0] = 1;
    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j <= 100000; j++) {
            if (j - c[i] >= 0) dp[j] += dp[j - c[i]];
        }
    }
    //有了这张表，我们可以查询在总和为s下，
    //对于一个x价值的硬币，限制cnt个数量，违规的方法数
    //违规方法数即为dp[s-x*(cnt+1)]
    //如何理解：dp[s-x*(cnt+1)]表示s-x*(cnt+1)价值中，x取任意数量(从0开始到可能很大)的方法数
    //然后加上cnt+1个x(这一步只有一种方法数)，相乘即为dp[s-x*(cnt+1)]
    //计算时，dp[s]-[1,4]所有违规方法数的并集即为答案
    //考虑容斥，[1,4]所有违规方法数=
    //1违规+2违规+3违规+4违规
    //-(1,2违规，1,3违规)...->一共C(4,2)种
    //+C(4,3)
    //-(1,2,3,4均违规)
    //表示有几个违规可以使用四个二进制位表示
    //当二进制位有奇数个1，对应符号为+，有偶数个1，对应符号为-
    while (n--) {
        for (int i = 1; i <= 4; i++) {
            cin >> d[i];
        }
        cin >> s;
        ll sum = dp[s];
        ll diff = 0;
        //枚举状态
        for (int sta = 1; sta <= 15; sta++) {
            int cnt = dig(sta);
            if (cnt & 1) {
                ll tmp = 0;
                for (int j = 0; j < 4; j++) {
                    if ((sta >> j) & 1) {
                        tmp += 1LL * c[j + 1] * (d[j + 1] + 1);
                    }
                }
                if (s - tmp >= 0) {
                    diff += dp[s - tmp];
                }
            }
            else {
                ll tmp = 0;
                for (int j = 0; j < 4; j++) {
                    if ((sta >> j) & 1) {
                        tmp += 1LL * c[j + 1] * (d[j + 1] + 1);
                    }
                }
                if (s - tmp >= 0) {
                    diff -= dp[s - tmp];
                }
            }
        }
        cout << sum - diff << '\n';




    }



    return 0;
}