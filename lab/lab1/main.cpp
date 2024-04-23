/* 此文件用于测试
 *
 * 输入：
 * 	从文件 "expr.txt" 中读取若干个中缀表达式
 *
 * 输出：
 * 	对于读入的每个表达式：
 * 	1. 打印读入的中缀表达式
 * 	2. 打印转化过程中栈的状态变化过程(需要打开 convert.h 中的宏 SHOW_CONVERT_STACK)
 * 	3. 打印转化得到的后缀表达式
 * 	4. 打印计算过程中栈的状态变化过程(需要打开 calculate.h 中的宏 SHOW_CALC_STACK)
 * 	5. 打印计算结果
 *
 * 假设:
 *	1. 操作数为任意实数或任意单个英文字母(区分大小写)
 *	2. 运算符只含 '-' 这种一元运算符和 '+' '-' '*' '/' '^' 五种二元运算符
 *	2* 不允许对整个表达式取负，如 -(2+3) 应改写为 -1*(2+3)
 *	2**不允许省略数字与字母之间的运算符号，如 3x 应改写为 3*x
 *	3. 界限符有左右括号 '(' ')' 和表达式起始结束符 '#'
 *
 * exit() 返回状态值：
 * 	0. 正常退出
 * 	1. 栈满
 * 	2. 栈空
 * 	3. 除零
 * 	4. 文件无法打开
 */

#include "convert.h"
#include "calculate.h"
#include <iostream>
#include <string>
#include <cstring>

#define MAX_EXPR_LENGTH 10000
#define MAX_VAR_NUM	20

using namespace std;

int main()
{
	FILE *fp = fopen("expr.txt", "r");	// 从 expr.txt 中读取若干中缀表达式
	if (fp == NULL)
	{
		exit(4);	// 文件无法打开，错误码 4
	}
	char buf[MAX_EXPR_LENGTH];
	int cnt = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s", buf);
		string inf = buf;	// 将 char* 字符串转换为 string 类字符串
		string suf;			// 后缀表达式
		string varTable;		// 变量操作数的符号集(如果有)
		ld varVal[MAX_VAR_NUM];	// 变量操作数的值(如果有，按 varTable 顺序)
		memset(varVal, 0, sizeof(varVal));
		cout << "# EXPR " << cnt++ << endl;
		cout << "Original infix expression: " << inf << endl;	// 打印中缀表达式
		suf = convert(inf, varTable);	// 转换
		if (!varTable.empty())		// 如果含变量操作数
		{
			int varCnt = 0;		// 对变量操作数计数
			for (auto it = varTable.begin(); it != varTable.end(); ++it)
			{
				cout << "Input the value of " << *it << ": ";
				cin >> varVal[varCnt++];	// 按提示依次输入变量操作数的值
			}
		}
		cout << "Converted to suffix expression: " << suf << endl;	// 打印后缀表达式
		ld ret = calculate(suf, varTable, varVal);	// 计算
		cout << "Result: " << ret << endl << endl;
	}

	return 0;
}
