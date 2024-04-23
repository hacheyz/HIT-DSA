#ifndef HW3_GRAPH_H
#define HW3_GRAPH_H

#include "forest.h"
#include <iostream>
#include <cstddef>
#include <vector>

using namespace std;

template<typename V, typename E, bool directed = false>
class vGraph // 抽象类，声明图的接口
{
public:
	virtual size_t nodeNum() = 0; // 返回顶点个数
	virtual size_t edgeNum() = 0; // 对无向图，返回边的个数；对有向图，返回弧的个数
	virtual void create() = 0;	// 图的建立算法
	virtual void show() = 0; // 打印图
	virtual void addNode(V v) = 0; // 新增一个顶点
	virtual void addNodesFrom(V *v, size_t vNum) = 0; // 从数组新增 vNum 个顶点
	virtual void delNode(V v) = 0; // 删去一个顶点
	virtual void addEdge(V v1, V v2, E e = 1) = 0; // 新增一条边
	virtual void delEdge(V v1, V v2) = 0; // 删去一条边
	virtual void getSucc(V v) = 0; // 打印 v 所有的后继顶点
	virtual void getPred(V v) = 0; // 打印 v 所有的前驱节点
	virtual bool isEdge(V v1, V v2) = 0; // 判断 (v1,v2) 是否是一条边
	virtual void DFS() = 0; // 深度优先搜索
	virtual void DFSNonRec() = 0; // 深度优先搜索（非递归）
	virtual void BFS() = 0; // 广度优先搜索
};

namespace List
{
	template<typename V, typename E, bool directed>
	class Graph; // 先声明一下 List::Graph，供 Matrix::Graph, EdgeNode, Vertex 声明友元
}

namespace Matrix
{
	template<typename V, typename E, bool directed = false>
	class Graph : public vGraph<V, E, directed> // 图的邻接矩阵实现
	{
		friend List::Graph<V, E, directed>; // 供转换用
	public:
		vector<size_t> DFSNum; // 顶点的先深编号
		vector<V> DFSSeq; // 顶点的先深序列
		Forest<V> DFSTree; // 顶点的深度优先生成树
		vector<size_t> BFSNum; // 顶点的先广编号
		vector<V> BFSSeq; // 顶点的先广序列
		Forest<V> BFSTree; // 顶点的广度优先生成树
		size_t nodeNum(); // 返回顶点个数
		size_t edgeNum(); // 对无向图，返回边的个数；对有向图，返回弧的个数
		void create(); // 图的建立算法
		void show(); // 打印邻接矩阵
		void addNode(V v); // 新增一个顶点
		void addNodesFrom(V *v, size_t vNum); // 从数组新增 vNum 个顶点
		void delNode(V v); // 删去一个顶点
		void addEdge(V v1, V v2, E e = 1); // 新增一条边
		void delEdge(V v1, V v2); // 删去一条边
		void getSucc(V v); // 打印 v 所有的后继顶点
		void getPred(V v); // 打印 v 所有的前驱节点
		bool isEdge(V v1, V v2); // 判断 (v1,v2) 是否是一条边
		List::Graph<V, E, directed> toList(); // 邻接矩阵表示法->邻接表表示法
		void DFS(); // 深度优先遍历（递归）
		void DFSNonRec(); // 深度优先遍历（非递归）
		void BFS(); // 广度优先遍历
		void calcDeg(); // 打印各顶点的度，根据 directed 不同，实现不同
	private:
		vector<vector<E> > mat; // 邻接矩阵-边表
		vector<V> vertex; // 顶点表
		vector<bool> visited; // 保存结点是否被访问过
		/* NOTE: 这里使用 vector<bool> 没有危害，因为程序不会取元素的指针*/
		typename vector<V>::iterator findVertex(V v); // 返回顶点的迭代器
		void initDFS(); // 清空先深序列、编号、visited 数组和森林，为先深森林导入顶点
		void initBFS(); // 清空先广序列、编号、visited 数组和森林，为先广森林导入顶点
		void DFSi(size_t i, size_t& cnt); // 从顶点 i 出发的一次先深搜索，供 public 函数 DFS 调用
		void BFSi(size_t i, size_t& cnt); // 从顶点 j 出发的一次先广搜索，供 public 函数 BFS 调用
	};
}

namespace List
{
	template<typename V, typename E, bool directed = false>
	class EdgeNode
	{
		friend class List::Graph<V, E, directed>;

	public:
		EdgeNode(size_t v, E e) : v(v), e(e), next(NULL)
		{
		};
	private:
		size_t v; // 边终点的下标
		E e; // 边权值
		EdgeNode<V, E, directed> *next;	// 下一条边
	};

	template<typename V, typename E, bool directed = false>
	class Vertex
	{
		friend class List::Graph<V, E, directed>;

	public:
		Vertex(V v) : v(v), firstEdge(NULL)
		{
		};
	private:
		V v; // 顶点的值
		EdgeNode<V, E, directed> *firstEdge; // 第一条边
	};

	template<typename V, typename E, bool directed = false>
	class Graph : public vGraph<V, E, directed> // 图的邻接表实现
	{
		friend Matrix::Graph<V, E, directed>; // 供转换用
		using Vert = Vertex<V, E, directed>;
		using Edge = EdgeNode<V, E, directed>;
	public:
		vector<size_t> DFSNum; // 顶点的先深编号
		vector<V> DFSSeq; // 顶点的先深序列
		Forest<V> DFSTree; // 顶点的深度优先生成树
		vector<size_t> BFSNum; // 顶点的先广编号
		vector<V> BFSSeq; // 顶点的先广序列
		Forest<V> BFSTree; // 顶点的广度优先生成树
		size_t nodeNum(); // 返回顶点个数
		size_t edgeNum(); // 对无向图，返回边的个数；对有向图，返回弧的个数
		void create(); // 图的建立算法
		void show(); // 打印邻接表
		void addNode(V v); // 新增一个顶点
		void addNodesFrom(V *v, size_t vNum); // 从数组新增 vNum 个顶点
		void delNode(V v); // 删去一个顶点
		void addEdge(V v1, V v2, E e = 1); // 新增一条边
		void delEdge(V v1, V v2); // 删去一条边
		void getSucc(V v); // 打印 v 所有的后继顶点
		void getPred(V v); // 打印 v 所有的前驱节点
		bool isEdge(V v1, V v2); // 判断 (v1,v2) 是否是一条边
		Matrix::Graph<V, E, directed> toMatrix(); // 邻接表表示法->邻接矩阵表示法
		void DFS(); // 深度优先遍历（递归）
		void DFSNonRec(); // 深度优先遍历（非递归）
		void BFS(); // 广度优先遍历（递归）
		void calcDeg(); // 打印各顶点的度，根据 directed 不同，实现不同
	private:
		vector<Vert> vertex; // 顶点表
		vector<bool> visited; // 保存结点是否被访问过
		typename vector<Vert>::iterator findVertex(V v); // 返回 vertex 中 v 的迭代器
		void initDFS(); // 清空先深序列、编号和森林，为先深森林导入顶点
		void DFSi(size_t i, size_t& cnt); // 供 public 函数 DFS 调用
		void initBFS(); // 清空先广序列、编号和森林，为先广森林导入顶点
		void BFSi(size_t i, size_t& cnt); // 供 public 函数 BFS 调用
	};
}

#endif //HW3_GRAPH_H