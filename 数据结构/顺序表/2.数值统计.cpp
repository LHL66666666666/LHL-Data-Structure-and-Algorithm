#include <iostream>
using namespace std;

//进行优化，因为输入的不只有正数，还有浮点数
#define eleType double





struct SequentialList {
	eleType* elements;//这是一个数组
	int size;
	int capacity;
};

//初始化
void initializeList(struct SequentialList* list, int capacity)
{
	//eleType是数据类型
	list->elements = new eleType[capacity];
	list->capacity = capacity;
	list->size = 0;
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
	return list->size == 0;
}

//顺序表的插入
void insert(struct SequentialList* list, int index, eleType element)
{
	//判断索引是否合法
	if (index<0 || index>list->size)
	{
		throw std::invalid_argument("invalid index");
	}
	//判断容量够不够
	if (list->size == list->capacity)
	{
		int newcapacity = list->capacity * 2;
		//在堆区开新的空间
		eleType* newelements = new eleType[newcapacity];  //创建数组
		//转移
		for (int i = 0; i < list->size; i++)
		{
			newelements[i] = list->elements[i];
		}
		//释放
		delete[] list->elements;
		list->elements = newelements;
		list->capacity = newcapacity;
	}
	//插入
	for (int i = list->size; i > index; i--)
	{
		list->elements[i] = list->elements[i - 1];
	}
	list->elements[index] = element;
	list->size++;
}

//顺序表的元素删除
void deleteElement(struct SequentialList* list, int index)
{
	//判断索引是否合法
	if (index < 0 || index >= list->size)
	{
		throw std::invalid_argument("invalid index");
	}
	for (int i = index; i < list->size - 1; i++)
	{
		list->elements[i] = list->elements[i + 1];
	}
	list->size--;
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
eleType getElement(struct SequentialList* list, int index)
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
	int n;
	//n=0时跳出循环
	while (cin >> n && n)
	{
		struct SequentialList list;
		struct SequentialList* ptr = &list;
		initializeList(ptr, 1);
		int count1 = 0, count2 = 0, count3 = 0;
		for (int i = 0; i < n; i++)
		{
			eleType x;
			cin >> x;
			insert(ptr, i, x);
		}
		for (int i = 0; i < ptr->size; i++)
		{
			if (getElement(ptr, i) > 1e-8)
			{
				count3++;
			}
			else if (getElement(ptr, i) < -1e-8)
			{
				count1++;
			}
			else count2++;
		}
		cout << count1 << ' ' << count2 << ' ' << count3 << endl;
		destroyList(ptr);
	}

	return 0;
}

//统计给定的n个数中，负数、零和正数的个数。
//输入数据有多组，每组占一行，
//每行的第一个数是整数n（n<100），表示需要统计的数值的个数，然后是n个实数；
//如果n=0，则表示输入结束，该行不做处理。