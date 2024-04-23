#ifndef HW2_BINARY_TREE_H
#define HW2_BINARY_TREE_H

#include "stack.h"
#include <iostream>
#include <vector>

template<typename T>
class BinaryTree
{
public:
	T data;
	BinaryTree *left;
	BinaryTree *right;

	BinaryTree(T data) : data(data), left(NULL), right(NULL)
	{
	}

	std::vector<int> inOrder();
};

template<typename T>
std::vector<int> BinaryTree<T>::inOrder()
{
	std::vector<int> inOrderSeq;
	Stack<BinaryTree<T> *> s;
	BinaryTree<T> *p = this;
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
			inOrderSeq.push_back(p->data);
			p = p->right;
		}
	}
	return inOrderSeq;
}


#endif //HW2_BINARY_TREE_H
