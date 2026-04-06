#include <vector>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        //如果是递增的，就在连续递增序列的最右侧卖出
        int pre = prices[0];
        int ans = 0;
        int i = 0;
        while (i < n)
        {
            int tmp = i;
            while (tmp + 1 < n && prices[tmp + 1] >= prices[tmp])
            {
                ++tmp;
            }
            ans += prices[tmp] - pre;
            i = tmp + 1;
            if (i<n) pre = prices[i];

        }
        return ans;
    }
};
//更简单的写法
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int ans = 0;
        for (int i = 1; i < n; i++)
        {
            ans += max(prices[i] - prices[i - 1], 0);
        }
        return ans;
    }
};