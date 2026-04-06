#include <vector>
using namespace std;
class Solution {
public:
    const int INF = 0x3f3f3f3f;
    vector<vector<int>> g;
    vector<int> dfn;
    vector<int> siz;
    //vector<int> pre;
    vector<int> val;
    int cnt;
    void dfs(int u, int fa)
    {
        dfn[u] = ++cnt;
        for (auto& v : g[u])
        {
            if (v != fa)
            {
                dfs(v, u);
                siz[dfn[u]] += siz[dfn[v]];
            }
        }
    }
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        cnt = 0;
        int n = nums.size();
        g.resize(n);
        dfn.resize(n + 1);
        siz.assign(n + 1, 1);
        val.resize(n + 1);
        val[0] = 0;
        //pre.resize(n + 1);
        //pre[0] = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int u = edges[i][0], v = edges[i][1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        //先找dfn序，再预处理一个异或前缀和数组，
        //对于每种删边方案，我们只要知道其中两个的异或值，就能根据整体的异或值算出剩下的一个
        dfs(0, -1);
        for (int i = 0; i < n; i++)
        {
            val[dfn[i]] = nums[i];
        }
        for (int i = 1; i <= n; i++)
        {
            val[i] ^= val[i - 1];
        }
        int ans = INF;
        //n^2枚举每种删边方案
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n - 1; j++)
            {
                //坑点：要判断这两棵子树是独立的，还是具有包含关系
                int u1 = edges[i][0], v1 = edges[i][1];
                int id1 = dfn[u1], id2 = dfn[v1];
                if (id1 < id2) swap(id1, id2);
                int u2 = edges[j][0], v2 = edges[j][1];
                int id3 = dfn[u2], id4 = dfn[v2];
                if (id3 < id4) swap(id3, id4);
                //判断两棵子树的关系
                //int m1 = id1, m2 = id3;
                if (id1+siz[id1]-1>=id3 && id1<=id3)
                {
                    //包含关系,id3是id1子树
                    int x1 = val[id1 + siz[id1] - 1] ^ val[id1 - 1];
                    int x2 = val[id3 + siz[id3] - 1] ^ val[id3 - 1];
                    int x3 = val[n] ^ x1;
                    x1 ^= x2;
                    int d = max(x1, max(x2, x3)) - min(x1, min(x2, x3));
                    ans = min(ans, d);
                }
                else if (id3 + siz[id3] - 1 >= id1 && id3 <= id1)
                {
                    //包含关系,id1是id3子树
                    int x1 = val[id1 + siz[id1] - 1] ^ val[id1 - 1];
                    int x2 = val[id3 + siz[id3] - 1] ^ val[id3 - 1];
                    int x3 = val[n] ^ x2;
                    x2 ^= x1;
                    int d = max(x1, max(x2, x3)) - min(x1, min(x2, x3));
                    ans = min(ans, d);
                }
                else {
                    //如果是非包含关系,即二者相互独立
                    int x1 = val[id1 + siz[id1] - 1] ^ val[id1 - 1];
                    int x2 = val[id3 + siz[id3] - 1] ^ val[id3 - 1];
                    int x3 = val[n] ^ x1 ^ x2;
                    int d = max(x1, max(x2, x3)) - min(x1, min(x2, x3));
                    ans = min(ans, d);
                }
            }
        }
        return ans;
    }
};