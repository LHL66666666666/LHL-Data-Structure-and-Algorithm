//set和multiset是一个树形容器
//有序集合
#include <iostream>
#include <set>
using namespace std;
void printSet(const set<int>& s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << ' ';
	}
	cout << endl;
}
#include <iostream>
#include <set>
using namespace std;

int main() {
    // 创建一个 set
    set<int> mySet;

    // 插入操作
    cout << "=== 插入操作 ===" << endl;
    mySet.insert(10);
    mySet.insert(30);
    mySet.insert(20);
    mySet.insert(40);
    mySet.insert(20);  // 重复元素，不会被插入

    cout << "Set 中的元素: ";
    for (int num : mySet) {
        cout << num << " ";
    }
    cout << endl;

    // 查找操作
    cout << "\n=== 查找操作 ===" << endl;
    cout << "count(20): " << mySet.count(20) << endl;
    cout << "count(50): " << mySet.count(50) << endl;

    auto it = mySet.find(30);
    if (it != mySet.end()) {
        cout << "找到元素 30" << endl;
    }
    else {
        cout << "未找到元素 30" << endl;
    }

    // lower_bound 和 upper_bound
    cout << "\n=== 范围查找 ===" << endl;
    auto lb = mySet.lower_bound(25);
    auto ub = mySet.upper_bound(35);

    cout << "lower_bound(25): ";
    if (lb != mySet.end()) {
        cout << *lb << endl;
    }
    else {
        cout << "end()" << endl;
    }

    cout << "upper_bound(35): ";
    if (ub != mySet.end()) {
        cout << *ub << endl;
    }
    else {
        cout << "end()" << endl;
    }

    // 删除操作 - 按值删除
    /*
    1. erase(x) - 按值删除
    返回值：删除的元素个数（size_type）
    对于 set，返回值只能是 0 或 1
    */
    cout << "\n=== 删除操作 ===" << endl;
    cout << "删除元素 20，删除了 " << mySet.erase(20) << " 个元素" << endl;
    cout << "删除元素 100，删除了 " << mySet.erase(100) << " 个元素" << endl;

    cout << "删除后 Set 中的元素: ";
    for (int num : mySet) {
        cout << num << " ";
    }
    cout << endl;

    // 删除操作 - 按迭代器删除
    /*
    2. erase(pos) - 按迭代器删除
    返回值：指向被删除元素之后元素的迭代器
    */
    it = mySet.find(30);
    if (it != mySet.end()) {
        mySet.erase(it);
        cout << "通过迭代器删除元素 30" << endl;
    }

    // 删除操作 - 按范围删除
    /*
    3. erase(first, last) - 按范围删除
    返回值：指向最后一个被删除元素之后元素的迭代器
    */
    mySet.insert(50);
    mySet.insert(60);
    mySet.insert(70);

    cout << "添加更多元素后: ";
    for (int num : mySet) {
        cout << num << " ";
    }
    cout << endl;

    auto first = mySet.find(50);
    auto last = mySet.find(70);
    if (first != mySet.end() && last != mySet.end()) {
        mySet.erase(first, ++last);  // 删除 [50, 70] 范围内的元素
        cout << "删除范围 [50,70] 后的元素: ";
        for (int num : mySet) {
            cout << num << " ";
        }
        cout << endl;
    }

    // 迭代器操作
    cout << "\n=== 迭代器操作 ===" << endl;
    mySet.clear();
    mySet.insert({ 1, 2, 3, 4, 5 });

    cout << "正向遍历: ";
    for (auto it = mySet.begin(); it != mySet.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "反向遍历: ";
    for (auto it = mySet.rbegin(); it != mySet.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 容量操作
    cout << "\n=== 容量操作 ===" << endl;
    cout << "set 是否为空: " << (mySet.empty() ? "是" : "否") << endl;
    cout << "set 的大小: " << mySet.size() << endl;

    // 清空操作
    mySet.clear();
    cout << "清空后 set 是否为空: " << (mySet.empty() ? "是" : "否") << endl;
    cout << "清空后 set 的大小: " << mySet.size() << endl;

    return 0;
}/*
set 是关联容器，含有键值类型对象的已排序集，搜索、移除和插入拥有对数复杂度。
set 内部通常采用 红黑树 实现。平衡二叉树 的特性使得 set 非常适合处理需要同时兼顾查找、插入与删除的情况。
和数学中的集合相似，set 中不会出现值相同的元素。
如果需要有相同元素的集合，需要使用 multiset。multiset 的使用方法与 set 的使用方法基本相同。
*/
/*
插入与删除操作
insert(x) 当容器中没有等价元素的时候，将元素 x 插入到 set 中。
erase(x) 删除值为 x 的 所有 元素，返回删除元素的个数。
erase(pos) 删除迭代器为 pos 的元素，要求迭代器必须合法。
erase(first,last) 删除迭代器在 [𝑓𝑖𝑟𝑠𝑡,𝑙𝑎𝑠𝑡)
[first,last) 范围内的所有元素。
clear() 清空 set。
*/