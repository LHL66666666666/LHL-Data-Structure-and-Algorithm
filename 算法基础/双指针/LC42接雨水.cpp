#include <vector>
using namespace std;
int pre[20005];
int suf[20005];
class Solution {
public:
    int max(int a, int b)
    {
        return a > b ? a : b;
    }
    int min(int a, int b)
    {
        return a < b ? a : b;
    }
    int trap(vector<int>& height) {
        //思路一：来自灵茶山艾府
        //核心：将每一个位置的格子看作一个单独的水桶
        //也就是说我们要讨论每一个下标的储水量，再累加
        //计算每一个格子的盛水量
        //我们构建前缀最大值和后缀最大值的数组
        //将每个位置看作水桶，计算每个位置盛水量，再求和
        //开两个数组，算前缀最大值和后缀最大值
        int n = height.size();
        memset(pre, 0, sizeof(pre));
        memset(suf, 0, sizeof(suf));
        for (int i = 0; i < n; i++) 
        {
            if (i == 0)
            {
                pre[i] = height[0];
                continue;
            }
            pre[i] = max(pre[i - 1], height[i]);
        }
        for (int i = n-1; i>=0; i--)
        {
            if (i == n - 1)
            {
                suf[i] = height[n - 1];
                continue;
            }
            suf[i] = max(suf[i + 1], height[i]);
        }
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans += (min(pre[i], suf[i]) - height[i]);
        }
        return ans;
    }
};

//双指针解法：
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        //依旧是计算每个下标的存储水量
        //只需要维护从左向右的最大值和从右向左的最大值即可
        //用双指针，指向两端，遍历时，将较小的一侧向中间移动
        //每个下标水量取决于两侧柱子较短的那个
        //只需要遍历一遍
        //还是维护前后缀最大值
        int l = 0, r = n - 1;
        long long ans = 0;
        int lmax = height[0], rmax = height[n - 1];
        while (l < r)
        {
            
            if (lmax<rmax)
            {
                ans += lmax - height[l];
                l++;
                lmax = max(lmax, height[l]);
            }
            else
            {
                ans += rmax - height[r];
                r--;
                rmax = max(rmax, height[r]);

            }
        }
        return ans;
    }
};