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
class MajorityChecker {
public:
    //线段树维护：
    //区间上进行摩尔投票之后剩下的出现次数最多元素,以及出现次数(剩余次数)
    struct node {
        int val, t;
    };
    vector<int> can;
    vector<int> cnt;
    int n;
    void up(int i) {
        int l = i << 1, r = i << 1 | 1;
        if (can[l] == can[r]) {
            can[i] = can[l];
            cnt[i] = cnt[l] + cnt[r];
        }
        else {
            if (cnt[l] > cnt[r]) {
                can[i] = can[l];
                cnt[i] = cnt[l] - cnt[r];
            }
            else if (cnt[l] < cnt[r]) {
                can[i] = can[r];
                cnt[i] = cnt[r] - cnt[l];
            }
            else {
                can[i] = -INF;
                cnt[i] = 0;
            }
        }
    }
    void build(int i, int l, int r, vector<int>& a) {
        if (l == r) {
            can[i] = a[l];
            cnt[i] = 1;
            return;
        }
        int mid = (r + l) >> 1;
        build(i << 1, l, mid, a);
        build(i << 1 | 1, mid + 1, r, a);
        up(i);
    }
    node query0(int ql, int qr, int i, int l, int r) {
        if (ql <= l && r <= qr) {
            return { can[i],cnt[i] };
        }
        int mid = (l + r) >> 1;
        node c1 = { -INF,0 }, c2 = { -INF,0 };
        if (ql <= mid) {
            c1 = query0(ql, qr, i << 1, l, mid);
        }
        if (qr > mid) {
            c2 = query0(ql, qr, i << 1 | 1, mid + 1, r);
        }
        node ans = { -INF,0 };
        if (c1.val == c2.val) {
            ans.val = c1.val;
            ans.t = c1.t + c2.t;
        }
        else {
            if (c1.t > c2.t) {
                ans.val = c1.val;
                ans.t = c1.t - c2.t;
            }
            else if (c2.t > c1.t) {
                ans.val = c2.val;
                ans.t = c2.t - c1.t;
            }
        }
        return ans;
    }
    vector<vector<int>> g;
    MajorityChecker(vector<int>& arr) {
        auto& a = arr;
        n = a.size();
        can.assign(n << 2, 0);
        cnt.assign(n << 2, 0);
        build(1, 0, n - 1, a);
        g.assign(20001, vector<int>());
        for (int i = 0; i < n; i++) {
            g[a[i]].emplace_back(i);
        }
    }
    int query(int left, int right, int threshold) {
        //只要出现大于等于threshold次即可，那么我们找区间范围上次数最多的
        //注意条件:2*threshold > r-l+1
        //也就是说我们要找这个区间的绝对众数，出现次数大于len/2的
        //就可以考虑摩尔投票的思路
        auto ans = query0(left, right, 1, 0, n - 1);
        if (ans.val == -INF) return -1;
        int val = ans.val;
        //我们提前收集了各个元素的下标的集合，且收集的时候就做到有序，
        //这一步查询元素val在区间[l,r]上的出现次数
        auto it1 = lower_bound(g[val].begin(), g[val].end(), left) - g[val].begin();
        auto it2 = upper_bound(g[val].begin(), g[val].end(), right) - g[val].begin();
        int num = it2 - it1;
        if (num >= threshold) return val;
        return -1;
    }
};
