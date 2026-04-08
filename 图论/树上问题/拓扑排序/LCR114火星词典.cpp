#include <vector>
#include <queue>
#include <string>
using namespace std;
class Solution {
public:
    int indegree[26];
    string alienOrder(vector<string>& words) {
        //我们需要构建新的字典序，可以考虑做成一张图
        //字典序小的指向字典序大的，只需要输出他的拓扑序即可
        //注意可能会有不合法的字母顺序，例如"abc","ab"这种一定不符合任何字典序
        //首先我们只需要在出现过的字母中建图，未出现的不需要考虑
        int n = words.size();
        //初始化入度表
        memset(indegree, -1, sizeof(indegree));
        for (auto& word : words)
        {
            int n1 = word.size();
            for (int i = 0; i < n1; i++)
            {
                if (indegree[word[i] - 'a'] == -1)
                {
                    indegree[word[i] - 'a'] = 0;
                }
            }
        }
        int cnt1 = 0;
        for (int i = 0; i < 26; i++)
        {
            if (indegree[i] == 0)
            {
                cnt1++;
            }
        }
        //建图
        vector<vector<int>> g(26);
        //遍历，每次只需比较相邻元素即可
        for (int i = 0; i < n - 1; i++)
        {
            string cur = words[i];
            string next = words[i + 1];
            int cn = cur.size();
            int nn = next.size();
            //逐位比较，也就是比较前缀
            int lim = min(cn, nn);
            for (int j = 0; j < lim; j++)
            {
                if (cur[j] != next[j])
                {
                    //比较出大小关系，字典序小的指向字典序大的
                    g[cur[j] - 'a'].emplace_back(next[j] - 'a');
                    indegree[next[j] - 'a']++;
                    //提前退出
                    break;
                }
                //注意这里特判！！不合法的情况，例如"abc","ab"这种一定不符合任何字典序
                //返回空字符串
                if (cn > nn && j == lim - 1)
                {
                    return "";
                }
            }
        }
        //拓扑排序
        string ans;
        queue<int> qe;
        for (int i = 0; i < 26; i++)
        {
            if (indegree[i] == 0)
            {
                qe.push(i);
            }
        }
        //统计个数，判断是否有环
        int cnt = 0;
        while (!qe.empty())
        {
            int tmp = qe.front();
            qe.pop();
            ++cnt;
            ans += (tmp + 'a');
            //消除影响
            for (auto i : g[tmp])
            {
                indegree[i]--;
                if (indegree[i] == 0)
                {
                    qe.push(i);
                }
            }
        }
        if (cnt == cnt1)
        {
            return ans;
        }
        else return "";
    }
};