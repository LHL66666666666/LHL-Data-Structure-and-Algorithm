#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> ret;
	//ret就是一个空的顺序表,初始化为0
	//获取元素数量
	cout << ret.size() << endl;
	//插入(依次插入到顺序表的尾部)
	ret.push_back(1024);
	cout << ret.size() << endl;
	//查找
	cout << ret[0] << endl;

	vector<int> ret2 = { 1,2,3,4,5 };
	for (int i = 0; i < ret2.size(); i++)
	{
		cout << ret2[i] << endl;
	}

}