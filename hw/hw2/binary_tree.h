#ifndef HW2_BINARY_TREE_H
#define HW2_BINARY_TREE_H

#include "stack.h"
#include "queue.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#define PLACE_HOLDER 36    // 占位符‘$’的ASCII码值，不允许将36作为二叉树结点的值
#define MAX_LEVEL_NUM 20    // 二叉树的最大高度为20
#define MAX_WIDTH 200        // 二叉树的最大宽度为200

using namespace std;

template<typename T>
class Node
{
public:
	T data;
	Node *left;
	Node *right;

	Node() : left(NULL), right(NULL)
	{
	}

	void visit()
	{
		cout << data << ' ';
	}
};

template<typename T>
class BinTree
{
public:
	Node<T> *root;
	vector<T> preOrderSeq;    // 保存树的先序遍历序列
	vector<T> inOrderSeq;    // 中序遍历序列
	vector<T> postOrderSeq;    // 后序遍历序列
	vector<T> levelOrderSeq;// 层序遍历序列

	BinTree();
	void create(vector<T> src);    // 利用可迭代对象src中的元素构建二叉树
	bool isEmpty();    // 是否为空树

	void show()    // 显示二叉树
	{
		/* 递归地打印二叉树，打印格式为
		 * A(B,C)
		 * 其中A为当前节点，B为A的左子树，C为A的右子树*/
		show(root);    // 调用带参数的protected同名函数，以实现递归，同时确保类的实例不需要传入参数
		cout << endl;
	};

	void preOrder()    // 先序遍历-递归
	{
		preOrderSeq.clear();
		preOrder(root);
		cout << endl;
	};

	void inOrder()    // 中序遍历-递归
	{
		inOrderSeq.clear();
		inOrder(root);
		cout << endl;
	};

	void postOrder()    // 后序遍历-递归
	{
		postOrderSeq.clear();
		postOrder(root);
		cout << endl;
	};
	void preOrderNonRec();    // 先序遍历-非递归
	void inOrderNonRec();    // 中序遍历-非递归
	void postOrderNonRec();   // 后序遍历-非递归
	void levelOrder();        // 层序遍历
	bool isComplete();        // 是否为完全二叉树
	int width()               // 计算二叉树的宽度
	{
		return width(root);
	}
	int newWidth();

protected:
	/*供public递归函数调用*/
	void show(Node<T> *pNode);
	void preOrder(Node<T> *pNode);
	void inOrder(Node<T> *pNode);
	void postOrder(Node<T> *pNode);
	int width(Node<T> *pNode);
};

template<typename T>
BinTree<T>::BinTree()
{
	root = NULL;
}

template<typename T>
void BinTree<T>::create(vector<T> src)
{
	if (src.empty())
		return;
	size_t size = src.size();
	Node<T> *ptrs[size];
	memset(ptrs, 0, sizeof(ptrs));    // 初始化为NULL
	for (size_t i = 0; i < size; i++)
	{
		if (src[i] != PLACE_HOLDER)
		{
			Node<T> *node = new Node<T>;
			node->data = src[i];
			ptrs[i] = node;
			if (i == 0)
			{
				root = node;
			}
			else if (i%2 == 1)
			{
				ptrs[i/2]->left = node;
			}
			else
			{
				ptrs[i/2 - 1]->right = node;
			}
		}
	}
}

template<typename T>
bool BinTree<T>::isEmpty()
{
	return root == NULL;
}

template<typename T>
void BinTree<T>::show(Node<T> *pNode)
{
	if (pNode != NULL)
	{
		cout << pNode->data;
		if (!pNode->left && !pNode->right)
			return;
		cout << '(';
		if (pNode->left)
			show(pNode->left);
		cout << ',';
		if (pNode->right)
			show(pNode->right);
		cout << ')';
	}
}

template<typename T>
void BinTree<T>::preOrder(Node<T> *pNode)
{
	if (pNode)
	{
		pNode->visit();
		preOrderSeq.push_back(pNode->data);
		preOrder(pNode->left);
		preOrder(pNode->right);
	}
}

template<typename T>
void BinTree<T>::inOrder(Node<T> *pNode)
{
	if (pNode)
	{
		inOrder(pNode->left);
		pNode->visit();
		inOrderSeq.push_back(pNode->data);
		inOrder(pNode->right);
	}
}

template<typename T>
void BinTree<T>::postOrder(Node<T> *pNode)
{
	if (pNode)
	{
		postOrder(pNode->left);
		postOrder(pNode->right);
		pNode->visit();
		postOrderSeq.push_back(pNode->data);
	}
}

template<typename T>
void BinTree<T>::preOrderNonRec()
{
	if (isEmpty())
	{
		cout << endl;
		return;
	}
	preOrderSeq.clear();    // 清空先序序列
	Stack<Node<T> *> s;    // 栈的实例，存储结点指针
	Node<T> *p = root;
	while (p != NULL || !s.isEmpty())
	{
		if (p != NULL)
		{
			p->visit();
			preOrderSeq.push_back(p->data);
			s.push(p);
			p = p->left;
		}
		else
		{
			p = s.pop();
			p = p->right;
		}
	}
	cout << endl;
}

template<typename T>
void BinTree<T>::inOrderNonRec()
{
	if (isEmpty())
	{
		cout << endl;
		return;
	}
	inOrderSeq.clear();
	Stack<Node<T> *> s;
	Node<T> *p = root;
	while (p != NULL || !s.isEmpty())
	{
		if (p != NULL)
		{
			s.push(p);
			p = p->left;
		}
		else
		{
			p = s.pop();
			p->visit();
			inOrderSeq.push_back(p->data);
			p = p->right;
		}
	}
	cout << endl;
}

template<typename T>
void BinTree<T>::postOrderNonRec()
{
	using pairNB = pair<Node<T> *, bool>;
	/* pairNB.first: Node<T> *, 结点指针
	 * pairNB.second: bool, 结点的右子树是否已被遍历*/
	if (isEmpty())
	{
		cout << endl;
		return;
	}
	postOrderSeq.clear();
	Stack<pairNB> s;
	Node<T> *p = root;
	while (p != NULL || !s.isEmpty())
	{
		if (p != NULL)
		{
			pairNB temp(p, false);
			s.push(temp);
			p = p->left;
		}
		else
		{
			pairNB top = s.pop();
			if (top.second == false)    // 该结点的右子树尚未遍历
			{
				p = top.first->right;
				top.second = true;    // 修改为已遍历后压回栈
				s.push(top);
			}
			else if (top.second == true)
			{
				top.first->visit();    // 右子树遍历完才能访问根节点
				postOrderSeq.push_back(top.first->data);
			}
		}
	}
	cout << endl;
}

template<typename T>
void BinTree<T>::levelOrder()
{
	if (isEmpty())
	{
		cout << endl;
		return;
	}
	levelOrderSeq.clear();
	Queue<Node<T> *> q;
	q.push(root);
	Node<T> *p;
	while (!q.isEmpty())
	{
		p = q.pop();
		p->visit();
		levelOrderSeq.push_back(p->data);
		if (p->left)
			q.push(p->left);
		if (p->right)
			q.push(p->right);
	}
	cout << endl;
}

template<typename T>
bool BinTree<T>::isComplete()
{
	/*基于层序遍历判定是否为完全二叉树*/
	if (isEmpty())
		return true;    // 空树也是完全二叉树
	Queue<Node<T> *> q;
	q.push(root);
	Node<T> *p;
	while (!q.isEmpty())
	{
		p = q.pop();
		if (p != NULL)
		{
			q.push(p->left);
			q.push(p->right);
		}
		else    // 若为完全二叉树，则遍历已经结束
		{
			while (!q.isEmpty())
			{
				p = q.pop();
				if (p != NULL)    // 仍有非空结点，说明不是完全二叉树
					return false;
			}
		}
	}
	return true;
}

template<typename T>
int BinTree<T>::width(Node<T> *pNode)
{
	/*基于层序遍历计算树的宽度*/
	if (pNode == NULL)
		return 0;
	int w[MAX_LEVEL_NUM];    // 存储每层的结点个数
	memset(w, 0, sizeof(w));
	w[0] = 1;
	Queue<Node<T> *> q;
	q.push(root);
	Node<T> *p;
	int cnt = 0;
	int twos = 2;
	int currWidth = 0;
	int maxWidth = 1;
	Node<T> *ptrs[MAX_WIDTH];
	memset(ptrs, 0, sizeof(ptrs));
	while (!q.isEmpty())
	{
		if (cnt >= twos)
		{
			for (int i = 0; i < twos; i++)
			{
				if (ptrs[i] != NULL)
					currWidth++;
			}
			if (currWidth > maxWidth)
				maxWidth = currWidth;
			cnt = 0;
			twos *= 2;
			memset(ptrs, 0, sizeof(ptrs));
			currWidth = 0;
		}
		p = q.pop();
		if (p != NULL)
		{
			{
				q.push(p->left);
				ptrs[cnt++] = p->left;
				q.push(p->right);
				ptrs[cnt++] = p->right;
			}
		}
	}
	return maxWidth;
}

#include <queue>

template<typename T>
int BinTree<T>::newWidth()
{
	queue<Node<T> *> q;
	q.push(root);
	int width;
	int maxWidth = 0;
	while (!q.empty())
	{
		int size = q.size();
		width = 0;
		while (size != 0) // 按层处理
		{
			Node<T> *p = q.front(); q.pop();
			if (p != NULL)
			{
				q.push(p->left);
				q.push(p->right);
				width++;
			}
			size--;
		}
		maxWidth = width > maxWidth ? width : maxWidth;
	}
	return maxWidth;
}


#endif //HW2_BINARY_TREE_H
