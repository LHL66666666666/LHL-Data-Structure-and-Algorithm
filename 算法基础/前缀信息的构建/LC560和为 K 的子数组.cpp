#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        //思路与和为k的连续子数组一脉相承
        //我们考虑以第i个位置结尾，他前面出现的目标前缀和的数量即可
        //目标是和为k也就是presum[i]-presum[x]=k,需要在哈希表中寻找的为presum[i]-k
        //一个虚拟0表示从开始位置不加任何数字
        unordered_map<int, vector<int>> mp;
        mp.insert({ 0,{-1}});
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            mp[sum].emplace_back(i);
            if (i > 0)
            {
                nums[i] += nums[i - 1];
            }
        }
        long long ans = 0;
        //遍历每个结束位置
        for (int i = 0; i < nums.size(); i++)
        {
            int tar = nums[i] - k;
            if (mp.count(tar) > 0)
            {
                for (auto j : mp[tar])
                {
                    if (j < i)
                    {
                        ans++;
                    }
                }
            }
        }
        return ans;
    }
};

//优化：边遍历的时候边更新哈希表，不要先处理完哈希表
//就可以避免再找下标大小关系
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp.insert({0,1});
        //value表示出现次数
        long long ans = 0;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            int tar = sum - k;
            if (mp.count(tar) > 0)
            {
                ans += mp[tar];
            }
            mp[sum]++;
        }
        return ans;
    }
};