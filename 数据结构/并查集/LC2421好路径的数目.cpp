#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    //并查集模板
    //代表节点数组，这里注意要保证一个集合中节点数值最大的一个作为代表节点
    int father[30005];
    //cnt数组，存储集合最大元素的数量
    int cnt[30005];
    void build(int n)
    {
        for (int i = 0; i < n; i++)
        {
            father[i] = i;
            cnt[i] = 1;
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
    int unite(int x, int y, vector<int>& vals)
    {
        //注意合并的时候要将合并完成的新集合的最大值设置为这两个集合的元素最大值
        //本题保证每次合并的两个节点一定不是一个集合中的元素
        //注意一定要查find(x)也就是代表节点的数值
        if (vals[find(x)] > vals[find(y)])
        {
            //两个集合最大值不一样，不存在好路径
            //把值较小的那一个挂到值大的上，集合最大值还是较大的那个数字，数量不变
            father[find(y)] = find(x);
            return 0;
        }
        else if (vals[find(x)] < vals[find(y)])
        {
            father[find(x)] = find(y);
            return 0;
        }
        else {
            //两个集合最大值相等，那么我们可以计算答案，计算着两个集合之间的好路径数量
            int ans = cnt[find(x)] * cnt[find(y)];
            //合并集合，同时记得先累加cnt
            cnt[find(y)] += cnt[find(x)];
            father[find(x)] = find(y);
            return ans;
        }
    }
    static bool cmp(pair<int,int>& a, pair<int,int>& b)
    {
        return a.first < b.first;
    }
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        build(n);
        //按照边排序，从小到大处理
        vector<pair<int,int>> id(n-1);
        for (int i = 0; i < n - 1; i++)
        {
            id[i].first = max(vals[edges[i][0]], vals[edges[i][1]]);
            id[i].second = i;
        }
        sort(id.begin(), id.end(), cmp);
        //按照排好序的vals来依次处理
        int ans = 0;
        for (int i = 0; i < n - 1; i++)
        {
            ans += unite(edges[id[i].second][0], edges[id[i].second][1],vals);
        }
        return ans + n;
    }
};

/*
提示 1
当涉及到最大/最小的约束时，往往要按照节点值的顺序思考。
应该从大到小，还是从小到大呢？

提示 2
一种比较暴力的思路是，先考虑节点值最大的点，从这些点中任选两个点，
作为路径的开始节点和结束节点，这样的路径都是满足题目要求的。
设节点值最大的点有 x 个，那么会形成 C(x,2)=x(x−1)/2​条长度大于 1 的好路径。
（单个节点的好路径单独统计）

然后从树中删去这些点，再递归考虑剩下的各个连通块内的好路径个数。
但这样每个节点会被多次统计，最坏情况下的时间复杂度为 O(n^2)

提示 3
倒着思考这一过程，把删除改为合并，你想到了哪个数据结构？

提示 4
并查集。

提示 5
按节点值从小到大考虑。
用并查集合并时，总是从节点值小的点往节点值大的点合并，这样可以保证连通块的代表元的节点值是最大的。
对于节点 x 及其邻居 y，如果 y 所处的连通分量的最大节点值不超过 vals[x]，那么可以把 y 所处的连通块合并到 x 所处的连通块中。
如果此时这两个连通块的最大节点值相同，那么可以根据乘法原理，把这两个连通块内的等于最大节点值的节点个数相乘，加到答案中。
*/