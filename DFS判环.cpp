#include <iostream>
#include <vector>
using namespace std;
//三色标记法
bool dfs(int v, vector<vector<int>>& g, vector<int>& color) {
    color[v] = 1;  // 1表示正在访问中（灰色）

    for (int u : g[v]) {
        if (color[u] == 0) {  // 0表示未访问（白色）
            if (dfs(u, g, color)) {
                return true;  // 发现环
            }
        }
        else if (color[u] == 1) {  // 遇到正在访问中的节点
            return true;  // 发现环！
        }
    }

    color[v] = 2;  // 2表示已访问完成（黑色）
    return false;
}

bool hasCycle(int n, vector<vector<int>>& graph) {
    vector<int> color(n, 0);  // 0=未访问，1=访问中，2=已访问

    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (dfs(i, graph, color)) {
                return true;
            }
        }
    }
    return false;
}