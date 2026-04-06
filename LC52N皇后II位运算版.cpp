//n皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，
//并且使皇后彼此之间不能相互攻击。
//给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。
//位运算实现的n皇后问题
//位运算只优化了常数时间，时间复杂度不变
//O(n!)
class Solution {
public:
    int totalNQueens(int n) {
        if (n < 1)
        {
            return 0;
        }
        //设置一个掩码跟据n的范围来限制范围
        int mask = (1LL << n) - 1;
        return f(mask, 0, 0, 0);
    }
    //mask二进制有几个1就是几皇后问题，表示问题规模
    //之前皇后对列的影响:col
    //之前皇后的左下对角线影响:left(从右上到左下)
    //之前皇后的右下对角线影响:right(从左上到右下)
    int f(int mask,int col,int left,int right)
    {
        //base case
        if (col == mask)
        {
            //col==mask
            //也就是说每一列都被填满了
            return 1;
        }
        //记录限制的变量
        int ban = (col | left | right);
        //目前ban上1表示限制，0表示可以放
        //取反之后1表示可以放皇后，0不能放，方便计算
        ban = (~ban);
        //mask限制位数,candidate的二进制位都是可行位置
        int candidate = mask & (ban);
        //对于每一行最多放一列，遍历每一列，由于列上的可行位置用1表示
        //遍历每一列可以通过：提取一个数字二进制表示最低位的一个1来实现
        //使用Brain Kernighan算法
        //记录答案的变量
        int ans = 0;
        //记录放置皇后的尝试
        int place = 0;
        while (candidate != 0)
        {
            //相当于candidate位于上他自己取反再加一，也就是-candidate
            place = candidate & (-candidate);
            //此时place二进制上的1正好是限制之外的那个位置
            //注意不要在这里更新限制，不然需要回溯，
            //但是按位与和按位或很难逆运算，所以我们要在递归函数里改
            //调递归
            ans += f(mask, col | place, (left | place) >> 1, (right | place) << 1);
            //记得更新candidate,把用过的1消去
            candidate ^= place;
        }
        return ans;
    }
};