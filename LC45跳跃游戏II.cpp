#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
class Solution {
public:
    int jump(vector<int>& nums) {
        auto& a = nums;
        int n = a.size();
        //维护当前能到的最大值，和当前能到的范围内，再走一步能到的最大值
        int cur = 0, nxt = 0;
        int cnt = 0;
        for (int i = 0; i <= n - 1; i++) {
            if (i > cur) {
                ++cnt;
                cur = nxt;
            }
            nxt = max(nxt, i + a[i]);
        }
        return cnt;

    }
};