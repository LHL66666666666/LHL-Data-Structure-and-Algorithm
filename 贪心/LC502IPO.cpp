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
        int p, c;
    };
    static bool cmp(const node& x, const node& y) {
        return x.c < y.c;
    }
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        auto& p = profits;
        auto& c = capital;
        int n = p.size();
        vector<node> a(n);
        for (int i = 0; i < n; i++) {
            a[i].p = p[i], a[i].c = c[i];
        }
        sort(a.begin(), a.end(), cmp);
        //资本到达一定数量才能解锁一些项目，对于每个能实现的项目，选择利润最大的
        priority_queue<int> pq;
        int cur = w;
        int cnt = k;
        int id = 0;
        while (cnt) {
            //解锁
            while (id < n && a[id].c <= cur) {
                pq.emplace(a[id].p);
                ++id;
            }
            if (pq.empty()) break;
            //每次选最大的
            cur += pq.top();
            pq.pop();
            --cnt;
        }
        return cur;
    }
};