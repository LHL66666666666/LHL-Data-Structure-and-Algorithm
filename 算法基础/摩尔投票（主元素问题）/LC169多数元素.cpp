#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        auto& a = nums;
        int n = a.size();
        //我们希望一次删除两个不同的数字，
        //这样最终剩下来的就是唯一有可能成为多数元素的候选值
        //打擂台的思想
        //维护当前出现最多的数字以及出现的次数，
        //每次遇到一个新元素就将这个当前最多元素的次数-1(相当于删掉两个不同元素)
        //如果遇到的元素和这个数字相等，那么出现次数++
        int can = 0, cnt = 0;
        for (int i = 0; i < n; i++) {
            if (cnt == 0) {
                ++cnt;
                can = a[i];
                continue;
            }
            if (a[i] != can) {
                --cnt;
            }
            else {
                ++cnt;
            }
        }
        int cnt1 = 0;
        for (int i = 0; i < n; i++) {
            cnt1 += (a[i] == can);
        }
        if (cnt1 > n / 2) return can;
        return -1;
    }
};