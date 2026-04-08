#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        //给定的是有向无环图
        //自己的思考：应当反向建图，富人指向穷人
        //按照拓扑排序，每次出队列的元素pk出一个最小值传递给上游节点，也就是指向的节点
        //邻接表建图
        int n = quiet.size();
        //quiet复制一份，表示原来都维持自己答案，后续再根据拓扑排序来传递更优的答案
        //注意ans存的是人
        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            ans[i] = i;
        }
        vector<vector<int>> g(n);
        vector<int> indegree(n);
        for (auto& i : richer)
        {
            g[i[0]].push_back(i[1]);
            indegree[i[1]]++;
        }
        queue<int> qe;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                qe.push(i);
            }
        }
        while (!qe.empty())
        {
            int tmp = qe.front();
            qe.pop();
            //传递信息
            for (auto& i : g[tmp])
            {
                //注意！我们修改的一直是ans中的信息，不要拿原信息比较，拿新的信息比较
                if (quiet[ans[tmp]] < quiet[ans[i]])
                {
                    ans[i] = ans[tmp];
                }
                indegree[i]--;
                if (indegree[i] == 0)
                {
                    qe.push(i);
                }
            }
        }
        return ans;
    }
};