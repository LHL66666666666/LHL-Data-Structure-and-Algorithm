#include <iostream>
#include <cstdio>
using namespace std;
//链表包含数据域和指针域
typedef int Elemtype;
struct node {
	Elemtype data;
	//数据
	struct node* next;
	//指向下一个节点的指针
};
/*
int main() {
	//循环单向链表的构建
	int n, m;
	scanf("%d%d", &n, &m);
	//定义变量
	node* head, * p, * now, * prev;
	//分配第一个节点，数据置为1
	head = new node;
	head->data = 1;
	head->next = NULL;
	//当前指针是头
	now = head;
	for (int i = 2; i <= n; i++) {
		//p是新节点
		p = new node;
		p->data = i;
		p->next = NULL;
		//将申请的新节点连到前面的链表上
		now->next = p;
		//尾指针后移
		now = p;
	}
	//尾指针指向头,建立循环链表
	now->next = head;
	
}
*/
/*
单向循环链表
将链表的头尾连接起来，链表就变成了循环链表。由于链表首尾相连，
在插入数据时需要判断原链表是否为空：为空则自身循环，不为空则正常插入数据。

大致流程如下：

初始化待插入的数据 node；
判断给定链表 p 是否为空；
若为空，则将 node 的 next 指针和 p 都指向自己；
否则，将 node 的 next 指针指向 p 的下一个结点；
将 p 的 next 指针指向 node
*/
/*
//单向循环链表的插入
void insertNode(int i, Node* p) {
	Node* node = new Node;
	node->value = i;
	node->next = NULL;
	if (p == NULL) {
		p = node;
		node->next = node;
	}
	else {
		node->next = p->next;
		p->next = node;
	}
}
*/
/*
//非循环链表的实现,尾插法
int main()
{
	int n;
	cin >> n;
	node* head = new node;
	node* current = head;
	head->data = 1;
	head->next = NULL;
	current = head;
	for (int i = 2; i <= n; i++)
	{
		node* p = new node;
		p->data = i;
		p->next = NULL;
		current->next = p;
		current = p;
		//current相当于一个标志位置的指针，一直在移动
	}
}
*/
/*
//非循环链表的实现,头插法
int main()
{
	int n;
	cin >> n;
	node* head = nullptr;
	//NULL和nullptr都可以
	for (int i = 1; i <= n; i++)
	{
		node* p = new node;
		p->data = i;
		p->next = head;
		head = p;
	}
}
*/
/*
//向链表中插入（写入）数据，意思是在中间插入某个数据
//流程大致如下：
//初始化待插入的数据 node；
//将 node 的 next 指针指向 p 的下一个结点；
//将 p 的 next 指针指向 node
*/
struct Node {
	int value;
	Node* next;
};
//p 是指向当前位置的节点，新节点会插入在 p 的后面
void insertNode(int i, Node* p) {
	Node* node = new Node;
	node->value = i;
	//这里要注意一定先让新的插入的节点指向原节点的下一个，
	//再让原节点更新，否则新插入节点无法指向原节点的下一个
	node->next = p->next;
	p->next = node;
}

//单向链表的遍历
void traverse(Node* head)
{
	Node* current = head;
	while (current != nullptr)
	{
		cout << current->value;
		if (current->next != nullptr)
		{
			cout << "->";
		}
		current = current->next;
	}
	cout << "NULL" << endl;
}