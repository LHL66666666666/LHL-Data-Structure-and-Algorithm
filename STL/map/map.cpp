/*
map 是有序键值对容器，它的元素的键是唯一的。搜索、移除和插入操作拥有对数复杂度。map 通常实现为 红黑树。
设想如下场景：现在需要存储一些键值对，例如存储学生姓名对应的分数：
Tom 0，Bob 100，Alan 100。但是由于数组下标只能为非负整数，
所以无法用姓名作为下标来存储，这个时候最简单的办法就是使用 STL 中的 map。
map 重载了 operator[]，可以用任意定义了 operator < 的类型作为下标（在 map 中叫做 key，也就是索引）：
map<Key, T> yourMap;
其中，Key 是键的类型，T 是值的类型，下面是使用 map 的实例：
map<string, int> mp;
map 中不会存在键相同的元素，multimap 中允许多个元素拥有同一键。multimap 的使用方法与 map 的使用方法基本相同。
*/
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    // 1. 创建和初始化 map
    map<string, int> studentScores;

    // 2. 插入操作的多种方式
    cout << "=== 插入操作 ===" << endl;

    // 方式1: 使用下标操作符
    studentScores["Alice"] = 95;
    studentScores["Bob"] = 87;
    studentScores["Charlie"] = 92;

    // 方式2: 使用 insert 函数和 pair
    studentScores.insert(pair<string, int>("David", 88));

    // 方式3: 使用 make_pair
    studentScores.insert(make_pair("Eve", 91));

    // 方式4: 使用 emplace (C++11)
    studentScores.emplace("Frank", 85);

    // 3. 遍历和显示元素
    cout << "学生成绩列表:" << endl;
    for (const auto& pair : studentScores) {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << endl;

    // 4. 查询操作
    cout << "=== 查询操作 ===" << endl;

    // 使用 find() 安全查询
    auto it = studentScores.find("Alice");
    if (it != studentScores.end()) {
        cout << "找到 Alice，成绩为: " << it->second << endl;
    }
    else {
        cout << "未找到 Alice" << endl;
    }

    // 使用 count() 检查元素是否存在
    if (studentScores.count("Bob") > 0) {
        cout << "Bob 存在于 map 中" << endl;
    }

    // 危险的下标访问（会自动插入不存在的元素）
    cout << "Grace 的成绩: " << studentScores["Grace"] << endl;
    cout << "现在 map 大小: " << studentScores.size() << endl;

    // 5. 边界查询
    cout << "\n=== 边界查询 ===" << endl;

    // 添加一些测试数据
    studentScores["Andy"] = 78;
    studentScores["Brian"] = 82;
    studentScores["Cathy"] = 90;

    // lower_bound 和 upper_bound
    auto lb = studentScores.lower_bound("B");
    auto ub = studentScores.upper_bound("C");

    cout << "名字在 B 到 C 之间的学生:" << endl;
    for (auto it = lb; it != ub; ++it) {
        cout << it->first << ": " << it->second << endl;
    }

    // 6. 删除操作
    cout << "\n=== 删除操作 ===" << endl;

    // 删除指定键的元素
    size_t deleted = studentScores.erase("David");
    cout << "删除了 " << deleted << " 个 David 的记录" << endl;

    // 通过迭代器删除
    auto deleteIt = studentScores.find("Eve");
    if (deleteIt != studentScores.end()) {
        studentScores.erase(deleteIt);
        cout << "删除了 Eve 的记录" << endl;
    }

    // 删除一个范围内的元素
    auto first = studentScores.find("Bob");
    auto last = studentScores.find("Charlie");
    if (first != studentScores.end() && last != studentScores.end()) {
        studentScores.erase(first, ++last); // 删除 [Bob, Charlie] 区间
        cout << "删除了 Bob 到 Charlie 之间的记录" << endl;
    }

    cout << "删除后的学生成绩列表:" << endl;
    for (const auto& pair : studentScores) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 7. 其他实用操作
    cout << "\n=== 其他操作 ===" << endl;

    cout << "map 是否为空: " << (studentScores.empty() ? "是" : "否") << endl;
    cout << "map 中元素数量: " << studentScores.size() << endl;

    // 清空 map
    studentScores.clear();
    cout << "清空后 map 是否为空: " << (studentScores.empty() ? "是" : "否") << endl;
    cout << "清空后元素数量: " << studentScores.size() << endl;

    // 8. 复杂类型示例
    cout << "\n=== 复杂类型示例 ===" << endl;

    map<int, string> employeeMap;
    employeeMap[101] = "张三";
    employeeMap[102] = "李四";
    employeeMap[103] = "王五";

    cout << "员工列表:" << endl;
    for (const auto& emp : employeeMap) {
        cout << "工号 " << emp.first << ": " << emp.second << endl;
    }

    return 0;
}