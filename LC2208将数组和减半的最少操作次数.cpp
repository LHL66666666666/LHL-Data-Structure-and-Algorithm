/*
给你一个正整数数组 nums 。每一次操作中，你可以从 nums 中选择 任意 一个数并将它减小到 恰好 一半。
（注意，在后续操作中你可以对减半过的数继续执行操作）
请你返回将 nums 数组和 至少 减少一半的 最少 操作数。
*/
//贪心可知，每次减半最大的元素是最优策略
//但是如果我们每次都进行排序时间复杂度会很大，考虑维护一个优先队列
//大根堆，每次操作堆顶元素，然后维护堆即可
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
class Solution {
public:
    int halveArray(vector<int>& nums) {
        double sum = 0;
        int n = nums.size();
        for (auto num : nums)
        {
            sum += num;
        }
        //维护一个优先级队列
        priority_queue<double> pq(nums.begin(),nums.end());
        double sum1 = sum;
        int ans = 0;
        while (sum1 > sum / 2.0)
        {
            double tmp = pq.top();
            pq.pop();
            tmp /= 2.0;
            sum1 -= tmp;
            pq.push(tmp);
            ans++;
        }
        return ans;
    }
};
/*
思路是用最大堆来模拟，每次将堆顶减半，累加每次减半的值，直到不低于总和的一半。

虽然浮点数可以通过本题，但是本着能不用浮点就不用浮点的想法（毕竟浮点数计算会产生误差），
将每个数都乘上一个 2 的幂次（比如 2^20），因为可以 证明 每个数除 2 的次数不会超过 20。

这样就可以愉快地用整数 + 堆来模拟了。
*/

//另一思路：继续优化到O(n):中位数分治