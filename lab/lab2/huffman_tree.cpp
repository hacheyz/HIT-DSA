#include "huffman_tree.h"

using namespace std;

HuffmanTree::HuffmanTree(CFPair *bucket, int n)
{
	leafNum = n;
	size = 2*n - 1;
	root = 2*n - 2;
	/* 初始化 */
	for (int i = 0; i < size; i++)
	{
		nodes[i].ch = 0;
		nodes[i].weight = 0;
		nodes[i].parent = STATIC_NULL;
		nodes[i].lChild = STATIC_NULL;
		nodes[i].rChild = STATIC_NULL;
	}
	/* 给前 n 个结点赋字符和权值 */
	for (int i = 0; i < n; i++)
	{
		nodes[i].ch = bucket[i].ch;
		nodes[i].weight = bucket[i].freq;
	}
}

void HuffmanTree::merge()
{
	/* 将[0,i-1]内的树进行合并 */
	for (int i = leafNum; i < size; i++)
	{
		int p1, p2;
		select2Min(i, p1, p2);
		nodes[p1].parent = i;
		nodes[p2].parent = i;
		nodes[i].lChild = p1;
		nodes[i].rChild = p2;
		nodes[i].weight = nodes[p1].weight + nodes[p2].weight;
	}
}

void HuffmanTree::select2Min(int cur, int& p1, int& p2)
{
	int min1, min2;
	size_t w1, w2;
	min1 = min2 = 0;
	w1 = w2 = SIZE_MAX;
	for (int i = 0; i < cur; i++)
	{
		/* 考查的是未合并的树的根节点的权值，因为已合并的树不能再次合并 */
		if (nodes[i].parent == STATIC_NULL)
		{
			if (nodes[i].weight < w1)
			{
				min1 = i;
				w1 = nodes[i].weight;
			}
			else if (nodes[i].weight >= w1 && nodes[i].weight < w2)
			{
				min2 = i;
				w2 = nodes[i].weight;
			}
		}
	}
	p1 = min1;
	p2 = min2;
}