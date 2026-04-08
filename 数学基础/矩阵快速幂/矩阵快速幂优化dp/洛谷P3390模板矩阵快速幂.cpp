#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr ll MOD = 1e9 + 7;
int n;
ll k;
vector<vector<ll>> matrix;
vector<vector<ll>> multi(vector<vector<ll>>& m1, vector<vector<ll>>& m2) {
    int a = m1.size(), c = m1[0].size(), b = m2.size();
    vector res(a, vector<ll>(b, 0));
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            ll ans = 0;
            for (int l = 0; l < c; l++) {
                ans = (ans + m1[i][l] % MOD * m2[l][j] % MOD) % MOD;
            }
            res[i][j] = ans;
        }
    }
    return res;
}
vector<vector<ll>> qpow(vector<vector<ll>>& m, ll x) {
    vector ans(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) ans[i][i] = 1;
    auto base = m;
    while (x) {
        if (x & 1) {
            ans = multi(ans, base);
        }
        base = multi(base, base);
        x >>= 1;
    }
    return ans;
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    matrix.assign(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    auto ans = qpow(matrix, k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}