#ifndef LAB2_HUFFMAN_TREE_H
#define LAB2_HUFFMAN_TREE_H

#include "store.h"
#include <iostream>
#include <cstdint>

#define STATIC_NULL -1

const int MAX_NODE_NUM = 2*(CHAR_NUM) - 1;

class HTNode    // 哈夫曼树结点
{
public:
	char ch;    // 字符字面量
	size_t weight;    // 字符权值
	int parent;
	int lChild;
	int rChild;
};

class HuffmanTree
{
public:
	int leafNum;    // 叶结点的个数|实际编码字符数
	int size;        // 有效结点的个数
	int root;        // 整棵树的根节点 i.e. 2*leafNum - 2
	HTNode nodes[MAX_NODE_NUM];    // 结点域，提供最坏情况下的结点数量

	HuffmanTree(CFPair *bucket, int n);    // 初始化，并利用 bucket 构建最初的 leafNum 个树
	void merge();                        // 对二叉树集合进行 leafNum - 1 次合并
	void select2Min(int cur, int& p1, int& p2);    // 从二叉树集合[0, cur-1]中选出权值最小的两棵，赋值到 p1，p2 中
};

#endif //LAB2_HUFFMAN_TREE_H
