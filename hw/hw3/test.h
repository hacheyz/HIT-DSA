#ifndef HW3_TEST_H
#define HW3_TEST_H

#include "graph.h"

template<typename V, typename E, bool directed>
void testMatrixGraph(Matrix::Graph<V, E, directed> G);
template<typename V, typename E, bool directed>
void testListGraph(List::Graph<V, E, directed> G);
template<typename T>
void printVec(vector<T> v);


template<typename V, typename E, bool directed>
void testMatrixGraph(Matrix::Graph<V, E, directed> G)
{
	cout << "-----邻接矩阵存储法：测试开始-----" << endl;
	if (directed)
		cout << "·建立了一个有向图，邻接矩阵如下：" << endl;
	else
		cout << "·建立了一个无向图，邻接矩阵如下：" << endl;
	G.show();
	cout << "·转换为以邻接表存储，邻接表如下：" << endl;
	G.toList().show();
	cout << "(下面所有操作仍基于邻接矩阵进行)" << endl;
	cout << "·深度优先搜索算法" << endl;
	G.DFS();
	cout << "深度优先森林: ";
	G.DFSTree.show();
	cout << "深度优先序列：";
	printVec(G.DFSSeq);
	cout << "深度优先编号：";
	printVec(G.DFSNum);
	cout << "·深度优先搜索算法（非递归）" << endl;
	G.DFS();
	cout << "深度优先森林: ";
	G.DFSTree.show();
	cout << "深度优先序列：";
	printVec(G.DFSSeq);
	cout << "深度优先编号：";
	printVec(G.DFSNum);
	cout << "·广度优先搜索算法" << endl;
	G.BFS();
	cout << "广度优先森林：";
	G.BFSTree.show();
	cout << "广度优先序列：";
	printVec(G.BFSSeq);
	cout << "广度优先编号：";
	printVec(G.BFSNum);
	cout << "-----邻接矩阵存储法：测试结束-----" << endl << endl;
}

template<typename V, typename E, bool directed>
void testListGraph(List::Graph<V, E, directed> G)
{
	cout << "-----邻接表存储法：测试开始-----" << endl;
	if (directed)
		cout << "·建立了一个有向图，邻接表如下：" << endl;
	else
		cout << "·建立了一个无向图，邻接表如下：" << endl;
	G.show();
	cout << "·转换为以邻接矩阵存储，邻接矩阵如下：" << endl;
	G.toMatrix().show();
	cout << "(下面所有操作仍基于邻接表进行)" << endl;
	cout << "·深度优先搜索算法" << endl;
	G.DFS();
	cout << "深度优先森林: ";
	G.DFSTree.show();
	cout << "深度优先序列：";
	printVec(G.DFSSeq);
	cout << "深度优先编号：";
	printVec(G.DFSNum);
	cout << "·深度优先搜索算法（非递归）" << endl;
	G.DFS();
	cout << "深度优先森林: ";
	G.DFSTree.show();
	cout << "深度优先序列：";
	printVec(G.DFSSeq);
	cout << "深度优先编号：";
	printVec(G.DFSNum);
	cout << "·广度优先搜索算法" << endl;
	G.BFS();
	cout << "广度优先森林：";
	G.BFSTree.show();
	cout << "广度优先序列：";
	printVec(G.BFSSeq);
	cout << "广度优先编号：";
	printVec(G.BFSNum);
	if (!directed)
		cout << "对于无向图，计算每个顶点的度：" << endl;
	else
		cout << "对于有向图，计算每个顶点的入度、出度和度" << endl;
	G.calcDeg();
	cout << "-----邻接表存储法：测试结束-----" << endl << endl;
}

template<typename T>
void printVec(vector<T> v)
{
	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << *it << ' ';
	}
	cout << endl;
}

#endif //HW3_TEST_H