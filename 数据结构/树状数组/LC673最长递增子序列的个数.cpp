#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
class Solution {
public:
    int m;
    struct node {
        int len, cnt;
    };
    vector<node> tree;
    int lowbit(int x) {
        return x & -x;
    }
    void add(int pos, node x) {
        while (pos <= m) {
            int len = x.len, cnt = x.cnt;
            if (tree[pos].len < len) {
                tree[pos].len = len;
                tree[pos].cnt = cnt;
            }
            else if (tree[pos].len == len) {
                tree[pos].cnt += cnt;
            }
            pos += lowbit(pos);
        }
    }
    node query(int pos) {
        int len = 0, cnt = 0;
        while (pos > 0) {
            if (tree[pos].len > len) {
                len = tree[pos].len;
                cnt = tree[pos].cnt;
            }
            else if (tree[pos].len == len) {
                cnt += tree[pos].cnt;
            }
            pos -= lowbit(pos);
        }
        return { len,cnt };
    }
    int findNumberOfLIS(vector<int>& nums) {
        //需要维护一个结构,len[i]表示以i(数值)结尾的最长递增子序列的长度
        //cnt[i]表示以i(数值)结尾的最长递增子序列的数量
        //遍历数组的各个元素,
        //我们需要找到来到每个位置时，以这个位置结尾的LIS的长度和个数
        //同时需要维护每个数值结尾的(len,cnt)信息
        //使用树状数组来维护
        auto a = nums;
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        int id = 1;
        map<int, int> mp;
        for (auto& i : a) {
            mp[i] = id++;
        }
        for (auto& i : nums) {
            i = mp[i];
        }
        tree.resize(id);
        m = id - 1;
        for (int i = 0; i < nums.size(); i++) {
            auto cur = query(nums[i] - 1);
            cur.len++;
            if (cur.cnt == 0) cur.cnt = 1;
            add(nums[i], cur);
        }
        return query(m).cnt;
    }
};