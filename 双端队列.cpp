/*
双端队列(deque)是指一个可以在队首/队尾插入或删除元素的队列。
相当于是栈与队列功能的结合。具体地，双端队列支持的操作有 4 个：

在队首插入一个元素
在队尾插入一个元素
在队首删除一个元素
在队尾删除一个元素
数组模拟双端队列的方式与普通队列相同。

同样地，也可以使用双栈模拟队列的思想来维护双端队列，
但需注意当某个栈为空时，交替查询队首和队尾将导致均摊分析失效。
考虑在移动时，只将非空栈的一半元素移动到空栈中，
并保持队首与队尾栈的性质，
这样处理后仍可以做到均摊常数时间的插入和删除。
*/
//使用循环队列的思想设计双端队列
//注意头部和尾部进出队列时移动方向是相反的
int deque[1000005];
int l, r, size, limit;
void init(int k)
{
	l = 0, r = 0, size = 0, limit = k;
}
//boolean insertFront()：将一个元素添加到双端队列头部。
//如果操作成功返回 true ，否则返回 false 
bool insertFront(int value) {
	if (isFull())
	{
		return false;
	}
	else if (isEmpty())
	{
		//可以将l，r都置为0
		l = 0, r = 0;
		deque[0] = value;
		size++;
		return true;
	}
	else 
	{
		//如果非空
		//l向左扩展
		l = (l - 1 + limit) % limit;
		deque[l] = value;
		size++;
		return true;
	}
}
//boolean insertLast() ：将一个元素添加到双端队列尾部。
//如果操作成功返回 true ，否则返回 false 。
bool insertLast(int value) {
	if (isFull())
	{
		return false;
	}
	else if (isEmpty())
	{
		l = 0, r = 0;
		deque[0] = value;
		size++;
		return true;
	}
	else
	{
		//r向右扩展
		r = (r + 1) % limit;
		deque[r] = value;
		size++;
		return true;
	}
}
//boolean deleteFront() ：从双端队列头部删除一个元素。 
//如果操作成功返回 true ，否则返回 false 。
bool deleteFront() {
	if (isEmpty())
	{
		return false;
	}
	else 
	{
		l = (l + 1) % limit;
		size--;
		return true;
	}
}
//boolean deleteLast() ：从双端队列尾部删除一个元素。
//如果操作成功返回 true ，否则返回 false 。
bool deleteLast() {
	if (isEmpty())
	{
		return false;
	}
	else
	{
		r = (r - 1 + limit) % limit;
		size--;
		return true;
	}
}
//int getFront() )：从双端队列头部获得一个元素。
//如果双端队列为空，返回 -1 。
int getFront() {
	if (isEmpty())
	{
		return -1;
	}
	else return deque[l];
}
//int getRear() ：获得双端队列的最后一个元素。
//如果双端队列为空，返回 -1 。
int getRear() {
	if (isEmpty())
	{
		return -1;
	}
	else return deque[r];
}

bool isEmpty() {
	return size == 0;
}

bool isFull() {
	return size == limit;
}