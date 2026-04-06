#include<set>
using namespace std;
struct node {
    int l, r;
    mutable int val;
    node(const int& il, const int& ir, const int& iv) :l(il), r(ir), val(iv) {}
    bool operator<(const node& o) const {
        return l < o.l;
    }
};
set<node> s;
//区间分裂操作
auto split(int pos) {
    //在set中查找到第一个l>=pos的位置
    auto it = s.lower_bound(node(pos, 0, 0));
    //如果it->l==pos，即已经存在以x为左端点的区间，那么直接返回即可，无需分割
    if (it != s.end() && it->l == pos) {
        return it;
    }
    //如果不以pos为左端点，那么我们跳到前一个区间进行分裂操作
    --it;
    int l = it->l, r = it->r, val = it->val;
    //删除原节点
    s.erase(it);
    s.insert(node(l, pos - 1, val));
    return s.insert(node(pos, r, val)).first;
}
//区间赋值操作
auto assign(int l, int r, int v) {
    auto itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, v));
}
//取出区间进行遍历操作
void perform(int l, int r) {
    auto itr = split(r + 1), itl = split(l);
    for (; itl != itr; ++itl) {
        // Perform Operations here
    }
}