#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
// constexpr ll MOD=998244353;
constexpr ll MOD = 1e9 + 7;
class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        auto& a = nums;
        int n = a.size();
        int can = 0, cnt = 0;
        for (int i = 0; i < n; i++) {
            if (cnt == 0) {
                can = a[i];
                ++cnt;
                continue;
            }
            if (a[i] == can) {
                ++cnt;
            }
            else --cnt;
        }
        //can即为绝对众数
        vector<int> pre(n);
        int tot = 0;
        for (int i = 0; i < n; i++) {
            tot += (a[i] == can);
            pre[i] = tot;
        }
        for (int i = 0; i < n; i++) {
            if (pre[i] > (i + 1) / 2 && tot - pre[i] > (n - i - 1) / 2) {
                return i;
            }
        }
        return -1;
    }
};