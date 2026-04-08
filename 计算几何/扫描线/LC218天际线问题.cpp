#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
class Solution {
public:
    struct node {
        int h, right;
        bool operator<(const node& other) const {
            return h < other.h;
        }
    };
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        auto& b = buildings;
        //注意到每个长方形的左端点和右端点都是可能成为转折点的位置
        //优先队列按照高度从大到小排
        int n = b.size();
        vector<int> p;
        for (int i = 0; i < n; i++) {
            p.emplace_back(b[i][0]);
            p.emplace_back(b[i][1]);
        }
        sort(p.begin(), p.end());
        vector<vector<int>> ans;
        priority_queue<node> pq;
        int id = 0;
        for (int i = 0; i < 2 * n; i++) {
            //加入
            while (id < n && b[id][0] == p[i]) {
                pq.emplace(b[id][2], b[id][1]);
                ++id;
            }
            //弹出过期
            while (!pq.empty() && pq.top().right <= p[i]) {
                pq.pop();
            }
            //记录答案
            if (pq.empty()) {
                if (ans.empty()) {
                    ans.push_back({ p[i],0 });
                }
                else {
                    auto bk = ans.back();
                    if (bk[1] == 0) {
                        continue;
                    }
                    ans.push_back({ p[i],0 });
                }
                continue;
            }
            if (ans.empty()) {
                ans.push_back({ p[i],pq.top().h });
            }
            else {
                auto bk = ans.back();
                if (bk[1] == pq.top().h) {
                    continue;
                }
                ans.push_back({ p[i],pq.top().h });
            }
        }
        return ans;
    }
};