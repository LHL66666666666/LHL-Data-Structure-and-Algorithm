/*
给定一个二叉树，找到其中最大的二叉搜索树（BST）子树，并返回该子树的大小。
其中，最大指的是子树节点数最多的。
二叉搜索树（BST）中的所有节点都具备以下属性：
左子树的值小于其父（根）节点的值。
右子树的值大于其父（根）节点的值。
注意：子树必须包含其所有后代。
*/
//LeetCode上类描述给定的二叉树
/*
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
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
	struct node {
		ll maxval, minval;
		bool isBST;
		ll maxBSTsize;
	};
	int largestBSTSubtree(TreeNode* root) {
		auto res=dfs(root);
		return res.maxBSTsize;
	}
	node dfs(TreeNode* root)
	{
		//子树为空树,base case
		if (!root)
		{
			node x;
			x.maxval = -INF, x.minval = INF, x.isBST = 1, x.maxBSTsize = 0;
			return x;
		}
		//如果子树不是空树
		//找到左右两侧的信息
		node left = dfs(root->left);
		node right = dfs(root->right);
		int flag = 0;
		//两种情况
		//情况1，不要这个根节点root
		ll ans = max(left.maxBSTsize, right.maxBSTsize);
		//情况2，满足左右子树都是二叉搜索树，检查根节点是否满足条件
		if (left.isBST && right.isBST)
		{
			if (root->val > left.maxval && root->val < right.minval)
			{
				flag = 1;
				ans = max(ans, left.maxBSTsize + right.maxBSTsize + 1);
			}
		}
		node ret;
		ret.isBST = flag, ret.maxBSTsize = ans;
		ret.maxval = max((ll)root->val, max(left.maxval, right.maxval));
		ret.minval = min((ll)root->val, min(left.minval, right.minval));
		return ret;
	}
};
