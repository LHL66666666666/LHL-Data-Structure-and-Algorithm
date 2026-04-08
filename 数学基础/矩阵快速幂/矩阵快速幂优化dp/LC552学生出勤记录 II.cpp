#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
// constexpr ll MOD=998244353;
constexpr ll MOD = 1e9 + 7;
class Solution {
public:
    vector<vector<ll>> multi(vector<vector<ll>>& m1, vector<vector<ll>>& m2) {
        int a = m1.size(), c = m1[0].size(), b = m2.size();
        vector res(a, vector<ll>(b, 0));
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                for (int k = 0; k < c; k++) {
                    res[i][j] = (res[i][j] + m1[i][k] % MOD * m2[k][j] % MOD) % MOD;
                }
            }
        }
        return res;
    }
    vector<vector<ll>> qpow(vector<vector<ll>>& mat, int k) {
        vector<vector<ll>> res(6, vector<ll>(6, 0));
        for (int i = 0; i < 6; i++) {
            res[i][i] = 1;
        }
        vector<vector<ll>> base = mat;
        while (k) {
            if (k & 1) {
                res = multi(res, base);
            }
            base = multi(base, base);
            k >>= 1;
        }
        return res;
    }
    int checkRecord(int n) {
        //A的数量:0,1
        //L:不能连续3个及以上,也就是只能有0,1,2个
        //设计状态:2*3=6种,对应A取0,1，L取0,1,2
        //dp[i][j]表示前缀i的字符的合法串的数量,状态为j
        //j=0:A=0,L=0
        //j=1:A=0,L=1
        //j=2:A=0,L=2
        //j=3:A=1,L=0
        //j=4:A=1,L=1
        //j=5:A=1,L=2
        //原始dp版本
        // vector<vector<ll>> dp(n+1,vector<ll>(6,0));
        // dp[1][0]=1,dp[1][1]=1,dp[1][2]=0,dp[1][3]=1,dp[1][4]=0,dp[1][5]=0;
        // for (int i=2;i<=n;i++) {
        //     dp[i][0]=(dp[i-1][0]+dp[i-1][1]+dp[i-1][2])%MOD;
        //     dp[i][1]=(dp[i-1][0])%MOD;
        //     dp[i][2]=(dp[i-1][1])%MOD;
        //     dp[i][3]=(dp[i-1][0]+dp[i-1][1]+dp[i-1][2]+dp[i-1][3]+dp[i-1][4]+dp[i-1][5])%MOD;
        //     dp[i][4]=(dp[i-1][3])%MOD;
        //     dp[i][5]=(dp[i-1][4])%MOD;
        // }
        // ll res=0;
        // for (int i=0;i<6;i++) {
        //     res=(res+dp[n][i])%MOD;
        // }
        // return res;
        //矩阵快速幂
        vector<vector<ll>> dp = { {1,1,0,1,0,0} };
        vector<vector<ll>> matrix = {
            {1,1,0,1,0,0},
            {1,0,1,1,0,0},
            {1,0,0,1,0,0},
            {0,0,0,1,1,0},
            {0,0,0,1,0,1},
            {0,0,0,1,0,0}
        };
        auto res = qpow(matrix, n - 1);
        res = multi(dp, res);
        ll ans = 0;
        for (int i = 0; i < 6; i++) {
            ans = (ans + res[0][i]) % MOD;
        }
        return ans;
    }
};