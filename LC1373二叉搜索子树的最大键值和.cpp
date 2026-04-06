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
	ll maxval, minval;
	bool isBST;
	ll maxBSTval;
	ll sum;
};
class Solution {
public:
	int maxSumBST(TreeNode* root) {
		auto res = dfs(root);
		return res.maxBSTval;
	}
	node dfs(TreeNode* root)
	{
		//base case
		if (!root)
		{
			node x;
			x.maxval = -INF, x.minval = INF, x.isBST = 1, x.maxBSTval = 0, x.sum = 0;
			return x;
		}
		//如果不是空树
		//找到左右两侧的信息
		node left = dfs(root->left);
		node right = dfs(root->right);
		int flag = 0;
		ll sum = root->val + left.sum + right.sum;
		//两种情况
		//情况1，不要这个根节点root
		ll ans = max(left.maxBSTval, right.maxBSTval);
		//情况2，满足左右子树都是二叉搜索树，检查根节点是否满足条件
		if (left.isBST && right.isBST)
		{
			if (root->val > left.maxval && root->val < right.minval)
			{
				flag = 1;
				ans = max(ans, sum);
			}
		}
		node ret;
		ret.sum = sum;
		ret.isBST = flag, ret.maxBSTval = ans;
		ret.maxval = max((ll)root->val, max(left.maxval, right.maxval));
		ret.minval = min((ll)root->val, min(left.minval, right.minval));
		return ret;
	}
};
