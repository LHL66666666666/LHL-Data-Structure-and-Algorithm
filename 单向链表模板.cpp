#include <iostream>
#include <stdexcept>
using namespace std;
#define eleType int

//实现链表结点的结构体
struct ListNode {
	//链表存在两个域，数据域和指针域
	//指针域：next结点用next表示
	eleType data;
	struct ListNode* next;
	//构造函数,初始化链表
	ListNode(eleType x) : data(x), next(NULL) {}
};

//链表的类(声明)
class LinkedList {
private:
	ListNode* head;
	//链表头部的结点
	int size;
	//链表的大小
public:
	//公有方法，构造链表的函数
	LinkedList() : head(NULL), size(0) {}
	//析构函数
	~LinkedList();
	//元素的添加,在索引为i的位置添加值为value的元素
	void insert(int i, eleType value);
	//元素删除
	void remove(int i);
	//查找值为value的结点
	ListNode* find(eleType value);
	//获取特定索引的结点
	ListNode* get(int i);
	//改值（更新）索引为i的位置改为value的元素
	void update(int i, eleType value);
	//打印输出
	void printf();
};
//析构函数
LinkedList::~LinkedList() {
	//析构每一个结点的内存空间
	//从头结点开始
	ListNode* curr = head;
	while (curr !=NULL)  //当head非空时
	{
		//将当前节点存储在temp中
		ListNode* temp = curr;
		//将当前结点置为后继结点
		curr = curr->next;
		//将temp删除
		delete temp;
	}
}

//元素的插入
void LinkedList::insert(int i, eleType value)
{
	//首先判断下标是否合法
	if (i<0 || i>size)
	{
		throw std::out_of_range("Invalid position");
	}
	ListNode* newNode = new ListNode(value);
	if (i == 0)  //插入位置为链表的头结点
	{
		newNode->next = head;
		head = newNode;
	}
	else {
		//定义一个游标节点
		ListNode* curr = head;
		//再遍历
		for (int j = 0; j < i - 1; j++)
		{
			curr = curr->next;
			//让curr一直等于它的后继节点
			//直到curr到插入位置的前面一个位置
		}
	}
}


int main()
{


	return 0;
}