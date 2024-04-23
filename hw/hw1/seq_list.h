/* ********** 说明 **********
 * 此文件包含：
 * 		1. 线性表的顺序存储结构的声明与定义
 * 		2. 在此基础上的五个算法
 */

#ifndef HW1_SEQ_LIST_H
#define HW1_SEQ_LIST_H

#include "all_list.h"
#include <iostream>
#include <cstring>

#define INVALID_POSITION -1

using namespace std;

typedef int SeqPos;

template<typename T>
class SeqList
{
public:
	/* 存储结构的声明 */
	T data[MAX_LENGTH];
	int last;

	SeqList();
	~SeqList();
	void create();    // 创建线性表并初始化为 0
	void destroy();
	void travel();    // 遍历并打印
	int length();
	bool isEmpty();
	bool isFull();
	void append(T x);    // 在表尾插入元素
	void insert(T x, SeqPos pos);    // 在 pos 插入元素
	void remove(SeqPos pos);        // 删除 pos 位置的元素
	T retrieve(SeqPos pos);        // 返回 pos 位置元素的数据域
	SeqPos find(T x);                // 返回第一个数据域为 x 的元素位置
	SeqPos prev(SeqPos pos);
	SeqPos next(SeqPos pos);
	SeqPos front();        // 返回第一个元素，若不存在，返回 INVALID_POSITION
	SeqPos back();            // 返回最后一个元素，若不存在，返回 INVALID_POSITION

	/* 五个算法 */
	SeqList<T>& removeGiven(T x);	// 删除给定元素
	SeqList<T>& removeDuplicate();    // 删除有序线性表的重复元素
	SeqList<T>& reverse();        // 逆置
	SeqList<T>& leftShift(int k);    // 左移 k 位
	SeqList<T>& rightShift(int k);    // 右移 k 位
	SeqList<T> merge(SeqList<T>& L);    // 合并两个有序线性表
};

template<typename T>
SeqList<T>::SeqList()
{
	create();    // 调用自定义构造函数
}

template<typename T>
SeqList<T>::~SeqList()
{
	destroy();    // 调用自定义析构函数
}

template<typename T>
void SeqList<T>::create()
{
	memset(data, 0, sizeof(data));    // 初始化为 0
	last = 0;    // 空表
}

template<typename T>
void SeqList<T>::destroy()
{
	last = 0;
}

template<typename T>
void SeqList<T>::travel()
{
	for (SeqPos i = 0; i < last; i++)
	{
		cout << data[i] << '\t';
	}
	cout << endl;
}

template<typename T>
int SeqList<T>::length()
{
	return last;
}

template<typename T>
bool SeqList<T>::isEmpty()
{
	return last == 0;
}

template<typename T>
bool SeqList<T>::isFull()
{
	return last == MAX_LENGTH;
}

template<typename T>
void SeqList<T>::append(T x)
{
	if (isFull())
	{
		cout << "表满" << endl;
		return;
	}
	data[last] = x;
	last++;
}

template<typename T>
void SeqList<T>::insert(T x, SeqPos pos)
{
	if (isFull())
	{
		cout << "表满" << endl;
		return;
	}
	if (pos < 0 || pos > last - 1)
	{
		cout << "非法位置" << endl;
		return;
	}
//	for (SeqPos i=pos; i<last; ++i)
	for (SeqPos i = last - 1; i >= pos; --i)
	{
		data[i + 1] = data[i];
	}
	data[pos] = x;
	last++;
}

template<typename T>
void SeqList<T>::remove(SeqPos pos)
{
	if (isFull())
	{
		cout << "表满" << endl;
		return;
	}
	if (pos < 0 || pos > last - 1)
	{
		cout << "非法位置" << endl;
		return;
	}
	for (SeqPos i = pos; i < last - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	last--;
}

template<typename T>
T SeqList<T>::retrieve(SeqPos pos)
{
	if (pos < 0 || pos > last - 1)
	{
		cout << "非法位置" << endl;
	}
	return data[pos];
}

template<typename T>
SeqPos SeqList<T>::find(T x)
{
	SeqPos r = INVALID_POSITION;
	for (int i = 0; i < last; ++i)
	{
		if (retrieve(i) == x)
		{
			r = i;
			break;
		}
	}
	return r;
}

template<typename T>
SeqPos SeqList<T>::prev(SeqPos pos)
{
	/* 只允许对表头以外的结点求前驱 */
	if (pos < 1 || pos > last - 1)
	{
		cout << "非法位置" << endl;
		return INVALID_POSITION;
	}
	return pos - 1;
}

template<typename T>
SeqPos SeqList<T>::next(SeqPos pos)
{
	/* 只允许对表尾以外的结点求后继 */
	if (pos < 0 || pos > last - 2)
	{
		cout << "非法位置" << endl;
		return INVALID_POSITION;
	}
	return pos + 1;
}

template<typename T>
SeqPos SeqList<T>::front()
{
	if (isEmpty())
	{
		return INVALID_POSITION;
	}
	return 0;
}

template<typename T>
SeqPos SeqList<T>::back()
{
	if (isEmpty())
	{
		return INVALID_POSITION;
	}
	return last - 1;
}

template<typename T>
SeqList<T>& SeqList<T>::removeGiven(T x)
{
	if (isEmpty())
	{
		return *this;
	}
	SeqPos i = front();
	while (i != last)
	{
		if (retrieve(i) == x)
		{
			remove(i);
		}
		else
		{
			i++;
		}
	}
	return *this;
}

template<typename T>
SeqList<T>& SeqList<T>::removeDuplicate()
{
	if (isEmpty())
	{
		return *this;
	}
	T temp = retrieve(0);
	for (SeqPos i = 1; i < last; ++i)
	{
		if (retrieve(i) == temp)
		{
			remove(i);
			i--;
		}
		temp = retrieve(i);
	}

	return *this;
}

template<typename T>
SeqList<T>& SeqList<T>::reverse()
{
	if (isEmpty())
	{
		return *this;
	}
	T ori[this->length()];
	memcpy(ori, data, sizeof(T)*length());
	this->last = 0;
	for (SeqPos i = sizeof(ori)/sizeof(T) - 1; i >= 0; --i)
	{
		this->append(ori[i]);
	}
	return *this;
}

template<typename T>
SeqList<T>& SeqList<T>::leftShift(int k)
{
	int len = length();
	if (len == 0)
	{
		return *this;
	}
	k = k%len;

	T ori[this->length()];
	memcpy(ori, data, sizeof(T)*length());
	this->last = 0;

	for (SeqPos i = k; i < sizeof(ori)/sizeof(T); ++i)
	{
		this->append(ori[i]);
	}
	for (SeqPos i = 0; i < k; ++i)
	{
		this->append(ori[i]);
	}
	return *this;
}

template<typename T>
SeqList<T>& SeqList<T>::rightShift(int k)
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
SeqList<T> SeqList<T>::merge(SeqList<T>& L)
{
	SeqList<T> R;
	SeqPos i, j;
	i = 0;
	j = 0;
	while (i != this->last && j != L.last)
	{
		if (this->retrieve(i) < L.retrieve(j))
		{
			R.append(this->retrieve(i));
			i++;
		}
		else
		{
			R.append(L.retrieve(j));
			j++;
		}
	}
	while (i != this->last)
	{
		R.append(this->retrieve(i));
		i++;
	}
	while (j != L.last)
	{
		R.append(L.retrieve(j));
		j++;
	}
	return R;
}

#endif //HW1_SEQ_LIST_H
