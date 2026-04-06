#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        //由于可以并行，我们开一个pre数组存储在修这门课之前需要的时间
        //并行时间最大值即为答案
        int ans = 0;
        vector<int> pre(n+1);
        pre.assign(n + 1, 0);
        vector<int> indegree(n+1);
        vector<vector<int>> g(n+1);
        for (auto& i : relations)
        {
            g[i[0]].push_back(i[1]);
            indegree[i[1]]++;
        }
        queue<int> qe;
        for (int i = 1; i <= n; i++)
        {
            if (indegree[i] == 0)
            {
                qe.push(i);
                pre[i] = time[i-1];
            }
        }
        while (!qe.empty())
        {
            int tmp = qe.front();
            qe.pop();
            //何时收集答案，当这个节点不再有邻居时
            //注意，并行完成，时间取最大值
            if (g[tmp].size() == 0)
            {
                ans = max(ans, pre[tmp]);
            }
            //消除影响
            for (auto& i : g[tmp])
            {
                pre[i] = max(pre[i], pre[tmp]);
                indegree[i]--;
                if (indegree[i] == 0)
                {
                    //加入队列之前先加上自己
                    qe.push(i);
                    pre[i] += time[i-1];
                }
            }
        }
        return ans;
    }
};