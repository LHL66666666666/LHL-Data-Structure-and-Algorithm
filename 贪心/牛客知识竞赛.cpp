#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;
int T;
int n;
struct node {
    int a, b;
};
bool cmp1(const node& x, const node& y) {
    return abs(x.a - x.b) < abs(y.a - y.b);
}
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<node> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].a >> a[i].b;
    }
    sort(a.begin() + 1, a.end(), cmp1);
    //按照|a[i].a-a[i].b|从小到大排序
    //遍历一遍，对于i位置元素我们找[1,i-1]中哪个与i搭配最优
    //有如下断言：当来到i位置时,a[i].a,a[i].b中较小者一定会成为瓶颈
    //原因：前面元素的差值都不超过|a[i].a-a[i].b|,前面的无法抵消i位置较小者的影响
    //因此一定要找前面a或b最大的来抵消较小者的影响
    //只需维护前缀最大a以及b
    int ma = a[1].a, mb = a[1].b;
    int ans = 0;
    for (int i = 2; i <= n; i++) {
        if (a[i].a < a[i].b) {
            ans = max(ans, ma + a[i].a);
        }
        else {
            ans = max(ans, mb + a[i].b);
        }
        ma = max(ma, a[i].a);
        mb = max(mb, a[i].b);
    }
    cout << fixed << std::setprecision(1) << ans / 2.0 << '\n';
    return 0;
}