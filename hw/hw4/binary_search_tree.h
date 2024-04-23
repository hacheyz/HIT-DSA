#ifndef HW4_BINARY_SEARCH_TREE_H
#define HW4_BINARY_SEARCH_TREE_H

#include "record.h"
#include <vector>
#include <cstddef>

using namespace std;

template<typename Keytype>
class BSTNode
{
public:
	Record<Keytype> data;
	BSTNode<Keytype> *lchild, *rchild;

	BSTNode(Record<Keytype> r) : data(r), lchild(NULL), rchild(NULL)
	{
	}
};

template<typename Keytype>
class BST
{
	using Node = BSTNode<Keytype>;
	using Rec = Record<Keytype>;
	using Vector = vector<Rec>;
public:
	BST(); // BST 的初始化
	void create(Vector input); // 从 input 构造一个 BST
	void insert(Rec r); // 插入记录 r
	void remove(Keytype k); // 移除关键字为 k 的记录
	BSTNode<Keytype> *search(Keytype k); // 查找关键字为 k 的记录
	Vector sort(); // 返回 BST 的中序序列
	void countSearch(double& succAsl, double& failAsl); // 计算查找成功和查找失败的平均查找长度
private:
	Node *root;
	size_t count; // 查找次数计数器, 每次开始查找前清零
	bool isEmpty(); // BST 是否非空
	void insert(Rec r, Node *& pNode); // 重载了 public insert, 以支持递归
	void remove(Keytype k, Node *& pNode); // 重载了 public remove, 以支持递归
	BSTNode<Keytype> *search(Keytype k, Node *pNode); // 重载了 public search, 以支持递归
	void sort(Vector& sorted, Node *pNode); // 重载了 public sort, 以支持递归
};

template<typename Keytype>
BST<Keytype>::BST()
{
	root = NULL;
}

template<typename Keytype>
bool BST<Keytype>::isEmpty()
{
	return (root == NULL);
}

template<typename Keytype>
void BST<Keytype>::create(Vector input)
{
	for (auto it = input.begin(); it != input.end(); it++)
	{
		insert(*it);
	}
}

template<typename Keytype>
void BST<Keytype>::insert(Rec r)
{
	insert(r, root);
}

template<typename Keytype>
void BST<Keytype>::insert(Rec r, Node *& pNode)
{
	if (pNode == NULL)
	{
		pNode = new Node(r);
		return;
	}
	if (r.key < pNode->data.key)
		insert(r, pNode->lchild);
	else if (r.key > pNode->data.key)
		insert(r, pNode->rchild);
	/* 若存在 pNode->data.key == r.key, 返回
	 * NOTE: 不允许记录的关键字重复 */
}

template<typename Keytype>
void BST<Keytype>::remove(Keytype k)
{
	remove(k, root);
}

template<typename Keytype>
void BST<Keytype>::remove(Keytype k, BST::Node *& pNode)
{
	if (pNode == NULL)
		return;
	if (k < pNode->data.key)
		remove(k, pNode->lchild);
	else if (k > pNode->data.key)
		remove(k, pNode->rchild);
	else
	{
		Node *toRmv = pNode;
		if (pNode->lchild == NULL) // 左子树为空
		{
			pNode = pNode->rchild; // 继承右链
			delete toRmv;
		}
		else if (pNode->rchild == NULL) // 右子树为空
		{
			pNode = pNode->lchild; // 继承左链
			delete toRmv;
		}
		else // pNode 有左右子树
		{
			Node *p = pNode->lchild; // 进入左子树
			while (p->rchild) // 在左子树中找最右结点, 即找左子树的最大结点
				p = p->rchild;
			pNode->data = p->data; // 用 p 的数据覆盖 pNode
			toRmv = p; // 从而将删除 pNode 转移为了删除 p
			delete toRmv;
		}
	}
}

template<typename Keytype>
BSTNode<Keytype> *BST<Keytype>::search(Keytype k)
{
	count = 0; // 查找次数计数器
	return search(k, root);
}

template<typename Keytype>
BSTNode<Keytype> *BST<Keytype>::search(Keytype k, Node *pNode)
{
	count++;
	if (pNode == NULL)
		return NULL;
	if (k < pNode->data.key) // k 比当前结点关键字小
		return search(k, pNode->lchild); // 前往左子树寻找
	else if (k > pNode->data.key)
		return search(k, pNode->rchild);
	else // k == pNode->data.key
		return pNode;
}

template<typename Keytype>
vector<Record<Keytype> > BST<Keytype>::sort()
{
	Vector sorted;
	sort(sorted, root);
	return sorted;
}

template<typename Keytype>
void BST<Keytype>::sort(Vector& sorted, Node *pNode)
{
	/* 递归地生成中序遍历序列 */
	if (pNode != NULL)
	{
		sort(sorted, pNode->lchild);
		sorted.push_back(pNode->data);
		sort(sorted, pNode->rchild);
	}
}

template<typename Keytype>
void BST<Keytype>::countSearch(double& succAsl, double& failAsl)
{
	/* 奇数查找成功 */
	size_t succSum = 0;
	for (int i = 1; i < 2048; i += 2)
	{
		search(i);
		succSum += count;
	}
	succAsl = (double)succSum/RECORD_LENGTH;
	/* 偶数查找失败 */
	size_t failSum = 0;
	for (int i = 0; i < 2048; i += 2)
	{
		search(i);
		failSum += count;
	}
	failAsl = (double)failSum/RECORD_LENGTH;
}

#endif //HW4_BINARY_SEARCH_TREE_H
