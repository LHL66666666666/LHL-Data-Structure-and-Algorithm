#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
class Solution {
public:
    static bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
        return a.first < b.first;
    }
    int minTaps(int n, vector<int>& ranges) {
        auto& a = ranges;
        vector<pair<int, int>> v;
        for (int i = 0; i <= n; i++) {
            v.emplace_back(i - a[i], i + a[i]);
        }
        sort(v.begin(), v.end(), cmp);
        int l = 0, cur = -1;
        int nxt = 0;
        int cnt = 0;
        int p = 0;
        for (int i = 0; i <= n; i++) {
            while (p <= n && v[p].first <= l) {
                nxt = max(nxt, v[p].second);
                ++p;
            }
            if (i > cur) {
                ++cnt;
                if (nxt < i) {
                    cnt = -1;
                    break;
                }
                cur = nxt;
                l = cur;
            }
        }
        return cnt;
    }
};
//写法2
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> right_most(n + 1);
        //维护每个位置能到达的最右端点
        for (int i = 0; i <= n; i++) {
            int r = ranges[i];
            int left = max(i - r, 0);
            right_most[left] = max(right_most[left], i + r);
        }
        int ans = 0;
        int cur_right = 0; // 已建造的桥的右端点
        int next_right = 0; // 下一座桥的右端点的最大值
        for (int i = 0; i < n; i++) { // 如果走到 n-1 时没有返回 -1，那么必然可以到达 n
            next_right = max(next_right, right_most[i]);
            if (i == cur_right) { // 到达已建造的桥的右端点
                if (i == next_right) {
                    return -1; // 无论怎么造桥，都无法从 i 到 i+1
                }
                cur_right = next_right; // 造一座桥
                ans++;
            }
        }
        return ans;
    }
};