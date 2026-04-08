/*
n 块石头放置在二维平面中的一些整数坐标点上。每个坐标点上最多只能有一块石头。

如果一块石头的 同行或者同列 上有其他石头存在，那么就可以移除这块石头。

给你一个长度为 n 的数组 stones ，其中 stones[i] = [xi, yi] 表示第 i 块石头的位置，返回 可以移除的石子 的最大数量。  
*/
#include <vector>
#include <map>
using namespace std;
class Solution {
public:
    int father[1005];
    void build()
    {
        for (int i = 0; i < 1005; i++)
        {
            father[i] = i;
        }
    }
    int find(int x)
    {
        if (x != father[x])
        {
            father[x] = find(father[x]);
        }
        return father[x];
    }
    bool isSame(int x, int y)
    {
        return find(x) == find(y);
    }
    void unite(int x, int y)
    {
        father[find(y)] = find(x);
    }
    int removeStones(vector<vector<int>>& stones) {
        build();
        int n = stones.size();
        //我们观察可知，相连的石头，以及跟这个相连区段上某一个点通过某行或某列相互串联起来的石头
        //我们称之为一个集团，易知一个集团的石头一定可以消除到只剩1个
        //只需要求集团的数量
        //合并这些点即可，也就是说对于这个点的坐标，如果之前的点在该行或该列出现过，就可以合并为1个
        //我们需要哈希表来存储在某行或某列是否存在已经出现过的石头，是则合并
        //另外，本题不好使用离散化，因为我们需要严格相等的行列指标
        map<int, pair<int, int>> mpx;
        map<int, pair<int, int>> mpy;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (mpx[stones[i][0]].second != 0)
            {
                unite(i, mpx[stones[i][0]].first);
            }
            else {
                mpx[stones[i][0]].first = i;
                mpx[stones[i][0]].second++;
            }
            if (mpy[stones[i][1]].second != 0)
            {
                unite(i, mpy[stones[i][1]].first);
            }
            else {
                mpy[stones[i][1]].first = i;
                mpy[stones[i][1]].second++;
            }
        }
        for (int i = 0; i < n; i++)
        {
            //统计集合的数量（连通分量的个数）
            if (i == father[i])
            {
                ans++;
            }
        }
        return n - ans;
    }
};
//简化，不需要pair
class Solution {
public:
    int father[1005];
    void build()
    {
        for (int i = 0; i < 1005; i++)
        {
            father[i] = i;
        }
    }
    int find(int x)
    {
        if (x != father[x])
        {
            father[x] = find(father[x]);
        }
        return father[x];
    }
    bool isSame(int x, int y)
    {
        return find(x) == find(y);
    }
    void unite(int x, int y)
    {
        father[find(y)] = find(x);
    }
    int removeStones(vector<vector<int>>& stones) {
        build();
        int n = stones.size();
        //我们观察可知，相连的石头，以及跟这个相连区段上某一个点通过某行或某列相互串联起来的石头
        //我们称之为一个集团，易知一个集团的石头一定可以消除到只剩1个
        //只需要求集团的数量
        //合并这些点即可，也就是说对于这个点的坐标，如果之前的点在该行或该列出现过，就可以合并为1个
        //我们需要哈希表来存储在某行或某列是否存在已经出现过的石头，是则合并
        //另外，本题不好使用离散化，因为我们需要严格相等的行列指标
        map<int, int> mpx;
        map<int, int> mpy;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int row = stones[i][0];
            int col = stones[i][1];
            if (!mpx.count(row))
            {
                mpx[row] = i;
            }
            else unite(i, mpx[row]);
            if (!mpy.count(col))
            {
                mpy[col] = i;
            }
            else unite(i, mpy[col]);

        }
        for (int i = 0; i < n; i++)
        {
            //统计集合的数量
            if (i == father[i])
            {
                ans++;
            }
        }
        return n - ans;
    }
};