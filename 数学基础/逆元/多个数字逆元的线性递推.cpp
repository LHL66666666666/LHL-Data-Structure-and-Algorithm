#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr ll MOD = 998244353;
// constexpr ll MOD=1e9+7;
int n;
ll p;
vector<ll> inv;
void init() {
    //生成[1,n]所有数字在模p意义下的乘法逆元
    //逆元线性递推公式
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (ll)(p - p / i) * inv[p % i] % p;
    }
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p;
    inv.assign(n + 1, 0);
    init();
    for (int i = 1; i <= n; i++) cout << inv[i] << '\n';
    return 0;
}