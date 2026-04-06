#include <vector>
#include <set>
#include <map>
#include <unordered_map>
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
//来到一个节点，路经总和等于：左子树的路经总和+右子树的路径总和+加入自己新产生的路径总和
//就是经典的前缀和+哈希表问题
//但是在这个问题中，我们需要回溯，因为每一条路径上所需建立的哈希表是不同的
//在结束一棵子树之后，必须恢复现场
//需要回溯就注定不能从下向上建立哈希表，需要从上向下建立哈希表
//DFS遍历这棵树，遍历到节点node时，假设node是路径的终点，
//那么有多少个起点，满足起点到终点node的路径总和恰好等于targetSum
class Solution {
public:
	unordered_map<ll, int> mp;
	int pathSum(TreeNode* root, int targetSum) {
		mp.clear();
		mp[0LL] = 1;
		return dfs(root, targetSum, 0);
	}
	//sum表示从根节点出发沿最短路来到当前节点，前缀和
	//返回以当前节点结尾时，累加和等于tar的路径数
	int dfs(TreeNode* root,int tar,ll sum)
	{
		if (!root)
		{
			return 0;
		}
		int ans = 0;
		sum += root->val;
		if (mp.count(sum-tar)) ans += mp[sum - tar];
		mp[sum]++;
		ans += dfs(root->left, tar, sum);
		ans += dfs(root->right, tar, sum);
		mp[sum]--;
		return ans;
	}
};