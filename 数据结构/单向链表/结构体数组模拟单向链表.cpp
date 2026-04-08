//结构体数组实现单向静态链表
#include <iostream>
const int N = 10005;
struct Node {
	int data;       // 节点存储的值
	int nextid;   // 下一个节点的索引，-1表示空
}nodes[N];

int head, idx;    // 头指针和当前可用索引

//初始化
void init()
{
	head = -1;    // 链表为空
	idx = 0;      // 从0开始分配节点
}

//头插法
void add_to_haed(int x)
{
	nodes[idx].data = x;
	nodes[idx].nextid = head;  // 新节点指向原头节点
	head = idx;                // 头指针指向新节点
	idx++;
}

//在k节点后插入
void add(int k, int x) {
	nodes[idx].data = x;
	nodes[idx].nextid = nodes[k].nextid;  // 新节点指向k的下一个节点
	nodes[k].nextid = idx;                // k节点指向新节点
	idx++;
}

//删除k节点后的节点,注意特判尾节点
void remove(int k) {
	if (nodes[k].nextid == -1) return;  // k后面没有节点
	nodes[k].nextid = nodes[nodes[k].nextid].nextid;  // 跳过下一个节点
}


//遍历链表
void traverse() {
	std::cout << "Linked List: ";
	for (int i = head; i != -1; i = nodes[i].nextid) {
		std::cout << nodes[i].data << " ";
	}
	std::cout << std::endl;
}