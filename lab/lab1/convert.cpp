#include "convert.h"
#include "stack.h"
#include <string>

using namespace std;

string convert(string inf, std::string& varTable)
{
	string suf;
	Stack<char> s;
	ll cnt = 0;	// 栈状态变化计数器
	bool negtiveFlag = false;	// 读入负数时置为 true
	/* 由宏是否被定义决定是否打印栈 */
#ifdef SHOW_CONVERT_STACK
	showConvertStack(s, cnt++);	//--//
#endif
	auto it = inf.begin();
	while (it != inf.end())
	{
		if (*it == '#')
		{
			it++;	// 忽略 '#'
		}
		else if (isdigit(*it) || isalpha(*it) || *it == '.')
		{
			if (negtiveFlag)
			{
				suf.push_back('-');	// 将 '-' 也输入后缀表达式，留待 calculate 处理
				negtiveFlag = false;
			}
			if (isalpha(*it))
			{
				if (varTable.find(*it) == -1)	// 如果变量表中无此符号
				{
					varTable.push_back(*it);
				}
				suf.push_back(*it);
				suf.push_back(' ');
				it++;
				continue;
			}
			while (isdigit(*it) || *it == '.')
			{
				suf.push_back(*it);	// 将 '.' 也输入后缀表达式，留待 calculate 处理
				it++;
			}
			suf.push_back(' ');
		}
		else if (*it == '(')
		{
			s.push('(');	// 遇到 '(' 直接入栈即可
#ifdef SHOW_CONVERT_STACK
			showConvertStack(s, cnt++);	//--//
#endif
			it++;
		}
		else if (*it == ')')
		{
			/* 一直出栈直到栈顶为 ‘(’ */
			while (s.getTop() != '(')
			{
				char top = s.pop();
#ifdef SHOW_CONVERT_STACK
				showConvertStack(s, cnt++);	//--//
#endif
				suf.push_back(top);
				suf.push_back(' ');
			}
			s.pop();	// 弹出 '('
#ifdef SHOW_CONVERT_STACK
			showConvertStack(s, cnt++);	//--//
#endif
			it++;
		}
		else
		{
			if (*it == '-')		// 处理负数
			{
				auto itPrev = prev(it);
				/* '-' 为首位，或前一位不是数字或字母或 ')' 时，认为 '-' 是负号而非减号 */
				if (*itPrev == '#' || (!isdigit(*itPrev) && !isalpha(*itPrev) && *itPrev != ')'))
				{
					negtiveFlag = true;
					it++;
					continue;
				}
			}
			/* 栈不空的情况下才可能需要出栈(栈空可直接入栈) */
			while (!s.isEmpty() && keepPop(*it, s.getTop()))
			{
				char top = s.pop();
#ifdef SHOW_CONVERT_STACK
				showConvertStack(s, cnt++);	//--//
#endif
				suf.push_back(top);
				suf.push_back(' ');
			}
			s.push(*it);
#ifdef SHOW_CONVERT_STACK
			showConvertStack(s, cnt++);	//--//
#endif
			it++;
		}
	}
	while (!s.isEmpty())	// 处理栈中剩余项
	{
		char top = s.pop();
#ifdef SHOW_CONVERT_STACK
		showConvertStack(s, cnt++);	//--//
#endif
		suf.push_back(top);
		suf.push_back(' ');
	}
	return suf;
}

int priority(char op)
{
	switch (op)
	{
	case '+':
	case '-':
		return 0;
	case '*':
	case '/':
		return 1;
	case '^':
		return 2;
	default:
		return -1;
	}
}

bool keepPop(char a, char b)
{
	/* 继续出栈的条件是 *it(i.e. a) 的优先级不比 top(i.e. b) 高 */
	if (priority(a) <= priority(b))
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
void showConvertStack(Stack<T> s, ll cnt)
{
	printf("convert stack status %2lld: ", cnt);
	s.travel();
}