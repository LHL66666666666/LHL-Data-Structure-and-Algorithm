//栈的修改与访问是按照后进先出的原则进行的，
//因此栈通常被称为是后进先出（last in first out）表，简称 LIFO 表。
//LIFO 表达的是 当前在容器 内最后进来的最先出去
const int N = 1e6 + 5;
int stack[N];
//size表示栈中元素个数，size=0表示空
//下标从0到size-1
int size = 0;
//判断空
bool isEmpty()
{
	return size == 0;
}
//入栈
void push(int x)
{
	stack[size++] = x;
}
//弹出
int  pop()
{
	return stack[--size];
}
//查询栈顶元素
int peek()
{
	return stack[size - 1];
}
//元素个数
int getsize()
{
	return size;
}