#include <string>
using namespace std;
class Solution {
public:
    //id数组方便下标与字符之间的转化
    int id[100005];
    //dp数组的含义：以每个字符结尾的在base中的连续子串的长度
    int dp[26];
    int findSubstringInWraproundString(string s) {
        //子串是指字符串中任意个连续的字符组成的部分
        //状态定义：在目标字符串里面找以a,b,c...z结尾的在base中连续的子串
        //这样天然实现了去重，因为以不同字符结尾的子串一定都是不一样的
        //感觉上就是基于去重考虑设计的这样一个状态
        //假设以a结尾的最长字串是长度为n，那么就会增加n个答案
        //将a,b,c...z每个位置的相加，就能得到最终答案，而且每个都不是重复的
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            id[i] = s[i] - 'a';
        }
        for (int i = 0; i < 26; i++)
        {
            dp[i] = 0;
        }
        //第一个位置的肯定是1
        dp[id[0]] = 1;
        //下面我们维护一个len变量记录目前积累了多少长度的串，更新每个位置的dp表
        int len = 1;
        for (int i = 1; i < n; i++)
        {
            int pre = id[i - 1];
            int cur = id[i];
            if ((pre + 1) % 26 == cur)
            {
                ++len;
            }
            else len = 1;
            //这一步的含义是找到最大的连续子串，比较一下现在累计的长度len和之前算过的dp[cur]哪个更大
            dp[cur] = max(dp[cur], len);
        }
        int ans = 0;
        for (int i = 0; i < 26; i++)
        {
            ans += dp[i];
        }
        return ans;
    }
};