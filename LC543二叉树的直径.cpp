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
struct node {
	ll maxlen;
	ll depth;
};
class Solution {
public:
	int diameterOfBinaryTree(TreeNode* root) {
		auto res = dfs(root);
		return res.maxlen;
	}
	node dfs(TreeNode* root)
	{
		if (!root)
		{
			node x;
			x.maxlen = 0;
			x.depth = -1;
			return x;
		}
		//我们定义深度根节点为到叶子节点经过的边数
		//每次来到一个节点，直径可能是左+右+2，也可能是原来的一条路径
		auto left = dfs(root->left);
		auto right = dfs(root->right);
		node ret;
		ret.depth = max(left.depth, right.depth) + 1;
		ret.maxlen = max(left.depth + right.depth + 2, max(left.maxlen, right.maxlen));
		return ret;
	}
};