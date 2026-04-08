#include <iostream>
using namespace std;
typedef long long ll;
int n, m, p, q;
struct node {
    int l, r;
}a[10000005];
int father[1000005];
int col[1000005];
void build() {
    for (int i = 1; i <= n + 1; i++) {
        father[i] = i;
    }
}
int find(int x) {
    if (father[x] != x) {
        father[x] = find(father[x]);
    }
    return father[x];
}
void dbg() {
    for (int i = 1; i <= m; i++) {
        cout << a[i].l << ' ' << a[i].r << '\n';
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> p >> q;
    build();
    for (int i = 1; i <= m; i++) {
        int t1 = ((ll)i * p + q) % n + 1, t2 = ((ll)i * q + p) % n + 1;
        int l = min(t1, t2), r = max(t1, t2);
        //注意在这里再+1！！！！！！
        a[i].l = l, a[i].r = r + 1;
    }
    //dbg();
    //反向处理，最后染色的覆盖在最上面，反向处理时遇到已经染色的就不要处理
    for (int i = m; i >= 1; i--) {
        int l = a[i].l, r = a[i].r;
        int fl = find(l), fr = find(r);
        // // 写法1
        // for (;fl<fr;) {
        //     col[fl]=i;
        //     father[fl]=find(fl+1);
        //     fl=find(fl);
        // }
        // 写法2
        for (int j = fl; j < fr;) {
            col[j] = i;
            father[j] = find(j + 1);
            j = find(j);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << col[i] << '\n';
    }
    return 0;
}