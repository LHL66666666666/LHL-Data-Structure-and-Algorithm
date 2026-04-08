#include <iostream>
#include <stdexcept>
using namespace std;
#define eleType int
//将元素类型定义为eleType

struct SequentialList {
	eleType* elements; //存储元素的数组 实际上就是int* elements
	int size; //元素个数
	int capacity; //实际容量
	//size<=capacity

};

//初始化
//要传指针
void initializeList(struct SequentialList* list, int capacity)
{
	list->elements = new eleType[capacity];
	list->size = 0;//表示一开始顺序表是空的
	list->capacity = capacity;
}

//销毁
void destroyList(struct SequentialList* list)
{
	delete[] list->elements;
	list = NULL;
}

//获取元素个数(顺序表大小)的接口
int size(struct SequentialList* list)
{
	return list->size;
}

//判断这个顺序表是否为空的接口
bool isEmpty(struct SequentialList* list)
{
	return list->size==0;
	//size为0为空
}

//顺序表的插入
void insert(struct SequentialList* list, int index, eleType element)
{
	//index表示插入的索引位置，element表示插入的元素
	//插入时可以插到最后一个位置，索引为list->size
	if (index<0 || index>list->size)
	{
		//如果下标非法，抛出异常
		throw std::invalid_argument("invalid index");
	}
	//判断容量capacity是否足够
	if (list->size == list->capacity)
	{
		//当size==capacity时，说明容量已经用完，需要扩容；
		int newCapacity = list->capacity * 2;
		//扩容两倍

		//创建新的数组
		eleType* newElements = new eleType[newCapacity];
		//把原来的元素赋值过来
		for (int i = 0; i < list->size; i++)
		{
			newElements[i] = list->elements[i];
		}
		//释放原来的内存
		delete[] list->elements;
		list->elements = newElements;  
		list->capacity = newCapacity;  //扩容成功
	}

	//插入操作：无论是否扩容，都需要执行以下代码
	//插入新元素,从后往前遍历
	for (int i = list->size; i > index; i--)
	{
		//把当前元素往后挪
		list->elements[i] = list->elements[i - 1];
	}
	list->elements[index] = element;
	list->size++;  //别忘记改变元素的数量
}

//顺序表的元素删除
void deleteElement(struct SequentialList* list,int index)
{
	//删除时不存在索引为list->size的元素
	if (index<0 || index>=list->size)
	{
		//如果下标非法，抛出异常
		throw std::invalid_argument("invalid index");
	}
	for (int i = index; i <= list->size-2; i++)
	{
		list->elements[i] = list->elements[i + 1];
		//原来index位置上的元素被覆盖掉了
	}
	list->size--;  //别忘记改变元素的数量

}

//元素的查找
int findElement(struct SequentialList* list, eleType element)
{
	//返回索引
	for (int i = 0; i < list->size; i++)
	{
		if (element == list->elements[i])
		{
			return i;
		}
	}
	return -1;
	//-1表示未查找到
}

//元素索引(获取第index个元素)
eleType getElement(struct SequentialList* list,int index)
{
	//找索引时不存在索引为list->size的元素
	if (index < 0 || index >= list->size)
	{
		//如果下标非法，抛出异常
		throw std::invalid_argument("invalid index");
	}
	return list->elements[index];
}

//元素修改
void updateElement(struct SequentialList* list, int index, eleType value)
{
	//找索引时不存在索引为list->size的元素
	if (index < 0 || index >= list->size)
	{
		//如果下标非法，抛出异常
		throw std::invalid_argument("invalid index");
	}
	list->elements[index] = value;



}

int main()
{
	struct SequentialList list1;
	struct SequentialList* ptr = &list1;
	initializeList(ptr, 10);
	for (int i = 0; i < 10; i++)
	{
		insert(ptr, i, i * 10);
	}
	cout << "size:" << size(ptr) << endl;
	cout << "isEmpty:" << isEmpty(ptr) << endl;

	//获取每个索引的元素
	for (int i = 0; i < ptr->size; i++)
	{
		cout << getElement(ptr,i) << ' ';
	}
	cout << endl;

	//删除元素
	deleteElement(ptr, 5);
	updateElement(ptr, 1, 666);
	cout << "size:" << size(ptr) << endl;
	for (int i = 0; i < ptr->size; i++)
	{
		cout << getElement(ptr, i) << ' ';
	}
	cout << endl;

	//元素查找
	cout << findElement(ptr, 20) << endl;

	//增加一个元素
	insert(ptr,  1 ,10101);
	cout << "size:" << size(ptr) << endl;
	for (int i = 0; i < ptr->size; i++)
	{
		cout << getElement(ptr, i) << ' ';
	}

	//删除
	destroyList(ptr);

	return 0;
}