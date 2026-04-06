#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        //我们可以考虑对所有数字取模，都是正数
        //取模之后的和能被整除即可
        //将处理完的数组累加再对sum0取模得到x
        //然后我们找连续的一段和取模为x即可
        int n = nums.size();
        long long sum0 = 0;
        for (int i = 0; i < n; i++)
        {
            nums[i] %= p;
            sum0 += nums[i];
        }
        int x = sum0 % p;
        if (x == 0)
        {
            return 0;
        }
        //map存前缀和对p取模and最后一次出现的位置
        unordered_map<int, int> mp;
        //假如虚拟0
        mp.insert({ 0,-1 });
        long long sum = 0;
        //我们要找的是(presum[i]-presum[j])%p=presum[i]%p-presum[j]%p=x
        //如果presum[i]%p>x
        //对于目前遍历到的presum[i],要找j位置满足presum[j]%p=presum[i]%p-x,这很显然
        //对于另一情况presum[i]%p<x
        //也就是说要找一个presum[j]%p=presum[i]%p-x+p
        //+p是为了填补负数
        //减法的同余原理
        long long ans = 1e5+5;
        for (int i = 0; i < n; i++)
        {
            sum = (sum + nums[i])%p;
            long long tar = (sum - x + p) % p;
            if (mp.count(tar) > 0)
            {
                ans = min(ans, (long long)i - mp[tar]);
            }
            mp[sum] = i;
        }
        if (ans < 1e5 + 5 && ans!=nums.size())
        {
            return ans;
        }
        return -1;
    }
};