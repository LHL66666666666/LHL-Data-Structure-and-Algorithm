/*
给你一个 n 个点组成的无向图边集 edgeList ，其中 edgeList[i] = [ui, vi, disi] 表示点 ui 和点 vi 之间有一条长度为 disi 的边。请注意，两个点之间可能有 超过一条边 。

给你一个查询数组queries ，其中 queries[j] = [pj, qj, limitj] ，你的任务是对于每个查询 queries[j] ，判断是否存在从 pj 到 qj 的路径，且这条路径上的每一条边都 严格小于 limitj 。

请你返回一个 布尔数组 answer ，其中 answer.length == queries.length ，当 queries[j] 的查询结果为 true 时， answer 第 j 个值为 true ，否则为 false 。
*/
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int father[100005];
    void build(int n)
    {
        for (int i = 0; i <= n; i++)
        {
            father[i] = i;
        }
    }
    int find(int x)
    {
        if (father[x] != x)
        {
            father[x] = find(father[x]);
        }
        return father[x];
    }
    void unite(int x, int y)
    {
        father[find(x)] = find(y);
    }
    static bool cmp(vector<int>& a, vector<int>& b)
    {
        return a[2] < b[2];
    }
    struct node {
        int p, q, lim;
        int id;
    }qu[100005];
    static bool cmp1(node x, node y)
    {
        return x.lim < y.lim;
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        //ok思考出来了，每次按照limit构建最小生成树
        //将边权小于limit的全合并，查询两个点是否属于一个集合
        //为了不每次重新生成，我们对limit排序，按照limit从小到大来处理
        build(n);
        //边权按照从小到大排序
        sort(edgeList.begin(), edgeList.end(), cmp);
        //查询按照limit从小到大排序
        int n2 = queries.size();
        for (int i = 0; i < n2; i++)
        {
            qu[i].id = i;
            qu[i].p = queries[i][0];
            qu[i].q = queries[i][1];
            qu[i].lim = queries[i][2];
        }
        sort(qu, qu + n2, cmp1);
        vector<bool> ans(n2);
        //按照limit从小到大来
        //双指针
        int p = 0;
        int n1 = edgeList.size();
        for (int i = 0; i < n2; i++)
        {
            int limit = qu[i].lim;
            while (p < n1 && edgeList[p][2] < limit)
            {
                int u = edgeList[p][0];
                int v = edgeList[p][1];
                //检查并且合并
                if (find(u) != find(v))
                {
                    unite(u, v);
                }
                p++;
            }
            //检查查询的两个点是否连通
            if (find(qu[i].p) == find(qu[i].q))
            {
                ans[qu[i].id] = true;
            }
            else ans[qu[i].id] = false;
        }
        return ans;
    }
};