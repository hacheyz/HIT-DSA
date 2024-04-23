#include "stack.h"
#include "calculate.h"
#include <cctype>
#include <cmath>

using namespace std;

long double calculate(string suf, string varTable, ld varVal[])
{
	ll cnt = 0;	// 栈状态变化计数器
	Stack<ld> s;
	bool negtiveFlag = false;
	auto it = suf.begin();
	while (it != suf.end())
	{
		if (*it == ' ')
		{
			it++;	// 忽略空格
			continue;
		}
		if (isdigit(*it) || isalpha(*it))
		{
			ld temp = 0;
			if (isalpha(*it))
			{
				int idx = 0;
				for (auto varIt = varTable.begin(); varIt != varTable.end(); ++varIt, ++idx)
				{
					if (*varIt == *it)	// 找到该变量的下标
						break;
				}
				temp = varVal[idx];	// 直接将变量的值赋给 temp
				it++;
			}
			while (isdigit(*it))	// 处理整数及小数的整数部分
			{
				temp *= 10;
				temp += *it - '0';
				it++;
			}
			if (it == suf.end() || *it != '.')
			{
				if (negtiveFlag)
				{
					temp *= -1;
					negtiveFlag = false;
				}
			}
			s.push(temp);
#ifdef SHOW_CALC_STACK
			showCalculateStack(s, cnt++);	//--//
#endif
		}
		else if (*it == '.')	// 处理小数点及小数部分
		{
			it++;
			ld temp = 0;
			ld tens = 10;
			while (isdigit(*it))
			{
				temp += (*it - '0')/tens;
				tens *= 10;
				it++;
			}
			ld top = s.pop();	// 将整数部分取出
#ifdef SHOW_CALC_STACK
			showCalculateStack(s, cnt++);	//--//
#endif
			top += temp;
			if (negtiveFlag)
			{
				top *= -1;
				negtiveFlag = false;
			}
			s.push(top);	// 将此数压入堆栈
#ifdef SHOW_CALC_STACK
			showCalculateStack(s, cnt++);	//--//
#endif
		}
		else
		{
			/* 当 '-' 后面无空格而紧跟操作数时，认为 '-' 为负号而非减号 */
			if (*it == '-' && (isdigit(*next(it)) || isalpha(*next(it))))
			{
				negtiveFlag = true;
				it++;
				continue;
			}
			ld a, b;
			b = s.pop();	// 逆序出栈
			a = s.pop();
			s.push(doOp(*it, a, b));
#ifdef SHOW_CALC_STACK
			showCalculateStack(s, cnt++);	//--//
#endif
			it++;
		}
	}
	return s.pop();	// 栈中唯一的数就是最终结果
}

ld doOp(char op, ld a, ld b)
{
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		if (b == 0)
		{
			exit(3);	// 除零，错误码 3
		}
		return a / b;
	case '^':
		return pow(a, b);
	default:
		return -1;
	}
}

template<typename T>
void showCalculateStack(Stack<T> s, ll cnt)
{
	printf("calculate stack status %2lld: ", cnt);
	s.travel();
}