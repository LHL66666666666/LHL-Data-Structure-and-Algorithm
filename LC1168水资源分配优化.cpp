/*
题目描述
村里面一共有 n 栋房子。我们希望通过建造水井和铺设管道来为所有房子供水。

对于每个房子 i，我们有两种可选的供水方案：一种是直接在房子内建造水井，
成本为 wells[i - 1] （注意 -1 ，因为 索引从0开始 ）；
另一种是从另一口井铺设管道引水，数组 pipes 给出了在房子间铺设管道的成本，
其中每个 pipes[j] = [house1j, house2j, costj] 
代表用管道将 house1j 和 house2j连接在一起的成本。连接是双向的。

请返回 为所有房子都供水的最低总成本 。
提示：

2 <= n <= 10^4
wells.length == n
0 <= wells[i] <= 10^5
1 <= pipes.length <= 10^4
pipes[j].length == 3
1 <= house1j, house2j <= n
0 <= costj <= 105
house1j != house2j
*/
#include<vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int father[10005];
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
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        //核心是创建一个虚拟水源点，将在房子内部自己打水井的开销看作虚拟水源点到这个点的边权
        //这样就转化为了最常见的最小生成树
        //也就是说我们自己再创建n条边,每条边连接虚拟水源点和每一个点
        //假设虚拟水源点在编号0位置
        int m = pipes.size();
        vector<vector<int>> edges;
        for (int i = 0; i < n; i++)
        {
            edges.push_back({ 0,i + 1,wells[i] });
        }
        for (auto& pipe : pipes)
        {
            edges.push_back(pipe);
        }
        //使用Kruskal
        build(n);
        sort(edges.begin(), edges.end(), cmp);
        int n1 = edges.size();
        long long ans = 0;
        for (int i = 0; i < n1; i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            if (find(u) != find(v))
            {
                ans += edges[i][2];
                unite(u, v);
            }
        }
        return ans;
    }
};