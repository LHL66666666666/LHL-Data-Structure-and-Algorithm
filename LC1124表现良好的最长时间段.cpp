#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        //依旧进行转化，将>8的转换为1，<8的为0
        for (int i = 0; i < hours.size(); i++)
        {
            if (hours[i] > 8)
            {
                hours[i] = 1;
            }
            else hours[i] = -1;
        }
        //我们仍然考虑遍历数组，每个以i结尾的位置最长的长度是多少
        //分两种情况
        //1.如果到i位置，前缀和>0,那么满足，这个就是最长
        //2.如果到i位置，前缀和<0,那么我们只需要找前缀和-1
        //为什么？这个数组的特殊性，由于全是1，-1，前缀和是连续变化的
        //也就是说，如果出现了一个前缀和小于0例如x<0
        //如果存在x-1，那么x-1就一定是满足条件的最早位置
        //考虑如果出现x-1，那么x-1前面必有x，又由连续性，x-1就是那个最早的满足条件位置
        //如果没有x-1，那么前面没有满足条件的位置
        unordered_map<int, int> mp;
        //map的value是key最早出现的位置
        int sum = 0;
        int ans = 0;
        for (int i = 0; i < hours.size(); i++)
        {
            sum += hours[i];
            if (sum > 0)
            {
                ans = max(ans, i + 1);
            }
            else {
                int tar = sum - 1;
                if (mp.count(tar) > 0)
                {
                    ans = max(ans, i - mp[tar]);
                }
            }
            if (mp.count(sum) == 0)
            {
                mp.insert({ sum,i });
            }
        }
        return ans;
    }
};