/* ********** 说明 **********
 * 此文件包含：
 * 		1. 线性表的链式存储结构的声明与定义
 * 		2. 在此基础上的五个算法
 * 假设：
 * 		所有传入函数的 pos 都是合法的结点地址（即头节点之后的所有节点）
 */

#ifndef HW1_LINK_LIST_H
#define HW1_LINK_LIST_H

#include "all_list.h"
#include <iostream>

using namespace std;

// 结点模板
template<typename T>
class Node
{
public:
	T data;
	Node<T> *next;
};

// 为 Node<T> * 设置别名 LinkPos
template<typename T>
using LinkPos = Node<T> *;

// 模板类声明
template<typename T>
class LinkList
{
public:
	/* 存储结构的声明 */
	Node<T> *head;    // 头节点不存数据

	LinkList();
	~LinkList();
	void create();    // 创建线性表
	void destroy();    // 释放线性表空间
	void travel();    // 遍历并打印
	int length();
	bool isEmpty();
	bool isFull();
	void append(T x);    // 在表尾插入元素
	void insert(T x, LinkPos<T> pos);    // 在 pos 插入元素
	void remove(LinkPos<T> pos);        // 删除 pos 位置的元素
	T retrieve(LinkPos<T> pos);        // 返回 pos 位置元素的数据域
	LinkPos<T> find(T x);                // 返回第一个数据域为 x 的元素位置
	LinkPos<T> prev(LinkPos<T> pos);
	LinkPos<T> next(LinkPos<T> pos);
	LinkPos<T> front();        // 返回第一个元素，若不存在，返回 head
	LinkPos<T> back();            // 返回最后一个元素，若不存在，返回 head

	/* 五个算法 */
	LinkList<T>& removeGiven(T x);	// 删除给定元素
	LinkList<T>& removeDuplicate();    // 删除有序线性表的重复元素
	LinkList<T>& reverse();        // 逆置
	LinkList<T>& leftShift(int k);    // 左移 k 位
	LinkList<T>& rightShift(int k);    // 右移 k 位
	LinkList<T> merge(LinkList<T>& L);    // 合并两个有序线性表
};

// 函数实现
template<typename T>
LinkList<T>::LinkList()
{
	create();    // 调用自定义构造函数
}

template<typename T>
LinkList<T>::~LinkList()
{
	destroy();    // 调用自定义析构函数
}

template<typename T>
void LinkList<T>::create()
{
	head = new Node<T>;
	head->data = 0;
	head->next = NULL;
}

template<typename T>
void LinkList<T>::destroy()
{
	LinkPos<T> p = head;
	while (p != NULL)
	{
		Node<T> *q = p->next;
		delete p;
		p = q;
	}
}

template<typename T>
void LinkList<T>::travel()
{
	LinkPos<T> p = front();
	while (p != NULL)
	{
		cout << retrieve(p) << '\t';
		p = p->next;
	}
	cout << endl;
}

template<typename T>
int LinkList<T>::length()
{
	int len = 0;
	LinkPos<T> p = head->next;
	while (p != NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}

template<typename T>
bool LinkList<T>::isEmpty()
{
	return head->next == NULL;
}

template<typename T>
bool LinkList<T>::isFull()
{
	return length() == MAX_LENGTH;
}

template<typename T>
void LinkList<T>::append(T x)
{
	if (isFull())
	{
		cout << "表满" << endl;
		return;
	}
	Node<T> *toAppend = new Node<T>;
	toAppend->data = x;
	toAppend->next = NULL;
	if (isEmpty())
	{
		head->next = toAppend;
	}
	else
	{
		LinkPos<T> p = back();
		p->next = toAppend;
	}
}

template<typename T>
void LinkList<T>::insert(T x, LinkPos<T> pos)
{
	if (isFull())
	{
		cout << "表满" << endl;
		return;
	}
	Node<T> *toInsert = new Node<T>;
	toInsert->data = x;
	toInsert->next = pos;
	LinkPos<T> prev = this->prev(pos);
	prev->next = toInsert;
}

template<typename T>
void LinkList<T>::remove(LinkPos<T> pos)
{
	if (isEmpty())
	{
		cout << "表空" << endl;
		return;
	}
	LinkPos<T> toRemove = pos;
	LinkPos<T> prev = this->prev(pos);
	prev->next = prev->next->next;
	delete toRemove;
}

template<typename T>
T LinkList<T>::retrieve(LinkPos<T> pos)
{
	return pos->data;
}

template<typename T>
LinkPos<T> LinkList<T>::find(T x)
{
	LinkPos<T> r = NULL;
	LinkPos<T> p = front();
	while (p != NULL)
	{
		if (retrieve(p) == x)
		{
			r = p;
			break;
		}
		p = p->next;
	}
	return r;
}

template<typename T>
LinkPos<T> LinkList<T>::prev(LinkPos<T> pos)
{
	if (front() == pos)
	{
		return head;    // head->next 的前驱为 head
	}
	LinkPos<T> p = head;
	while (p->next != NULL && p->next != pos)
	{
		p = p->next;
	}
	return p;
}

template<typename T>
LinkPos<T> LinkList<T>::next(LinkPos<T> pos)
{
	return pos->next;
}

template<typename T>
LinkPos<T> LinkList<T>::front()
{
	if (isEmpty())
	{
		return NULL;
	}
	else
	{
		return head->next;
	}
}

template<typename T>
LinkPos<T> LinkList<T>::back()
{
	if (isEmpty())
	{
		return NULL;
	}
	LinkPos<T> p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

template<typename T>
LinkList<T>& LinkList<T>::removeGiven(T x)
{
	LinkPos<T> p = front();
	LinkPos<T> q;
	while (p != NULL)
	{
		q = p->next;
		if (retrieve(p) == x)
		{
			remove(p);
		}
		p = q;
	}
	return *this;
}

template<typename T>
LinkList<T>& LinkList<T>::removeDuplicate()
{
	if (isEmpty())
	{
		return *this;
	}
	LinkPos<T> p = front();
	T temp = retrieve(p);
	p = p->next;
	LinkPos<T> q;
	while (p != NULL)
	{
		q = p->next;
		if (retrieve(p) == temp)
		{
			remove(p);
		}
		temp = retrieve(p);
		p = q;
	}
	return *this;
}

template<typename T>
LinkList<T>& LinkList<T>::reverse()
{
	if (isEmpty())
	{
		return *this;
	}
	LinkPos<T> p = front();
	this->head->next = NULL;
	while (p != NULL)
	{
		this->insert(p->data, this->head->next);
		p = p->next;
	}
	return *this;
}

template<typename T>
LinkList<T>& LinkList<T>::leftShift(int k)
{
//	LinkList<T> R;
	int len = length();
	if (len == 0)
	{
		return *this;
	}
	k = k%len;
	LinkPos<T> pOri = front();
	LinkPos<T> p = pOri;
	this->head->next = NULL;
	for (int i = 0; i < k; ++i)
	{
		p = p->next;
	}
	LinkPos<T> start = p;
	while (p != NULL)
	{
		this->append(p->data);
		p = p->next;
	}
	p = pOri;
	while (p != start)
	{
		this->append(p->data);
		p = p->next;
	}

	return *this;
}

template<typename T>
LinkList<T>& LinkList<T>::rightShift(int k)
{
	int len = length();
	if (len == 0)
	{
		return *this;
	}
	k = k%len;
	return leftShift(len - k);
}

template<typename T>
LinkList<T> LinkList<T>::merge(LinkList<T>& L)
{
	LinkList<T> R;
	LinkPos<T> p, q;
	p = this->front();
	q = L.front();
	while (p != NULL && q != NULL)
	{
		if (this->retrieve(p) < L.retrieve(q))
		{
			R.append(this->retrieve(p));
			p = p->next;
		}
		else
		{
			R.append(L.retrieve(q));
			q = q->next;
		}
	}
	while (p != NULL)
	{
		R.append(this->retrieve(p));
		p = p->next;
	}
	while (q != NULL)
	{
		R.append(L.retrieve(q));
		q = q->next;
	}

	return R;
}

#endif //HW1_LINK_LIST_H
