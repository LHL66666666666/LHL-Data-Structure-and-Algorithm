//使用静态数组存储二叉树
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 1e5 + 5;
struct Node {
	char value;
	int lson, rson;		//左右孩子
}tree[N];
int index = 1;
//一般用0来表示空节点
int newNode(char val)
{
	//tree[0]不用，表示空节点
	tree[index].value = val;
	tree[index].lson = 0;
	tree[index].rson = 0;
	return index++;
}
//插入孩子节点
void insert(int& father, int child, int l_r)
{
	if (l_r == 0)
	{
		tree[father].lson = child;
		//左孩子  
	}
	else 
	{
		tree[father].rson = child;
		//右孩子
	}
}
int dfn[N] = { 0 };
//dfn[i]表示节点i的时间戳
//这里时间戳表示节点第一次被访问的时间戳
int dfn_timer = 0;
//打印时间戳
//时间戳打印的结果就是下面的“先序输出”
void dfn_order(int father) 
{
	if (father != 0)
	{
		dfn[father] = ++dfn_timer;
		//打印输出时间戳
		printf("dfn[%c]=%d\n",tree[father].value,dfn[father]);
		//递归调用左孩子和右孩子
		dfn_order(tree[father].lson);
		dfn_order(tree[father].rson);
	}
}
//DFS序。在递归时每个节点来回处理两次，即第1次访问（前进）和第2次回溯（回退）
/*
visit order（）函数打印出了DFS序{E B A A D C C D B G F F I H H I G E}。
这个序列有一个重要特征：每个节点出现两次，
被这两次包围起来的是以它为父节点的一棵子树。
例如，序列中的{B A A D C C D B}就是以B为父节点的一棵子树；
又如{I H H I},是以I为父节点的一棵子树。这个特征是递归操作产生的。
*/
int visit_timer = 0;
void visit_order(int father)
{
	if (father != 0)
	{
		//打印输出dfs序，第1次访问节点
		printf("visit[%c]=%d\n",tree[father].value,++visit_timer);
		//递归遍历左右孩子
		visit_order(tree[father].lson);
		visit_order(tree[father].rson);
		//打印输出dfs序，第2次回溯
		printf("visit[%c]=%d\n", tree[father].value, ++visit_timer);
	}
}


/*
树的深度。从根节点向子树DFS，每个节点第1次被访问时，深度加1；
从这个节点回溯时，深度减1。用deep[i]表示节点i的深度,
deep node（）函数打印出了深度：
deep[E] =1; deep[B] =2; deep[A] =3; deep[D] =3; deep[C] =4;
deep[G] =2; deep[F] =3; deep[I] =3; deep[H] =4
*/
int deep[N] = { 0 };	//deep[i]表示节点i的深度
int deep_timer = 0;
void deep_node(int father)
{
	if (father != 0)
	{
		deep[father] = ++deep_timer;
		//打印输出树的深度，第1次访问该节点时，深度+1
		printf("deep[%c]=%d\n",tree[father].value,deep[father]);
		//递归调用
		deep_node(tree[father].lson);
		deep_node(tree[father].rson);
		//回溯，深度-1
		deep_timer--;
	}
}

/*
子树节点总数。用num[i]表示以i为父亲的子树上的节点总数。
例如，以B为父节点的子树共有4个节点{A B C D}。只需要一次简单的DFS就能完成，
每棵子树节点的数量等于它的两个子树的数量相加，再加1，即加它自己。
num node（）函数做了计算并打印出了以每个节点为父亲的子树上的节点数量。
*/
int num[N] = { 0 };
int num_node(int father)
{
	if (father == 0)
	{
		return 0;
		//father=0意味着递归到了树的叶子
		//向下不再有节点
	}
	else
	{
		num[father] = num_node(tree[father].lson) + num_node(tree[father].rson) + 1;
		//递归调用
		printf("num[%c]=%d\n",tree[father].value,num[father]);
		//打印输出子树节点总数(包括自己)
		return num[father];
	}
}

/*
先序输出。
preorder（）函数按父节点、左子节点、右子节点的顺序打印，
输出{E B A D C G F I H}.
*/
void preorder(int father)
{
	if (father != 0)
	{
		std::cout << tree[father].value << ' ';
		preorder(tree[father].lson);
		preorder(tree[father].rson);
	}
}

/*
中序输出。
inorder（）函数按左子节点、父节点、右子节点的顺序打印，
输出{A B C D E F G H I}.
*/
void inorder(int father)
{
	if (father != 0)
	{
		inorder(tree[father].lson);
		std::cout << tree[father].value << ' ';
		inorder(tree[father].rson);
	}
}

/*
后序输出。
postorder（）函数按左子节点、右子节点、父节点的顺序打印，
输出{A C D B F H I G E}.
*/
void postorder(int father)
{
	if (father != 0)
	{
		postorder(tree[father].lson);
		postorder(tree[father].rson);
		std::cout << tree[father].value << ' ';
	}
}
/*
提示	如果已知树的先序、中序、后序，可以确定一棵树。
“先序+中序”或“后序+中序”都能确定一棵树，但是“先序+后序”不能确定一棵树
*/

//建立一颗树
int buildtree()
{
	int A = newNode('A'); int B = newNode('B'); int C = newNode('C');//定义节点
	int D = newNode('D'); int E = newNode('E'); int F = newNode('F');
	int G = newNode('G'); int H = newNode('H'); int I = newNode('I');
	//0代表左孩子，1代表右孩子
	insert(E, B, 0); insert(E, G, 1);	//建树.E的左孩子是B,右孩子是G
	insert(B, A, 0); insert(B, D, 1); 
	insert(G, F, 0); insert(G, I, 1);
	insert(D, C, 0); insert(I, H, 0);
	int root = E;
	return root;
}
int main() {
	int root = buildtree();
	cout << "dfn order:"; dfn_order(root); cout << endl;	//打印时间戳
	cout << "visit order:"; visit_order(root); cout << endl;	//打印DFS序
	cout << "deep order:"; deep_node(root); cout << endl;	//打印节点深度
	cout << "num of tree:"; num_node(root); cout << endl;	//打印子树上的节点数
	cout << "in order:"; inorder(root); cout << endl;	//打印中序序列
	cout << "pre order:"; preorder(root); cout << endl;	//打印先序序列
	cout << "post order:"; postorder(root); cout << endl;	//打印后序序列
	return 0;
}
// 分析DFS遍历二叉树的复杂度，和BFS差不多，
// 时间复杂度为O(n)，空间复杂度为O(n)，因为使用了长度为n的递归栈。

//DFS框架
