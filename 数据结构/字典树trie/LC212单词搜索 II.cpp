/*
给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words， 返回所有二维网格上的单词 。
单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母在一个单词中不允许被重复使用。
*/
#include <vector>
#include <string>
//本题中前缀树的两个作用：
//1.剪枝：直到有必要的才去递归展开
//2.在每一个字符串的结尾节点存储这个字符串，避免了路径中收集每个字符
//3.利用前缀树进行删除操作，修改pass值来表示这个字符串已经被收集，不需要再次递归展开，依旧是剪枝
//注意：这里的前缀树是对于待收集字符串建的一棵前缀树
class Solution {
public:
	//使用静态数组实现前缀树
	int tree[300005][30];
	//int end[300005];
	struct node {
		int val = 0;
		//多加入一个参数表示到这里结束的那个字符串
		std::string s;
	}end[300005];
	int pass[300005];
	//cnt记录申请节点的编号
	int cnt = 0;
	//初始化
	void build() {
		cnt = 1;
	}
	//增
	void insert(std::string s) {
		//从头节点开始，首先在头节点+1表示经过了头节点
		//cur表示当前的节点是哪个
		int cur = 1;
		pass[cur]++;
		for (int i = 0; i < s.size(); i++) {
			//path表示下一步的路径
			int path = s[i] - 'a';
			if (tree[cur][path] == 0) {
				//分配新的内存编号
				tree[cur][path] = ++cnt;
			}
			//更新当前的节点
			cur = tree[cur][path];
			//经过下一个位置
			pass[cur]++;
		}
		//遍历完之后，将现在在的节点end值+1
		end[cur].val++;
		end[cur].s = s;
	}
	//清空数组，避免数据污染
	void clear() {
		for (int i = 1; i <= cnt; i++) {
			//因为我们最多用了cnt行
			memset(tree[i], 0, sizeof(tree[i]));
			end[i].val = 0;
			end[i].s.clear();
			pass[i] = 0;
		}
	}

	//搜索四个坐标
	int x[4] = { 0,0,1,-1 };
	int y[4] = { 1,-1,0,0 };
	std::vector<std::string> ans;
	//注意这里形参idx表示前缀树节点的编号
	//返回值是收集到的字符串的数量，便于pass里面剪枝
	int dfs(std::vector<std::vector<char>>& board, int idx, int x0, int y0, int m, int n)
	{
		//不合法的位置直接返回
		if (x0 < 0 || x0 >= m || y0 < 0 || y0 >= n || board[x0][y0] == 0)
		{
			return 0;
		}
		//记录当前位置
		char tmp = board[x0][y0];
		//计算字典树中路的编号
		int road = tmp - 'a';
		//idx表示节点编号，road是在26个之中哪一位置
		idx = tree[idx][road];	
		//检查字典树后续还有没有走向road的路，如果有的话继续走，没有的话就不需要走了，直接返回
		if (pass[idx] == 0)
		{
			//表示后续不再存在路，可以直接返回
			return 0;
		}
		//将自己设置为不可用
		board[x0][y0] = 0;
		//fix变量记录这条路上收集了几个字符串，用于剪枝3
		int fix = 0;
		//如果来到末尾位置，加入答案
		if (end[idx].s.size() > 0)
		{
			ans.emplace_back(end[idx].s);
			end[idx].s.clear();
			end[idx].val = 0;  //标记为已找到
			fix++;
		}
		//检查四个位置
		for (int i = 0; i < 4; i++)
		{

			fix += dfs(board, idx, x0 + x[i], y0 + y[i], m, n);

		}
		//恢复现场
		board[x0][y0] = tmp;
		//剪枝3
		pass[idx] -= fix;
		return fix;
	}
	std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
		//m行n列
		int m = board.size();
		int n = board[0].size();
		ans.clear();
		//建前缀树
		build();
		for (auto word : words)
		{
			insert(word);
		}
		//搜索
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				//dfs,注意这里不再dfs每一个单词，而是采用dfs字典树的方式优化
				dfs(board, 1, i, j, m, n);
			}
		}
		clear();
		return ans;
	}
};