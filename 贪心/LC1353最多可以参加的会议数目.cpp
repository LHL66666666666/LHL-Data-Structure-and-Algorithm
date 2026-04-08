#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
struct DSU {
    vector<size_t> pa, size;
    explicit DSU(size_t size_) : pa(size_), size(size_, 1) {
        iota(pa.begin(), pa.end(), 0);
    }
    size_t find(size_t x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
    void unite(size_t x, size_t y) {
        x = find(x), y = find(y);
        if (x == y) return;
        pa[y] = x;
        size[x] += size[y];
    }
};
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        if (a[1] != b[1]) return a[1] < b[1];
        return a[0] > b[0];
    }
    int maxEvents(vector<vector<int>>& events) {
        auto& a = events;
        int n = a.size();
        sort(a.begin(), a.end(), cmp);
        int lst = a[n - 1][1];
        DSU dsu(lst + 2);
        vector<int> vis(lst + 1);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = a[i][0]; j <= a[i][1];) {
                if (!vis[j]) {
                    vis[j] = 1;
                    dsu.unite(j + 1, j);
                    ++cnt;
                    break;
                }
                j = dsu.find(j);
            }
        }
        return cnt;

    }
};
//方法2
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
    int maxEvents(vector<vector<int>>& events) {
        auto& a = events;
        int n = a.size();
        sort(a.begin(), a.end(), cmp);
        int ed = 0;
        for (int i = 0; i < n; i++) {
            ed = max(ed, a[i][1]);
        }
        //按照开始时间排序，想法是最大化利用每一天的时间
        //因此遍历天数，在按照开始时间排序的数组中，每天可以解锁新的能参加的会议
        //如果有多个会议的 startDay[i]都相同呢?
        //比如有三个会议 [1,1],[1,2],[1,3]，参加哪个会议更好?
        //应当参加最紧迫的会议，也就是结束时间最早的一个
        //我们需要一个数据结构维护结束时间。这个数据结构需要支持如下操作：
        //添加结束时间。
        //查询结束时间的最小值。
        //删除最小的结束时间，表示我们参加这个会议，或者这个会议已过期（结束时间小于当前时间）。
        //最小堆完美符合要求。
        //在第 i 天：
        //删除最小堆中结束时间小于 i 的会议（已过期）。
        //把开始时间为 i 的会议的结束时间，加到最小堆中。
        //如果最小堆不为空，那么弹出堆顶（参加会议），把答案加一
        priority_queue<int, vector<int>, greater<>> pq;
        int id = 0;
        int cnt = 0;
        for (int i = 1; i <= ed; i++) {
            //解锁新的能参加的会议
            while (id < n && a[id][0] == i) {
                pq.emplace(a[id][1]);
                ++id;
            }
            //淘汰过期的会议
            while (!pq.empty() && pq.top() < i) pq.pop();
            //选一个最紧迫的
            if (!pq.empty()) {
                pq.pop();
                ++cnt;
            }
        }
        return cnt;

    }
};
