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
//发现一个节点可以监控三层
//不妨考虑一下一个节点能监控几个
//自己，父节点(每个节点仅有1个父节点)，最多2个子节点
//子节点一层的节点数量一定不必它上一层的节点数量少
//我们跟据这种隔两层填一层的初步思考，考虑设计三种状态，对于1个节点x
//状态0：x未被覆盖，x的子节点均被覆盖
//状态1：x被覆盖，但是x上无摄像机，x的子节点均被覆盖
//状态2：x被覆盖，x上有摄像机，x的子节点均被覆盖
//实际上我们不能再找出更多状态
//假设还存在其他状态：那么只能是x未被覆盖，且x子节点未被覆盖，这种情况显然无法实现全覆盖
//这三种状态可以实现递推
//status表示状态，cnt表示安装摄像头数量
struct node {
	int status;
	int cnt;
};
class Solution {
public:
	int minCameraCover(TreeNode* root) {
		auto res = dfs(root);
		int ans = res.cnt;
		if (res.status == 0)
		{
			++ans;
		}
		return ans;
	}
	//这个递归建立在root一定有父节点的前提之下
	node dfs(TreeNode* root)
	{
		//空节点
		if (!root)
		{
			node x;
			x.status = 1;
			x.cnt = 0;
			return x;
		}
		auto left = dfs(root->left);
		auto right = dfs(root->right);
		int s1 = left.status, s2 = right.status;
		node ret;
		int cnt = left.cnt + right.cnt;
		if (s1 == 0 || s2 == 0)
		{
			ret.status = 2;
			++cnt;
		}
		else if (s1 == 2 || s2 == 2)
		{
			ret.status = 1;
		}
		else {
			ret.status = 0;
		}
		ret.cnt = cnt;
		return ret;
	}
};