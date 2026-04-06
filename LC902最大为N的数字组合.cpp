#include <vector>
#include <string>
using namespace std;
using ll = long long;
class Solution {
public:
    //数位dp的尝试策略
    //将 n 转换成字符串 s，定义 dfs(i,isLimit,isNum) 表示构造从左往右第 i 位及其之后数位的合法方案数，其中：
    //isLimit 表示当前是否受到了 n 的约束。若为真，则第 i 位填入的数字至多为 s[i]，否则至多为 9。
    //例如 n = 234，如果前面填了 23，那么最后一位至多填 4；如果前面填的不是 23，那么最后一位至多填 9。
    //如果在受到约束的情况下填了 s[i]，那么后续填入的数字仍会受到 n 的约束。
    //isNum 表示 i 前面的数位是否填了数字。若为假，则当前位可以跳过（不填数字），或者要填入的数字至少为1(不过本题已经明确没有0，可以任意填)；
    //若为真，则必须填数字，且要填入的数字从 0 开始。
    //这样我们可以控制构造出的是一位数 / 两位数 / 三位数等等。
    //对于本题而言，要填入的数字可直接从 digits 中选择。
    //枚举要填入的数字
    //我们考虑：
    //1) 如果选择组成的数字位数上小于n的位数，那么是随意选择的
    //   也就是选出来再全排列
    //2) 如果在前缀保持与n的前缀相同的情况下，某一位选择的该位小于n这一位的数字
    //   那么后续的数字可以随意选择
    //3) 如果前缀保持与n的前缀相同的情况下，该位置选择了与n这一位一样的数
    //   那么后续仍有限制，不能超过n该位上的数
    ll dfs(vector<string>& d, string& s,int id,int islimit,int isnum)
    {
        if (id == s.size())
        {
            if (isnum) return 1;
            else return 0;
        }
        ll ans = 0;
        //如果前面没填数字，这里还可以不填
        // islimit 改为 0，因为没有填数字，位数都比 n 要短，自然不会受到 n 的约束
        // isnum 仍然为 0，因为没有填任何数字
        if (isnum == 0)
        {
            ans += dfs(d, s, id + 1, 0, 0);
        }
        //不论前面填不填，都可以在这一位上填
        //这一位上必须填数字的情况
        //讨论是否被限制
        //注意：对于一般的题目而言，如果这里 is_num 为 false，则必须从 1 开始枚举，
        //由于本题 digits 没有 0，所以无需处理这种情况
        if (islimit == 1)
        {
            //被限制了
            for (int i = 0; i < d.size(); i++)
            {
                if (d[i][0] < s[id])
                {
                    //填了一位比n这一位小的数字，后续就无限制了
                    ans += dfs(d, s, id + 1, 0, 1);
                }
                else if (d[i][0] == s[id])
                {
                    //填了一位与n这一位相等的数字，后续依然被限制
                    ans += dfs(d, s, id + 1, 1, 1);
                }
                else {
                    //填了比这一位大的，不行，退出，因为d有序
                    break;
                }
            }
        }
        else {
            //无限制，既然来到这都无限制，后续都无限制
            //随意填
            ans += 1LL * d.size() * dfs(d, s, id + 1, 0, 1);
        }
        return ans;
    }
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        //digits为非递减数组
        //将n转化为字符串
        string s;
        int tmp = n;
        while (tmp)
        {
            s += (tmp % 10 + '0');
            tmp /= 10;
        }
        reverse(s.begin(), s.end());
        return dfs(digits, s, 0, 1, 0);
    }
};
//记忆化版本
/*
只需要记忆化 i，因为：
对于一个固定的 i，它受到 isLimit 或 isNum 的约束在整个递归过程中至多会出现一次，没必要记忆化。
比如 n=234，当 i=2 的时候，前面可以填 11,12,13,…,23，如果受到 isLimit 的约束，就说明前面填的是 23。
「当 i=2 的时候，前面填的是 23」这件事情，在整个递归过程中至多会出现一次。
另外，如果只记忆化 i，dp 数组的含义就变成在不受到 n 的约束时的合法方案数，
所以要在 !isLimit && isNum 成立时才去记忆化。
接着上面的例子，在前面填 23 的时候，下一位填的数字不能超过 4，因此算出来的结果是不能套用到前面填的是 11,12,13,...这些数字上面的。
*/
class Solution {
public:
    vector<int> dp;
    ll dfs(vector<string>& d, string& s, int id, int islimit, int isnum)
    {
        if (id == s.size())
        {
            if (isnum) return 1;
            else return 0;
        }
        if (!islimit && isnum && dp[id] != -1) return dp[id];
        ll ans = 0;
        if (isnum == 0)
        {
            ans += dfs(d, s, id + 1, 0, 0);
        }
        if (islimit == 1)
        {
            for (int i = 0; i < d.size(); i++)
            {
                if (d[i][0] < s[id])
                {
                    ans += dfs(d, s, id + 1, 0, 1);
                }
                else if (d[i][0] == s[id])
                {
                    ans += dfs(d, s, id + 1, 1, 1);
                }
                else {
                    break;
                }
            }
        }
        else {
            ans += 1LL * d.size() * dfs(d, s, id + 1, 0, 1);
        }
        if (!islimit && isnum) dp[id] = ans;
        return ans;
    }
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string s;
        int tmp = n;
        while (tmp)
        {
            s += (tmp % 10 + '0');
            tmp /= 10;
        }
        reverse(s.begin(), s.end());
        dp.assign(s.size(), -1);
        return dfs(digits, s, 0, 1, 0);
    }
};