//一维数组模拟实现单向链表
#include <iostream>
using namespace std;
const int N = 100005;
//静态全局数组
int head, e[N], ne[N], idx;

/*
head: 头指针，存储链表第一个节点的索引

e[N]: 值数组，e[i] 存储索引为 i 的节点的值

ne[N]: 下一个指针数组，ne[i] 存储索引为 i 的节点的下一个节点索引

idx: 当前可用的节点索引,idx是一直递增的
*/

//初始化
void init() 
{
	head = -1;  //空链表，头指针-1
	//链表的最后一个元素指向-1
	idx = 0;  //从0索引开始分配节点
}

//头插法,要插入的值为x
void add_to_head(int x)
{
	e[idx] = x;      // 步骤1：在idx位置存储值x
	ne[idx] = head;  // 步骤2：新节点的next指向原头节点,这里的head是上一次的head
	head = idx;      // 步骤3：头指针指向新节点
	idx++;           // 步骤4：idx移动到下一个可用位置
}

//在k后插入
void add(int k,int x)
{
	e[idx] = x;         // 步骤1：在idx位置存储值x
	ne[idx] = ne[k];    // 步骤2：新节点指向k节点的下一个节点
	ne[k] = idx;        // 步骤3：k节点指向新节点
	idx++;              // 步骤4：idx移动到下一个可用位置
}

//删除,这里删除指的是删除第k个节点的下一个节点
void remove(int k)
{
	//特判k是最后一个节点，即尾节点
	if (ne[k] == -1) return;  // 如果k后面没有节点，直接返回
	ne[k] = ne[ne[k]];  // 让k节点直接指向k的下下个节点
	//也就是说我们直接跳过了k的下一个节点
}
//注意特判k是头节点的情况，头节点需要特殊处理
void removehead() 
{
	head = ne[head];
}

//遍历
void print() 
{
	//i=-1时标志着到达尾节点
	for (int i = head; i != -1; i = ne[i])
	{
		cout << e[i] << ' ';
	}
	cout << endl;
}

//模拟执行
int main() {
	init();                    // head=-1, idx=0

	add_to_head(1);           // 链表：1
	add_to_head(2);           // 链表：2→1  
	add_to_head(3);           // 链表：3→2→1
	print();                  // 输出：3 2 1

	add(head, 4);             // 链表：3→4→2→1
	print();                  // 输出：3 4 2 1

	remove(head);             // 链表：3→2→1
	print();                  // 输出：3 2 1

	return 0;
}

//如果要实现约瑟夫问题,构建循环链表
int e1[N], ne1[N], idx1;
void build_circle(int n)
{
	idx1 = 0;
	for (int i = 1; i <= n; i++)
	{
		e1[idx1] = i;
		if (idx1 > 0)
		{
			ne1[idx1 - 1] = idx1;   //前一个指向当前
		}  
		idx1++;
	}
	//最后实现循环
	ne1[idx1 - 1] = 0;  // 最后一个指向第一个，形成环
}
void solve() 
{
	int n, m;
	cin >> n >> m;
	int cnt = 1, sum = n;
	int now = 0, prev = idx1 - 1;
	while (sum > 0)
	{
		//计数m-1次
		for (int i = 1; i < m; i++)
		{
			prev = now;
			now = ne1[now];
		}
		cout << e1[now] << ' ';
		//删除节点now
		ne1[prev] = ne1[now];
		now = ne1[now];
		sum--;
	}
}
/*
关键点说明
prev 的作用：记录前一个节点，用于删除当前节点时重新链接

数 m - 1 次的原因：因为要从当前节点开始数，数到第 m 个时，
current 正好指向要淘汰的人

删除操作：ne[prev] = ne[current] 跳过当前节点

current 移动：删除后 current 移动到下一个节点，继续游戏
*/