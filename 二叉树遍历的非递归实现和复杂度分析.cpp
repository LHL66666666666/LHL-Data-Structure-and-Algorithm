#include <iostream>
#include <stack>
using namespace std;
int main() {
    // 用数组模拟二叉树：[1,2,3,4,5,6]
    int tree[] = { 1, 2, 3, 4, 5, 6 };

    stack<int> stk;  // 存储数组索引
    stk.push(0);     // 根节点索引0入栈

    cout << "先序遍历结果: ";

    while (!stk.empty()) {
        int index = stk.top();
        stk.pop();
        cout << tree[index] << " ";

        // 计算左右孩子索引（完全二叉树的索引关系）
        int right_index = 2 * index + 2;
        int left_index = 2 * index + 1;

        // 先右后左入栈
        if (right_index < 6) {  // 6是数组长度
            stk.push(right_index);
        }
        if (left_index < 6) {
            stk.push(left_index);
        }
    }

    cout << endl;
    return 0;
}


#include <iostream>
#include <stack>
using namespace std;

const int N = 1e5 + 5;

struct Node {
    int val;
    int lson, rson;  // 左右孩子的索引
} tree[N];

int index = 1;  // 当前可用的节点索引

//先序遍历，非递归版
//思路：先将头节点入栈，每次弹出一个节点，先压右再压左
//展示后进先出，先序是父节点，左孩子，右孩子
void preOrder(int root)
{
    if (root == 0)
    {
        //空节点
        return;
    }
    stack<int> stk;     //存储节点索引
    stk.push(root);     //头节点压入栈
    while (!stk.empty())
    {
        int current = stk.top();
        /*
        current 只是当前节点的"快照"，用于获取该节点的左右孩子

        修改current不会影响栈中的实际节点

        每个循环的current都是独立的，互不影响
        */
        //如果非空的话
        //先弹出栈顶元素(头节点)
        stk.pop();
        cout << tree[current].val << ' ';     //输出头节点
        //先将右侧压入栈
        if (tree[current].rson != 0)
        {
            stk.push(tree[current].rson);
        }
        //再压左侧
        if (tree[current].lson != 0)
        {
            stk.push(tree[current].lson);
        }
    }
    cout << '\n';
}

//中序遍历
//顺序是左节点，父节点，右节点
//流程：1.遍历到某一子树，先头节点进栈，再将他的左边界进栈直到左边界遍历完
//2.从栈里弹出节点，节点的右子树重复1
//3. 直到没有子树且栈为空
// 中序遍历，非递归版
void inOrder(int root) {
    if (root == 0) return;  // 空节点

    stack<int> stk;
    int current = root;

    cout << "中序遍历结果: ";

    while (current != 0 || !stk.empty()) {
        // 1. 遍历到某一子树，先头节点进栈，再将左边界进栈直到左边界遍历完
        if (current != 0) {
            stk.push(current);
            current = tree[current].lson;  // 一直往左走
        }
        // 2. 从栈里弹出节点，节点的右子树重复1
        else {
            //这里很关键，当current是0也就是为空时，
            //将current赋值为栈顶的元素
            current = stk.top();
            stk.pop();
            cout << tree[current].val << " ";  // 访问当前节点

            current = tree[current].rson;  // 转向右子树
        }
    }
    cout << endl;
}

//后序遍历 两个栈实现，空间复杂度较高
//左子节点、右子节点、父节点的顺序
//使用两个栈的方法
//我们先序遍历是中，左，右
//我们在先序遍历中改变压入栈的顺序，先压入左，再压入右，就变成了
//中，右，左的输出顺序，我们在应该输出的位置不输出，
//将元素压入一个新的栈，按照栈的后进先出，
//就变为了左，右，中的输出顺序，这与后序相同
void posOrder2stacks(int root)
{
    if (root == 0)
    {
        return;
    }
    stack<int> stk1;
    stack<int> stk2;
    stk1.push(root);
    while (!stk1.empty())
    {
        int current = stk1.top();
        stk2.push(current);
        //先输出
        stk1.pop();
        //cout << tree[current].val << ' ';
        //此时弹出时先不输出，压入stk2
        //变顺序的先序，先压左
        if (tree[current].lson != 0)
        {
            stk1.push(tree[current].lson);
        }
        if (tree[current].rson != 0)
        {
            stk1.push(tree[current].rson);
        }
    }
    //循环结束后依次弹出stk2中的元素
    while (!stk2.empty())
    {
        int value = stk2.top();
        cout << tree[value].val << ' ';
        stk2.pop();
    }
    cout << endl;
}

//后序遍历 使用一个栈
//左子节点、右子节点、父节点的顺序
//引入一个概念：上次打印输出的节点
void posOrder1stack(int root)
{
    if (root == 0)
    {
        return;
    }
    int h = 0;  // 上一次打印的节点索引，初始为0表示没有打印过
    //维护一个变量h，如果始终没有打印过头节点，那么h就是头节点
    //一旦打印过节点，h就变为了打印的节点
    //之后h的含义就是：上一次打印的节点
    stack<int> stk;
    stk.push(root);
    while (!stk.empty()) {
        int cur = stk.top();  // 查看栈顶，但不弹出

        if (tree[cur].lson != 0 && h != tree[cur].lson && h != tree[cur].rson) {
            // 有左孩子且左孩子没处理过
            stk.push(tree[cur].lson);
        }
        else if (tree[cur].rson != 0 && h != tree[cur].rson) {
            // 有右孩子且右孩子没处理过
            stk.push(tree[cur].rson);
        }
        else {
            // 左右孩子都处理过了，或者没有孩子
            cout << tree[cur].val << " ";
            h = cur;  // 记录本次打印的节点
            stk.pop();
        }
    }
    cout << endl;
}


int main() {
    // 创建测试二叉树
    //     1
    //    / \
    //   2   3
    //  / \   \
    // 4   5   6

    // 构建节点
    tree[1] = { 1, 2, 3 };  // 节点1，左孩子是2，右孩子是3
    tree[2] = { 2, 4, 5 };  // 节点2，左孩子是4，右孩子是5
    tree[3] = { 3, 0, 6 };  // 节点3，左孩子为空(0)，右孩子是6
    tree[4] = { 4, 0, 0 };  // 节点4，叶子节点
    tree[5] = { 5, 0, 0 };  // 节点5，叶子节点
    tree[6] = { 6, 0, 0 };  // 节点6，叶子节点

    // 执行非递归先序遍历，从根节点1开始
    cout << "先序遍历结果: ";
    preOrder(1);  // 输出: 1 2 4 5 3 6

    return 0;
}