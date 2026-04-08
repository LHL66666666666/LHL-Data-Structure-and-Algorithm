#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
// constexpr ll MOD=1e9+7;
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        auto& a = machines;
        int n = a.size();
        if (n == 1) return 0;
        int sum = accumulate(a.begin(), a.end(), 0);
        if (sum % n != 0) {
            return -1;
        }
        int x = sum / n;
        int ans = 0;
        vector<int> pre(n);
        vector<int> suf(n);
        pre[0] = a[0];
        for (int i = 1; i < n; i++) {
            pre[i] = pre[i - 1] + a[i];
        }
        suf[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suf[i] = suf[i + 1] + a[i];
        }
        ans = max(ans, abs((n - 1) * x - suf[1]));
        for (int i = 1; i <= n - 2; i++) {
            int l = i * x - pre[i - 1], r = (n - i - 1) * x - suf[i + 1];
            if (l > 0 && r > 0) {
                ans = max(ans, l + r);
            }
            else ans = max(ans, max(abs(l), abs(r)));
        }
        ans = max(ans, abs((n - 1) * x - pre[n - 2]));
        return ans;

    }
};