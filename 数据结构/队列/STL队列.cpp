//C++ 在 STL 中提供了一个容器 std::queue，使用前需要先引入 <queue> 头文件。
/*
STL 中对 queue 的定义
// clang-format off
template<
    class T,
    class Container = std::deque<T>
> class queue;

T 为 queue 中要存储的数据类型。

Container 为用于存储元素的底层容器类型。这个容器必须提供通常语义的下列函数：

back()
front()
push_back()
pop_front()
STL 容器 std::deque 和 std::list 满足这些要求。
如果不指定，则默认使用 std::deque 作为底层容器。
*/
/*
STL 中的 queue 容器提供了一众成员函数以供调用。其中较为常用的有：

元素访问
q.front() 返回队首元素
q.back() 返回队尾元素
修改
q.push() 在队尾插入元素
q.pop() 弹出队首元素
容量
q.empty() 队列是否为空
q.size() 返回队列中元素的数量
此外，queue 还提供了一些运算符。较为常用的是使用赋值运算符 = 为 queue 赋值，示例
*/
#include <queue>
using namespace std;
std::queue<int> q1, q2;

// 向 q1 的队尾插入 1
q1.push(1);

// 将 q1 赋值给 q2
q2 = q1;

// 输出 q2 的队首元素
std::cout << q2.front() << std::endl;
// 输出: 1