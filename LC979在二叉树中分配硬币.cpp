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
//显然我们需要子树的节点数量，就是最终状态下需要的硬币个数
//同时，每个节点如果已经拥有了1个硬币，那么需要将硬币推给自己的根节点
//如果不够的话，需要向其他节点要硬币
//记录完成以上操作需要的操作次数
//同时，要操作次数最少，尽量找离自己近的转移
struct node {
	//cnt表示节点数，op表示需要的操作次数，sum表示自己及子树的硬币数量之和
	ll cnt;
	ll op;
	ll sum;
};
class Solution {
public:
	int distributeCoins(TreeNode* root) {
		auto res = dfs(root);
		return res.op;
	}
	node dfs(TreeNode* root)
	{
		//base case空节点
		if (!root)
		{
			node x;
			x.cnt = 0, x.op = 0, x.sum = 0;
			return x;
		}
		//注意一次只能转移1个
		auto left = dfs(root->left);
		auto right = dfs(root->right);
		ll cnt = left.cnt + right.cnt+1;
		ll sum = left.sum + right.sum+root->val;
		node ret;
		ret.op = abs(left.sum - left.cnt) + abs(right.sum - right.cnt) + left.op + right.op;
		ret.cnt = cnt;
		ret.sum = sum;
		return ret;
	}
};