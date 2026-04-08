#include <vector>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
class Solution {
public:
	int cnt;
	vector<int> dfn;
	//siz数组下标用的是dfn序重排之后的下标
	vector<int> siz;
	//dep数组记录深度，下标用的同样是dfn序重排之后的下标
	vector<int> dep;
	void dfs(TreeNode* root,int depth)
	{
		if (!root) return;
		int u = root->val;
		dfn[u] = ++cnt;
		dep[dfn[u]]=depth;
		if (root->left != nullptr)
		{
			dfs(root->left,depth+1);
			int v1 = root->left->val;
			siz[dfn[u]] += siz[dfn[v1]];
		}
		if (root->right != nullptr)
		{
			dfs(root->right,depth+1);
			int v2 = root->right->val;
			siz[dfn[u]] += siz[dfn[v2]];
		}
	}
	vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
		cnt = 0;
		dfn.resize(100005);
		siz.assign(100005,1);
		dep.resize(100005);
		dfs(root, 0);
		//对于每次查询，假设删除值为x的节点，
		//我们消除了dfn序dfn[x]到dfn[x]+siz[dfn[x]]-1的节点
		//也就是说我们要在dep数组中找到去除这一段之后的最大值
		//由于是离线查询，我们可以预处理出dep数组的前后缀最大值，直接查询即可
		//增加两个虚拟点0,cnt+1，方便边界处理，这两个点对应深度都是0
		vector<int> maxl(100005);
		vector<int> maxr(100005);
		for (int i = 1; i <= cnt; i++)
		{
			maxl[i] = max(maxl[i - 1], dep[i]);
		}
		for (int i = cnt; i >= 1; i--)
		{
			maxr[i] = max(maxr[i + 1], dep[i]);
		}
		vector<int> ans;
		int m = queries.size();
		for (int i = 0; i < m; i++)
		{
			int u = dfn[queries[i]];
			int l = maxl[u - 1], r = maxr[u + siz[u]];
			ans.emplace_back(max(l, r));
		}
		return ans;
	}
};