#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        auto& a = nums;
        int n = a.size();
        int ans = INF, l = INF, r = INF;
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
        multiset<int> s;
        for (int i = 0; i < n; i++) {
            pq.emplace(a[i][0], make_pair(i, 0));
            s.insert(a[i][0]);
        }
        l = *s.begin(), r = *s.rbegin();
        ans = r - l;
        while (1) {
            auto cur = pq.top();
            pq.pop();
            auto it0 = s.find(cur.first);
            s.erase(it0);
            int row = cur.second.first;
            int id = cur.second.second;
            if (id == a[row].size() - 1) break;
            pq.emplace(a[row][id + 1], make_pair(row, id + 1));
            s.insert(a[row][id + 1]);
            auto x = (*s.rbegin()) - (*s.begin());
            if (ans > x) {
                ans = x;
                l = *s.begin();
                r = *s.rbegin();
            }
        }
        return { l,r };
    }
};