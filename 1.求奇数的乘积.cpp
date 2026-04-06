#include <iostream>
#define eleType int
using namespace std;

struct SequentialList {
	eleType* elements;//这是一个数组
	int size;
	int capacity;
};

//初始化
void initailizeList(struct SequentialList* list, int capacity)
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
		list->elements == newelements;
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
	while (cin >> n)
	{
		struct SequentialList list;
		struct SequentialList* ptr = &list;
		initailizeList(ptr, n);
		int ans = 1;
		for (int i = 0; i < n; i++)
		{
			int x;
			cin >> x;
			insert(ptr, i, x);

		}
		for (int i = 0; i < n; i++)
		{
			if (getElement(ptr, i) % 2 == 1)
			{
				ans *= getElement(ptr, i);
			}
		}
		cout << ans << endl;

	}


	return 0;
}