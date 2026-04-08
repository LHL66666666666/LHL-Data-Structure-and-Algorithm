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
    vector<vector<ll>> st1;
    vector<vector<ll>> st2;
    ll getMaxFunctionValue(vector<int>& receiver, ll k) {
        auto& rec = receiver;
        int n = rec.size();
        st1.assign(n + 1, vector<ll>(35));
        st2.assign(n + 1, vector<ll>(35));
        for (int i = 0; i < n; i++) {
            st1[i][0] = rec[i];
            st2[i][0] = rec[i];
        }
        for (int j = 1; j < 35; j++) {
            for (int i = 0; i < n; i++) {
                st1[i][j] = st1[st1[i][j - 1]][j - 1];
                st2[i][j] = st2[i][j - 1] + st2[st1[i][j - 1]][j - 1];
            }
        }
        //遍历每一个x
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ll tmp = 0;
            ll stp = k;
            int pos = i;
            for (int j = 34; j >= 0; j--) {
                if (stp - (1LL << j) >= 0) {
                    stp -= (1LL << j);
                    tmp += st2[pos][j];
                    pos = st1[pos][j];
                }
            }
            ans = max(ans, tmp + i);
        }
        return ans;
    }
};