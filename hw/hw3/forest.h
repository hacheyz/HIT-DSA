#ifndef HW3_FOREST_H
#define HW3_FOREST_H

#include <iostream>
#include <vector>

#define STATIC_NULL -1

using namespace std;

template<typename T>
class Node // 孩子兄弟父亲表示法
{
public:
	T data;
	int child;
	int sibling;
	int parent;

	Node(T data) :
			data(data),
			child(STATIC_NULL),
			sibling(STATIC_NULL),
			parent(STATIC_NULL)
	{
	}
};

template<typename T>
class Forest
{
public:
	vector<int> root; // 存储森林中每棵树的根
	vector<Node<T>> node;

	Forest()
	{
	}

	void destroy();

	void show()
	{
		/* 递归地打印森林，打印格式为
		 * P1(S1,S2,...),P2(...),...
		 * 其中P1为第一棵树的父节点，S1,S2,...为P1的孩子，以','分隔
		 * P2,...为其他树*/
		root.clear();
		for (int i = 0; i < node.size(); i++)
		{
			if (node[i].parent == STATIC_NULL)
				root.push_back(i);
		}
		for (auto it = root.begin(); it != root.end(); it++)
		{
			show(*it);
			if (it + 1 != root.end())
				cout << ',';
		}
		cout << endl;
	}

	void importNodesFrom(vector<T> vertex); // 从图导入结点
	void addSon(int i, int j); // 将下标为 j 的结点设置为下标为 i 的结点的孩子

private:
	void show(int pNode); // 供 public show 调用
};

template<typename T>
void Forest<T>::destroy()
{
	root.clear();
	node.clear();
}

template<typename T>
void Forest<T>::show(int pNode)
{
	if (pNode != STATIC_NULL)
	{
		cout << node[pNode].data;
		int p = node[pNode].child;
		if (p == STATIC_NULL)
			return;
		cout << '(';
		while (p != STATIC_NULL)
		{
			show(p);
			if (node[p].sibling != STATIC_NULL)
				cout << ',';
			p = node[p].sibling;
		}
		cout << ')';
	}
}

template<typename T>
void Forest<T>::importNodesFrom(vector<T> vertex)
{
	if (!vertex.empty())
	{
		for (auto it = vertex.begin(); it != vertex.end(); it++)
		{
			node.push_back(Node<T>(*it));
		}
	}
}

template<typename T>
void Forest<T>::addSon(int i, int j)
{
	if (node[i].child == STATIC_NULL)
	{
		node[i].child = j;
		node[j].parent = i;
	}
	else
	{
		int p = node[i].child;
		while (node[p].sibling != STATIC_NULL)
		{
			p = node[p].sibling;
		}
		node[p].sibling = j;
		node[j].parent = i;
	}
}

#endif //HW3_FOREST_H