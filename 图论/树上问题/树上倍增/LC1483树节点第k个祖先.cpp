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
class TreeAncestor {
public:
    vector<vector<int>> g;
    vector<vector<int>> st;
    vector<int> dep;
    void dfs(int u, int fa) {
        if (fa != -1) {
            dep[u] = dep[fa] + 1;
        }
        for (int j = 1; j < 32; j++) {
            if (dep[u] - (1LL << j) > 0) {
                st[u][j] = st[st[u][j - 1]][j - 1];
            }
            else break;
        }
        //子节点st表的构建依赖于所有父节点的
        //因此先建立好父节点的，再搞子节点
        for (auto& v : g[u]) {
            dfs(v, u);
        }
    }
    TreeAncestor(int n, vector<int>& parent) {
        auto& p = parent;
        g.assign(n + 1, vector<int>());
        st.assign(n + 1, vector<int>(32, -1));
        dep.assign(n + 1, 0);
        st[0][0] = -1;
        for (int i = 1; i < n; i++) {
            g[p[i]].emplace_back(i);
            st[i][0] = p[i];
        }
        dep[0] = 1;
        dfs(0, -1);
        //注意!!构建st表的时候，需要按照dfs的顺序来构建!!
    }
    int getKthAncestor(int node, int k) {
        if (dep[node] - k <= 0) return -1;
        int tmp = k;
        int anc = node;
        for (int j = 31; j >= 0; j--) {
            if (tmp >= (1LL << j)) {
                tmp -= (1LL << j);
                anc = st[anc][j];
            }
        }
        return anc;
    }
};