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
    struct node {
        int len, right;
        friend bool operator>(const node& a, const node& b) {
            return a.len > b.len;
        }
    };
    struct qy {
        int pos, id;
    };
    static bool cmp(const qy& a, const qy& b) {
        return a.pos < b.pos;
    }
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        auto& itv = intervals;
        auto& q = queries;
        int n = itv.size();
        sort(itv.begin(), itv.end());
        //操作离线
        int m = q.size();
        vector<qy> q1(m);
        for (int i = 0; i < m; i++) {
            q1[i].pos = q[i];
            q1[i].id = i;
        }
        sort(q1.begin(), q1.end(), cmp);
        priority_queue<node, vector<node>, greater<node>> pq;
        vector<int> ans(m);
        int id = 0;
        for (int i = 0; i < m; i++) {
            //加入左端点比自己小的
            while (id < n && itv[id][0] <= q1[i].pos) {
                pq.emplace(itv[id][1] - itv[id][0] + 1, itv[id][1]);
                ++id;
            }
            //弹出过期
            while (!pq.empty() && pq.top().right < q1[i].pos) {
                pq.pop();
            }
            if (pq.empty()) {
                ans[q1[i].id] = -1;
            }
            else ans[q1[i].id] = pq.top().len;
        }
        return ans;
    }
};