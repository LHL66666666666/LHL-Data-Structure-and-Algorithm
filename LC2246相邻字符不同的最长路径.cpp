#include <vector>
#include <string>
#include <queue>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
struct node {
    //len1表示一定要自己，len2表示一定不要自己，len3表示一定要自己，且是单链
    int len1, len2, len3;
};
class Solution {
public:
    vector<vector<int>> g;
    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();
        if (n == 1) return 1;
        g.resize(n);
        for (int i = 1; i < n; i++)
        {
            int v = i, u = parent[i];
            g[u].emplace_back(v);
        }
        auto ans = dfs(s, 0);
        return max(ans.len1, ans.len2);

    }
    //可能性分为两种：
    //一定要这个节点的最长路径，不要这个节点的最长路径
    //记录这两个信息，取最大值
    node dfs(string& s,int u)
    {
        if (g[u].empty())
        {
            node x;
            x.len1 = 1, x.len2 = 0, x.len3 = 1;
            return x;
        }
        int len1 = 1, len2 = 0, len3 = 1;
        priority_queue<int> pq;
        for (auto& v : g[u])
        {
            auto to = dfs(s, v);
            if (s[v] != s[u])
            {
                pq.push(to.len3);
            }
            len2 = max(len2, max(to.len1, to.len2));
        }
        if (!pq.empty())
        {
            int cur = pq.top();
            pq.pop();
            len3 += cur;
            len1 += cur;
        }
        if (!pq.empty())
        {
            int cur = pq.top();
            pq.pop();
            len1 += cur;
        }
        node ret;
        ret.len1 = len1, ret.len2 = len2, ret.len3 = len3;
        return ret;
    }
};