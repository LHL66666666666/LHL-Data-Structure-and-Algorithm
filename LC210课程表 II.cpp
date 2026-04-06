/*
现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。
给你一个数组 prerequisites ，
其中 prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修 bi 。
例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，
你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组 。
*/
#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        //先建图，使用邻接表建图
        vector<vector<int>> graph(numCourses + 1);
        vector<int> indegree(numCourses + 1);
        //建图的同时建立入度表统计入度
        //这里直接范围式循环，因为给定的点的数组可能为空！注意
        for (auto& i : prerequisites)
        {
            //注意这里是后面的指向前面的，本题的特殊之处
            graph[i[1]].push_back(i[0]);
            //被指向的元素入度++
            indegree[i[0]]++;
        }
        //准备一个队列处理,队列收集入度为0的店依次弹出，弹出顺序就是拓扑序
        queue<int> qe;
        //cnt存储弹出的数量，如果所有元素均被弹出，那么证明无环，否则有环(即产生循环依赖)
        int cnt = 0;
        vector<int> ans;
        //第一遍，先收集初始入度为0的点
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
            {
                qe.push(i);
            }
        }
        //当队列不为空时，循环弹出入度为0的点，每次弹出时处理这个点指向的点，
        //将被指向的点的入度--
        while (!qe.empty())
        {
            //弹出入度为0的元素
            int tmp = qe.front();
            ans.emplace_back(tmp);
            qe.pop();
            cnt++;
            //处理这个元素的邻居，同时如果发现0就入队列
            for (auto& i : graph[tmp])
            {
                indegree[i]--;
                if (indegree[i] == 0)
                {
                    qe.push(i);
                }
            }
        }
        if (cnt == numCourses)
        {
            return ans;
        }
        else return {};
    }
};