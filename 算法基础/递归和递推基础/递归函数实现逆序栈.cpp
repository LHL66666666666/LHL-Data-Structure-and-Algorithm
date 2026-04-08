//使用递归函数实现一个栈中元素的逆序
//原地修改
#include <stack>
using namespace std;
//子函数，作用是将栈底元素返回，并且使栈中所有元素整体向下移1单位
int bottomout(stack<int> stk)
{
	int ans = stk.top();
	stk.pop();
	if (stk.empty())
	{
		return ans;
	}
	else {
		int last = bottomout(stk);
		stk.push(ans);
		return last;
	}
}
void reverse(stack<int> stk)
{
	if (stk.empty())
	{
		return;
	}
	//栈底部的元素，在递归最外层，因此在push的时候最后被push进去
	//这样就实现了reverse
	int num = bottomout(stk);
	reverse(stk);
	stk.push(num);
}