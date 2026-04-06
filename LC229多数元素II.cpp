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
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        auto& a = nums;
        int n = a.size();
        //出现次数超过n/3的数字，最多存在2个
        //类似于找超过n/2次数的数字，我们维护2个候选，每次删掉3个不同元素
        //如果要找超过n/k次数的数字，那么最多k-1个候选，每次删除k个数字
        //用一个哈希表来维护这些候选值
        //这个写法支持n/k的情况，使用map比较好写
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            if (mp.size() < 2) {
                mp[a[i]]++;
            }
            else {
                if (mp.find(a[i]) != mp.end()) {
                    mp[a[i]]++;
                    continue;
                }
                vector<int> del;
                for (auto& e : mp) {
                    e.second--;
                    if (e.second == 0) {
                        del.emplace_back(e.first);
                    }
                }
                for (auto& e : del) {
                    auto it = mp.find(e);
                    mp.erase(it);
                }
            }
        }
        vector<int> can(2, -INF);
        int id = 0;
        for (auto& e : mp) {
            can[id++] = e.first;
        }
        vector<int> cnt1(2);
        for (int i = 0; i < n; i++) {
            cnt1[0] += (a[i] == can[0]);
            cnt1[1] += (a[i] == can[1]);
        }
        vector<int> ans;
        if (cnt1[0] > n / 3) ans.emplace_back(can[0]);
        if (cnt1[1] > n / 3) ans.emplace_back(can[1]);
        return ans;
    }
};