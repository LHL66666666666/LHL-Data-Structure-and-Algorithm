#include <vector>
using namespace std;
class Solution {
public:
    long long max(long long a, long long b)
    {
        return a > b ? a : b;
    }
    long long min(long long a, long long b)
    {
        return a < b ? a : b;
    }
    int maxArea(vector<int>& height) {
        int n = height.size();
        if (n == 2)
        {
            return min(height[0], height[1]);
        }
        int l = 0, r = n - 1;
        long long ans = 0;
        /*
        while (l < r)
        {
            //我们发现如果越靠近中间如果柱子高度越低，再取是无意义的
            ans = max(ans, (r - l) * min(height[l], height[r]));
            //接下来要先移动哪一个
            //显然移动那个较小的
            bool flag = 0;
            if (height[l] < height[r])
            {
                flag = 1;
                l++;
            }
            else r--;
            while (r > l && height[l] < height[l - 1] && flag )
            {
                l++;
            }
            while (r>l && height[r] < height[r + 1] && !flag )
            {
                r--;
            }
        }
        //其实谁短移动谁就行了，不需要这些额外的优化，反而容易越界
        */
        while (l < r) {
            ans = max(ans, (long long)(r - l) * min(height[l], height[r]));

            if (height[l] < height[r]) {
                l++;
            }
            else {
                r--;
            }
        }
        return ans;
    }
};