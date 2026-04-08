#include <vector>
using namespace std;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        //最多松弛k+1次，经过k+1条边
        //我们不能直接使用Bellman-Ford,因为Bellman-Ford在一轮中的松弛并不一定是只能多延伸出来1个节点
        //我们要限制松弛，保证每一次路径上只能增加一个新的节点
        //使用一张老的dis表存储上一轮松弛之后的状态，每次要更新距离时从老的dis表里查找
        vector<int> pre(n, INF);
        //源点
        pre[src] = 0;
        //最多松弛k+1次，每次增加1条遍
        //k+1次迭代
        for (int i = 0; i <= k; i++)
        {
            //新dis表
            vector<int> next = pre;
            //处理每条边
            for (auto i : flights)
            {
                int u = i[0], v = i[1], w = i[2];
                //尝试松弛，但是要去pre里查找
                if (next[v] > pre[u] + w)
                {
                    next[v] = pre[u] + w;
                }
            }
            //更新pre
            pre.clear();
            pre = next;
        }
        if (pre[dst] < INF) return pre[dst];
        else return -1;
    }
};
/*
本题是带限制的图论最短路问题
需要注意的是，在遍历所有的“点对/边”进行松弛操作前，需要先对 dist 进行备份，
否则会出现「本次松弛操作所使用到的边，也是在同一次迭代所更新的」，从而不满足边数限制的要求。
举个例子，例如本次松弛操作使用了从 a 到 b 的当前最短距离来更新 dist[b]，
直接使用 dist[a] 的话，不能确保 dist[a] 不是在同一次迭代中所更新，
如果 dist[a] 是同一次迭代所更新的话，那么使用的边数将会大于 k 条。
因此在每次迭代开始前，我们都应该对 dist 进行备份，在迭代时使用备份来进行松弛操作。
*/