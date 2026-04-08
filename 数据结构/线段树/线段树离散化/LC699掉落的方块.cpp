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
    vector<int> seg;
    vector<int> reset;
    vector<int> upd;
    void up(int i) {
        seg[i] = max(seg[i << 1], seg[i << 1 | 1]);
    }
    void lazy(int qv, int i) {
        seg[i] = qv;
        reset[i] = qv;
        upd[i] = 1;
    }
    void down(int i) {
        if (upd[i]) {
            lazy(reset[i], i << 1);
            lazy(reset[i], i << 1 | 1);
            upd[i] = 0;
        }
    }
    void update(int ql, int qr, int qv, int l, int r, int i) {
        if (ql <= l && r <= qr) {
            lazy(qv, i);
            return;
        }
        int mid = (r + l) >> 1;
        down(i);
        if (ql <= mid) {
            update(ql, qr, qv, l, mid, i << 1);
        }
        if (qr > mid) {
            update(ql, qr, qv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
    int query(int ql, int qr, int l, int r, int i) {
        if (ql <= l && r <= qr) {
            return seg[i];
        }
        int mid = (r + l) >> 1;
        down(i);
        int ans = -INF;
        if (ql <= mid) {
            ans = max(ans, query(ql, qr, l, mid, i << 1));
        }
        if (qr > mid) {
            ans = max(ans, query(ql, qr, mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        auto& a = positions;
        int n = a.size();
        vector<int> ans;
        //分析：维护区间最大值
        //注意维护左右边界：当正方形边缘如果是擦过的话，可以正常下落
        //处理每一条操作时，先查询区间[l,l+len-1]的最大值x，
        //再将区间[l,l+len-1]最大值重置为len+x
        //x轴坐标范围很大，但是方块数量只有1000，考虑离散化
        //先处理出每个方块cover的区间，将区间端点离散化
        vector<int> pos(1, 0);
        for (int i = 0; i < n; i++) {
            int l = a[i][0], r = a[i][0] + a[i][1] - 1;
            pos.emplace_back(l);
            pos.emplace_back(r);
        }
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end()), pos.end());
        int n1 = pos.size();
        seg.assign(n1 << 2, 0);
        reset.assign(n1 << 2, 0);
        upd.assign(n1 << 2, 0);
        for (int i = 0; i < n; i++) {
            auto l = lower_bound(pos.begin(), pos.end(), a[i][0]) - pos.begin();
            auto r = lower_bound(pos.begin(), pos.end(), a[i][0] + a[i][1] - 1) - pos.begin();
            int cur = query(l, r, 1, n1, 1);
            update(l, r, cur + a[i][1], 1, n1, 1);
            int res = query(1, n1, 1, n1, 1);
            ans.emplace_back(res);
        }
        return ans;
    }
};