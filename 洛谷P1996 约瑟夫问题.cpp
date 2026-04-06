#include <iostream>
using namespace std;
struct Node {
	int value;
	Node* next;
};
int main() {
	int n, m;
	cin >> n >> m;
	Node* head = new Node;
	head->value = 1;
	head->next = NULL;
	Node* cur = head;
	for (int i = 2; i <= n; i++)
	{
		Node* p = new Node;
		p->value = i;
		p->next = NULL;
		cur->next = p;
		cur = p;
	}
	//循环起来
	cur->next = head;
	//下面实现删除
	Node* prev = head;
	//这边别忘记把cur变成头结点
	cur = head;
	//从头开始数
	while ((n--) > 1)
	{
		for (int i = 1; i < m; i++)
		{
			prev = cur;
			cur = cur->next;
			//数m次停下，这时cur指向第m个
		}
		//输出
		cout << cur->value << ' ';
		//然后删除第m个
		prev->next = cur->next;
		delete cur;
		cur = prev->next;
	}
	//循环结束时n=1
	//输出最后一个
	cout << prev->value;
	delete prev;


	return 0;
}