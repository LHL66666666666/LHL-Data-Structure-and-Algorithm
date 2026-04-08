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
        vector<vector<ll>> res(5, vector<ll>(5, 0));
        for (int i = 0; i < 5; i++) {
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
    //aeiou:12345
    int countVowelPermutation(int n) {
        //反向建图即可找出i-1->i的递推式，这是一个k维1阶的递推关系式
        //dp[i][j]表示长度为i的前缀的方案数量
        vector<vector<ll>> dp = { {1,1,1,1,1} };
        //关系矩阵，反向见图得到
        //a由e,i,u转移来
        //e由a,i转移来
        //i由e,o转移来
        //o由i转移来
        //u由i,o转移来
        vector<vector<ll>> matrix = {
            {0,1,0,0,0},
            {1,0,1,0,0},
            {1,1,0,1,1},
            {0,0,1,0,1},
            {1,0,0,0,0}
        };
        vector<vector<ll>> ans = qpow(matrix, n - 1);
        ans = multi(dp, ans);
        ll res = 0;
        for (int i = 0; i < 5; i++) {
            res += ans[0][i];
            res %= MOD;
        }
        return res;
    }
};