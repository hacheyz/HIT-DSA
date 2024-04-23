/* ********** 说明 **********
 * 此文件包含：
 * 		1. 线性表的静态链表存储结构的声明与定义
 * 		2. 静态链表的逆置算法
 * 假设：
 * 		所有传入函数的 pos 都是合法的结点地址（即头节点之后的所有节点）
 */

#ifndef HW1_STATIC_LINK_LIST_H
#define HW1_STATIC_LINK_LIST_H

#include "all_list.h"
#define STATIC_NULL 0

using namespace std;

template<typename T>
class StaticNode
{
public:
	T data;
	int next;
};

typedef int Cursor;

template<typename T>
class StaticList
{
private:
	StaticNode<T> space[MAX_LENGTH];
protected:
	Cursor getNode();			// 申请空间
	void freeNode(Cursor pos);	// 回收空间
public:
	/* 存储结构的声明 */
	Cursor head;

	StaticList();
	~StaticList();
	void create();
	void destroy();
	void travel();    // 遍历并打印
	int length();
	bool isEmpty();
	bool isFull();
	void append(T x);    // 在表尾插入元素
	void insert(T x, Cursor pos);    // 在 pos 插入元素
	void remove(Cursor pos);        // 删除 pos 位置的元素
	T retrieve(Cursor pos);        // 返回 pos 位置元素的数据域
	Cursor find(T x);                // 返回第一个数据域为 x 的元素位置
	Cursor prev(Cursor pos);
	Cursor next(Cursor pos);
	Cursor front();        // 返回第一个元素
	Cursor back();            // 返回最后一个元素

	/* 逆置算法的声明 */
	StaticList<T>& reverse();	// 逆置
};

template<typename T>
Cursor StaticList<T>::getNode()
{
	Cursor r = space[0].next;
	space[0].next = space[r].next;
	return r;
}

template<typename T>
void StaticList<T>::freeNode(Cursor pos)
{
	space[pos].next = space[0].next;
	space[0].next = pos;
}

template<typename T>
StaticList<T>::StaticList()
{
	create();
}

template<typename T>
StaticList<T>::~StaticList()
{
	destroy();
}

template<typename T>
void StaticList<T>::create()
{
	for (int i=2; i<MAX_LENGTH; ++i)
	{
		space[i].next = i + 1;
	}
	space[MAX_LENGTH - 1].next = STATIC_NULL;	// 令最后一个可用结点的 next 为 0（空）
	space[0].next = 2;	// space[0].next 为第一个可用结点
	head = 1;	// space[1] 为链表头节点（不存数据）
	space[1].next = STATIC_NULL;
}

template<typename T>
void StaticList<T>::destroy()
{
	Cursor p = 1;
	while (p != STATIC_NULL)
	{
		Cursor q = next(p);
		freeNode(p);
		p = q;
	}
}

template<typename T>
void StaticList<T>::travel()
{
	Cursor p = front();
	while (p != STATIC_NULL)
	{
		cout << retrieve(p) << '\t';
		p = next(p);
	}
	cout << endl;
}

template<typename T>
int StaticList<T>::length()
{
	int len = 0;
	Cursor p = space[1].next;
	while (p != STATIC_NULL)
	{
		len++;
		p = next(p);
	}
	return len;
}

template<typename T>
bool StaticList<T>::isEmpty()
{
	return next(1) == STATIC_NULL;
}

template<typename T>
bool StaticList<T>::isFull()
{
	return length() == MAX_LENGTH;
}

template<typename T>
void StaticList<T>::append(T x)
{
	Cursor toAppend = getNode();
	if (toAppend == STATIC_NULL)
	{
		cout << "表满" << endl;
		return;
	}
	space[toAppend].data = x;
	space[toAppend].next = STATIC_NULL;
	Cursor p = back();
	space[p].next = toAppend;
}

template<typename T>
void StaticList<T>::insert(T x, Cursor pos)
{
	Cursor toInsert = getNode();
	if (toInsert == STATIC_NULL)
	{
		cout << "表满" << endl;
		return;
	}
	space[toInsert].data = x;
	space[toInsert].next = pos;
	Cursor prev = this->prev(pos);
	space[prev].next = toInsert;
}

template<typename T>
void StaticList<T>::remove(Cursor pos)
{
	if (isEmpty())
	{
		cout << "表空" << endl;
		return;
	}
	Cursor toRemove = pos;
	Cursor prev = this->prev(pos);
	space[prev].next = next(next(prev));
	freeNode(toRemove);
}

template<typename T>
T StaticList<T>::retrieve(Cursor pos)
{
	return space[pos].data;
}

template<typename T>
Cursor StaticList<T>::find(T x)
{
	Cursor r = STATIC_NULL;
	Cursor p = front();
	while (p != STATIC_NULL)
	{
		if (retrieve(p) == x)
		{
			r = p;
			break;
		}
		p = next(p);
	}
	return r;
}

template<typename T>
Cursor StaticList<T>::prev(Cursor pos)
{
	Cursor p = 1;
	while (next(p) != STATIC_NULL && next(p) != pos)
	{
		p = next(p);
	}
	return p;
}

template<typename T>
Cursor StaticList<T>::next(Cursor pos)
{
	return space[pos].next;
}

template<typename T>
Cursor StaticList<T>::front()
{
	return next(1);
}

template<typename T>
Cursor StaticList<T>::back()
{
	Cursor p = 1;
	while (next(p) != STATIC_NULL)
	{
		p = next(p);
	}
	return p;
}

template<typename T>
StaticList<T>& StaticList<T>::reverse()
{
	if (isEmpty())
	{
		return *this;
	}
	Cursor p = front();
	space[1].next = STATIC_NULL;
	while (p != STATIC_NULL)
	{
		this->insert(space[p].data, space[1].next);
		p = next(p);
	}
	return *this;
}


#endif //HW1_STATIC_LINK_LIST_H