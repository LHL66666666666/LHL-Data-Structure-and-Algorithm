#include <iostream>
#include <vector>
typedef long long ll;
using namespace std;
struct node {
    int w, v;
};
vector<node> v;
int n, m;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    v.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i].w >> v[i].v;
    }
    //01背包?
    //带路径的01背包
    //我们找出达成最大值的路径，这些路径中都存在的数字属于A类，只存在的一个或几个的属于B类，未出现的属于C类
    //先搞个01背包
    vector<vector<ll> > dp(n + 1, vector<ll>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - v[i].w >= 0) {
                dp[i][j] = max(dp[i - 1][j - v[i].w] + v[i].v, dp[i][j]);
            }
        }
    }
    ll x = dp[n][m];
    //对于一个物品i，我们考虑两个条件：
    //1.如果一定不取i，其余物品随意取，能否达到最大价值x
    //2.如果一定取i，其余物品随意取，能否达到价值x-val[i]
    //dp2[i][j]表示从i号物品到n号物品，随意选择，在花费不超过j的情况下能达到的最大值
    vector<vector<ll>> dp2(n + 2, vector<ll>(m + 1, 0));
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j <= m; j++) {
            dp2[i][j] = dp2[i + 1][j];
            if (j - v[i].w >= 0) {
                dp2[i][j] = max(dp2[i][j], dp2[i + 1][j - v[i].w] + v[i].v);
            }
        }
    }
    vector<char> ret(n + 1, 'C');
    //现在判断每个物品是否符合条件1和2
    for (int i = 1; i <= n; i++) {
        int flag1 = 0, flag2 = 0;
        //检查条件1，一定不取i
        for (int j = 0; j <= m; j++) {
            if (dp[i - 1][j] + dp2[i + 1][m - j] == x) {
                flag1 = 1;
            }
        }
        //检查条件2，一定取i
        for (int j = 0; j <= m - v[i].w; j++) {
            if (dp[i - 1][j] + dp2[i + 1][m - v[i].w - j] == x - v[i].v) {
                flag2 = 1;
            }
        }
        if (flag1 && flag2) {
            ret[i] = 'B';
        }
        else if (!flag1 && flag2) {
            ret[i] = 'A';
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ret[i];
    }
    cout << '\n';
    return 0;
}
