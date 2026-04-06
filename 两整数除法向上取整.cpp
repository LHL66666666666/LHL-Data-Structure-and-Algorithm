#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//在C语言中，整数除法默认是向下取整（即直接截断小数部分）
//在C语言中，整数除法的行为是向零取整（truncated toward zero）
//这意味着无论操作数的符号如何，结果都会向零的方向舍入。具体来说：
//对于正数，除法结果会向下取整（floor），例如 7 / 3 等于 2。
//对于负数，除法结果会向上取整（ceil），例如 - 7 / 3 等于 - 2（因为 - 2.33向零取整为 - 2）
//这种取整方式称为截断取整（truncation）


//公式：
//		对于正整数a和正整数b（b不为0），向上取整的公式为：
//		(a + b - 1) / b
//事实上，当 a 和 b 同号（均为正或均为负）时该公式成立

//通用方法：
//先计算商 quotient = a / b 和余数 remainder = a % b。
//调整规则：当余数非零且 a 与 b 同号时，商加1。
//
//原理：
//同号时（如两正数），余数 > 0 表示需进位。
//异号时（如一正一负），整数除法已向上取整，无需调整。
int main()
{
	//当两数同号时
	int a, b;
	scanf("%d %d", &a, &b);
	int res = (a + b - 1) / b;
	printf("%d\n", res);

	printf("%d\n", ceil_div(7, -3));


	return 0;
}

//通用方法
int ceil_div(int a, int b)
{
	if (b == 0) return 0; // 简化处理除0错误
	return (a % b != 0 && (a < 0) == (b < 0)) ? (a / b + 1) : (a / b);
	//对于同号的情况，若不整除，向下取整再加1等于向上取整
}