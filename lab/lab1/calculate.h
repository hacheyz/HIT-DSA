/* 计算过程所用到的宏和函数声明 */

#ifndef LAB1_CALCULATE_H
#define LAB1_CALCULATE_H

#include <string>

//#define SHOW_CALC_STACK

typedef long double ld;	// 使用 long double 作为操作数的数据类型，精度高，范围大
typedef long long ll;

ld doOp(char op, ld a, ld b);	// 执行二元运算
ld calculate(std::string suf, std::string varTable, ld varVal[]);	// 主函数，返回计算结果

template<typename T>
void showCalculateStack(Stack<T> s, ll cnt);	// 遍历打印栈

#endif //LAB1_CALCULATE_H
