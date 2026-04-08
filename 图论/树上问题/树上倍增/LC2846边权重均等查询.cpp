#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
// constexpr ll MOD=998244353;
constexpr ll MOD = 1e9 + 7;
class Solution {
public:
    struct node {
        int lca, mx;
    };
    vector<vector<pair<int, int>>> g;
    vector<int> dep;
    vector<vector<int>> st1;
    vector<vector<vector<int>>> st2;
    void dfs(int u, int fa, int w) {
        if (fa != -1) {
            dep[u] = dep[fa] + 1;
            st1[u][0] = fa;
            st2[u][0][w]++;
        }
        for (int j = 1; j <= 15; j++) {
            if (dep[u] - (1LL << j) > 0) {
                st1[u][j] = st1[st1[u][j - 1]][j - 1];
                for (int k = 0; k <= 26; k++) {
                    st2[u][j][k] = st2[u][j - 1][k] + st2[st1[u][j - 1]][j - 1][k];
                }
            }
            else break;
        }
        for (auto& e : g[u]) {
            int v = e.first;
            if (v == fa) continue;
            dfs(v, u, e.second);
        }
    }
    node query(int v1, int v2) {
        if (dep[v1] < dep[v2]) swap(v1, v2);
        int pos1 = v1, pos2 = v2;
        int stp1 = dep[v1] - dep[v2];
        vector<int> cnt(27);
        for (int j = 15; j >= 0; j--) {
            if (stp1 - (1LL << j) >= 0) {
                for (int k = 0; k <= 26; k++) {
                    cnt[k] += st2[pos1][j][k];
                }
                pos1 = st1[pos1][j];
                stp1 -= (1LL << j);
            }
        }
        if (pos1 == pos2) {
            int mx = *max_element(cnt.begin(), cnt.end());
            return { pos1,mx };
        }
        for (int j = 15; j >= 0; j--) {
            if (dep[pos1] - (1LL << j) > 0) {
                if (st1[pos1][j] != st1[pos2][j]) {
                    for (int k = 0; k <= 26; k++) {
                        cnt[k] += st2[pos1][j][k];
                        cnt[k] += st2[pos2][j][k];
                    }
                    pos1 = st1[pos1][j];
                    pos2 = st1[pos2][j];
                }
            }
        }
        for (int k = 0; k <= 26; k++) {
            cnt[k] += st2[pos1][0][k];
            cnt[k] += st2[pos2][0][k];
        }
        int mx = *max_element(cnt.begin(), cnt.end());
        return { st1[pos1][0],mx };
    }
    vector<int> minOperationsQueries(int n, vector<vector<int>>& eg, vector<vector<int>>& queries) {
        g.assign(n + 1, vector<pair<int, int>>());
        for (auto& e : eg) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        //只需找出两点之间路径上出现次数最多的边权即可
        //注意到，边权的值域很小,[1,26]
        st1.assign(n + 1, vector<int>(16));
        st2.assign(n + 1, vector(16, vector<int>(27)));
        dep.assign(n + 1, 0);
        dep[0] = 1;
        dfs(0, -1, 0);
        vector<int> ans;
        for (auto& q : queries) {
            int x = q[0], y = q[1];
            auto cur = query(x, y);
            //总节点数
            int lca = cur.lca;
            int sum = (dep[x] + dep[y] - 2 * dep[lca]);
            ans.emplace_back(sum - cur.mx);
        }
        return ans;
    }
};