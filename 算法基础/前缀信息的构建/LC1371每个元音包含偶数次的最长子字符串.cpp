#include <string>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int findTheLongestSubstring(string s) {
        //要找连续的子字符串
        //统计以第i个位置结尾的最长的满足条件的子串
        //使用状态压缩bitmask
        //将5个元音压到5个二进制位上，这样就变成了有限个状态,2^5=32个状态
        //就可以用哈希表高效查询，
        //因为要出现偶数次，考虑异或运算的性质
        //奇数次是1，偶数次是0
        //同时异或运算还有逆运算的好性质
        int n = s.size();
        //哈希表记录某一状态最早出现的位置
        unordered_map<int, int> mp;
        //加入虚拟0
        mp.insert({ 0,-1 });
        //记录异或前缀和
        //状态构建为
        //u o i e a
        int xorsum = 0;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == 'a')
            {
                xorsum ^= 1;
            }
            else if (s[i] == 'e')
            {
                xorsum ^= (1 << 1);
            }
            else if (s[i] == 'i')
            {
                xorsum ^= (1 << 2);
            }
            else if (s[i] == 'o')
            {
                xorsum ^= (1 << 3);
            }
            else if (s[i] == 'u')
            {
                xorsum ^= (1 << 4);
            }
            //要查找的是异或上xorsum=0的数字
            int tar = xorsum;
            if (mp.count(tar) > 0)
            {
                ans = max(ans, i - mp[tar]);
            }
            if (mp.count(xorsum) == 0)
            {
                mp[xorsum] = i;
            }

        }
        return ans;
    }
};