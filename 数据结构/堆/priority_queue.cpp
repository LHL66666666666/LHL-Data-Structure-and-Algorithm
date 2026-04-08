/*
priority_queue 是C++标准库中的优先队列容器，
它实际上是一个堆数据结构。
默认情况下是一个大根堆（最大堆）。
*/
//头文件和定义
#include <queue>
#include <vector>  // 需要包含，因为priority_queue使用vector作为底层容器
// 基本定义
std::priority_queue<int> pq;  // 默认大根堆
// 完整定义
std::priority_queue<T, Container, Compare>

//构造函数
// 1. 默认构造
std::priority_queue<int> pq1;
// 2. 使用比较函数构造
std::priority_queue<int, std::vector<int>, std::greater<int>> pq2;  // 小根堆
// 3. 从已有容器构造
std::vector<int> vec = { 3, 1, 4, 1, 5 };
std::priority_queue<int> pq3(vec.begin(), vec.end());

//常用成员函数
std::priority_queue<int> pq;
// 插入元素
pq.push(10);
pq.push(5);
pq.push(20);
// 访问堆顶元素（最大/最小元素）
int top = pq.top();  // 返回20（大根堆）
// 删除堆顶元素
pq.pop();
// 检查是否为空
bool isEmpty = pq.empty();
// 获取元素个数
int size = pq.size();

//大根堆 vs 小根堆
#include <functional>  // 需要包含这个头文件使用std::greater
// 大根堆（默认）- 堆顶是最大值
std::priority_queue<int> maxHeap;
// 等价于：
std::priority_queue<int, std::vector<int>, std::less<int>> maxHeap;
// 小根堆 - 堆顶是最小值
std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

//自定义比较函数
// 方法1：使用函数对象
struct Compare {
    bool operator()(int a, int b) {
        return a > b;  // 小根堆
        // return a < b;  // 大根堆
    }
};
std::priority_queue<int, std::vector<int>, Compare> pq;
// 方法2：使用lambda表达式（C++11以上）
auto cmp = [](int left, int right) { return left > right; };
std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

//9. 重要注意事项
//访问前检查空队列：在调用 top() 或 pop() 前要检查队列是否为空
//
//底层容器：默认使用 vector，也可以使用 deque
//
//时间复杂度：
//
//push() : O(log n)
//
//pop() : O(log n)
//
//top() : O(1)
//
//不支持随机访问：只能访问堆顶元素
//
//这种数据结构在解决区间调度、Dijkstra算法、Huffman编码等问题中非常有用。