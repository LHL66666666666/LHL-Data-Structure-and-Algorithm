/*
你想要用小写字母组成一个目标字符串 target。

开始的时候，序列由 target.length 个 '?' 记号组成。而你有一个小写字母印章 stamp。

在每个回合，你可以将印章放在序列上，并将序列中的每个字母替换为印章上的相应字母。你最多可以进行 10 * target.length  个回合。

举个例子，如果初始序列为 "?????"，而你的印章 stamp 是 "abc"，那么在第一回合，你可以得到 "abc??"、"?abc?"、"??abc"。（请注意，印章必须完全包含在序列的边界内才能盖下去。）

如果可以印出序列，那么返回一个数组，该数组由每个回合中被印下的最左边字母的索引组成。如果不能印出序列，就返回一个空数组。

例如，如果序列是 "ababc"，印章是 "abc"，那么我们就可以返回与操作 "?????" -> "abc??" -> "ababc" 相对应的答案 [0, 2]；

另外，如果可以印出序列，那么需要保证可以在 10 * target.length 个回合内完成。任何超过此数字的答案将不被接受。
*/
#include <vector>
#include <string>
#include <queue>
using namespace std;
class Solution {
public:
    //int wrong[1005];
    vector<int> movesToStamp(string stamp, string target) {
        //memset(wrong, 0, sizeof(wrong));
        int n = stamp.size();
        int m = target.size();
        //如果满足条件那么肯定可以找到一个最终位置，可能不止一个
        //我们消除最终位置，如果有多个最终位置，我们在最终位置中间找stamp的中间部分
        //在最左侧匹配前缀，最右侧匹配后缀
        //没有要求最少操作次数，只要不超过最大限制即可
        //我们可以进行操作的位置是0到m-n，我们假设这些位置全部操作，只需要确定出一个合适的顺序即可
        //我们定义从每个位置初始为stamp,与target不相同的数目是错误度
        //根据分析，最后一次操作的一定是错误度为0的区域
        //由于可以覆盖，我们考虑逆向思维，每次覆盖之后就相当于将原来这些位置的错误度-1
        //每次操作错误度为0的点，就可以得出顺序
        //这类似拓扑排序，我们将错误度视作入度
        vector<int> wrong(1005);
        //错误度数组是以开头位置作为下标
        wrong.assign(m - n + 1, n);
        //建图
        vector<vector<int>> g(m);
        //注意这里枚举i是枚举每一个开头位置，我们要在每一个开头位置都进行操作
        for (int i = 0; i <= m - n; i++)
        {
            int r = i + n - 1;
            for (int j = i; j <= r; j++)
            {
                //统计错误度
                if (target[j] == stamp[j - i])
                {
                    wrong[i]--;
                }
                else {
                    //这里建图要注意，j位置是错误的点，如果改正了这个错误的点，会对哪些位置产生影响
                    //因为我们在讨论的是i开头的这个长度的匹配效果，改正这个点只对i位置产生影响
                    //否则图上会出现重边
                    //我们消除影响的时候，只需要消除错误位置的影响，原本正确的不能减
                    //因此我们将j位置指向i连一条边即可
                    //j位置错误导致i位置的错误度增加
                    g[j].push_back(i);
                }
            }
        }
        vector<int> ans;
        //vis数组存储某一位置是否被取消过，如果被取消不要重复取消
        vector<int> vis(m);
        //按照拓扑排序的思路
        queue<int> qe;
        int cnt = 0;
        for (int i = 0; i <= m - n; i++)
        {
            if (wrong[i] == 0)
            {
                qe.push(i);
            }
        }
        while (!qe.empty())
        {
            int tmp = qe.front();
            qe.pop();
            ans.push_back(tmp);
            ++cnt;
            //另一个关键点：消除这一块对哪些位置的错误度产生了影响
            //注意：其他位置原来对的不要减掉！！！，不然会出问题，只有错的位置需要减去
            //需要只减去错误的位置,而错误的位置我们建图时已经标记好
            for (int j = tmp; j <= tmp + n - 1; j++)
            {
                if (vis[j] == 0)
                {
                    vis[j] = 1;
                    for (auto i : g[j])
                    {
                        wrong[i]--;
                        if (wrong[i] == 0)
                        {
                            qe.push(i);
                        }
                    }
                }
            }
        }
        //记得反转，我们模拟逆序操作
        reverse(ans.begin(), ans.end());
        if (cnt == m - n + 1)
        {
            return ans;
        }
        else return {};
    }
};