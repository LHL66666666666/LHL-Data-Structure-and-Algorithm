//每一个线段都有start和end两个数据项，表示这条线段在X轴上从start位置开始到end位置结束。
//给定一批线段，求所有重合区域中最多重合了几个线段，首尾相接的线段不算重合。
//例如：线段[1, 2]和线段[2.3]不重合。
//线段[1, 3]和线段[2, 3]重合
//输入描述：
//第一行一个数N，表示有N条线段
//接下来N行每行2个数，表示线段起始和终止位置
//输出描述：
//输出一个数，表示同一个位置最多重合多少条线段
//思考：可以用差分
//注意到重合区域的左边界一定是某一区间的左边界
//重合区域的右边界一定是某个区间的右边界
#include <iostream>
#include <algorithm>
//using namespace std;
int max(int x, int y)
{
	return x > y ? x : y;
}
struct node {
	int l, r;
}a[10005];
bool cmp(node x, node y)
{
	return x.l < y.l;
}
//手写堆练习一下模板
int heap[10005];
int size;
//向上建堆，本题需要的是小根堆
void heapup(int val)
{
	heap[size] = val;
	int idx = size++;
	//传参是插入堆的索引
	while (heap[idx] < heap[(idx - 1) / 2])
	{
		//交换
		int tmp = heap[idx];
		heap[idx] = heap[(idx - 1) / 2];
		heap[(idx - 1) / 2] = tmp;
		idx = (idx - 1) / 2;
	}
}
//向下建堆
void heapdown(int idx)
{
	//记录左孩子的位置
	int l = 2 * idx + 1;
	//右孩子是l+1
	while (l<size)
	{
		//先找出best，即左右孩子中最小的那个
		int best;
		if (l + 1 < size && heap[l + 1] < heap[l])
		{
			//存在右孩子且右孩子更小，此时best是右孩子索引
			best = l + 1;
		}
		else best = l;
		// 如果当前节点已经小于等于最小的孩子，调整结束
		if (heap[idx] <= heap[best]) {
			break;
		}
		else {
			int tmp = heap[idx];
			heap[idx] = heap[best];
			heap[best] = tmp;
			idx = best;
			l = 2 * idx + 1;
		}
	}
}
//弹出堆顶的元素
//类似于堆排序的思路，将堆进行重构
void heapdelete()
{
	//思路就是先将要出堆的元素交换到末位置，再将size-1
	//再将堆重构
	int tmp = heap[0];
	heap[0] = heap[size - 1];
	heap[size - 1] = tmp;
	size--;
	heapdown(0); 
}
//向堆中添加元素
int main() {
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; i++)
	{
		std::cin >> a[i].l >> a[i].r;
	}
	//我们按照左端点从小到大进行排序
	//右端点暂时不考虑
	std::sort(a + 1, a + 1 + n, cmp);
	int ans = 0;
	//现在来比较新加入的左端点与堆中最小右端点的大小关系
	for (int i = 1; i <= n; i++)
	{
		while (size > 0 && heap[0] <= a[i].l)
		{
			heapdelete();
		}
		heapup(a[i].r);
		ans = max(ans, size);
	}
	std::cout << ans << std::endl;


	return 0;
}
//这种方法利用了优先队列（堆）来高效地维护当前重叠的线段集合，
//是解决这类区间重叠问题的经典方法。
//使用STL：priority_queue
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

struct node {
	int l, r;
};

bool cmp(node x, node y) {
	return x.l < y.l;
}

int main() {
	int n;
	std::cin >> n;

	std::vector<node> a(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a[i].l >> a[i].r;
	}

	// 按照左端点从小到大进行排序
	std::sort(a.begin(), a.end(), cmp);

	// 小根堆，存储线段的右端点
	std::priority_queue<int, std::vector<int>, std::greater<int>> heap;

	int ans = 0;

	for (int i = 0; i < n; i++) {
		// 移除所有右端点 <= 当前线段左端点的线段（不重叠的线段）
		while (!heap.empty() && heap.top() <= a[i].l) {
			heap.pop();
		}

		// 将当前线段的右端点加入堆中
		heap.push(a[i].r);

		// 更新最大重叠数
		ans = std::max(ans, (int)heap.size());
	}

	std::cout << ans << std::endl;

	return 0;
}