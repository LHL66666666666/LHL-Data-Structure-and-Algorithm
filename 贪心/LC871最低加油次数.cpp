#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int& t = target;
        int& s = startFuel;
        auto& a = stations;
        a.push_back({ t,0 });
        int n = a.size();
        priority_queue<int> pq;
        int ans = 0;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            s -= (a[i][0] - cur);
            int d = a[i][1];
            cur = a[i][0];
            if (s < 0) {
                while (s < 0 && !pq.empty()) {
                    auto e = pq.top();
                    pq.pop();
                    s += e;
                    ++ans;
                }
                if (s < 0) {
                    return -1;
                }
            }
            pq.emplace(d);
        }
        return ans;
    }
};
/*
当汽车行驶到第 i 个加油站时，视作获取了一个装有 fuel[i] 升汽油的油桶。
在后续的行驶过程中，可以在没油时，把油桶中的油加到汽车中。
选哪个（哪些）油桶？
为了让加油次数尽量少，贪心地选油量多的油桶。
由于有添加和删除操作，用最大堆维护这些油桶
*/