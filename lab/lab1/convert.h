/* 转换过程所用到的宏和函数声明 */

#ifndef LAB1_CONVERT_H
#define LAB1_CONVERT_H

#include "stack.h"
#include <string>

//#define SHOW_CONVERT_STACK

typedef long long ll;

int priority(char op);	// 计算运算符优先级
bool keepPop(char a, char b);	// 判断是否应该继续出栈

template<typename T>
void showConvertStack(Stack<T> s, ll cnt);	// 遍历打印栈

std::string convert(std::string inf, std::string& varTable);	// 主函数，返回转化后的后缀表达式

#endif //LAB1_CONVERT_H
