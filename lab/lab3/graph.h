#ifndef LAB3_GRAPH_H
#define LAB3_GRAPH_H

#include "stack.h"
#include "binary_tree.h"
#include <iostream>
#include <cstddef>
#include <vector>
#include <cstring>
#include <queue>
#include <time.h>

#define INFTY 0x7fff // 无穷大
#define TEST_NUM 100000 // Dijkstra 优化算法测试组数

using namespace std;

template<typename T>
T sum(vector<T> vec)
{
	T summ = 0;
	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		summ += *it;
	}
	return summ;
}

template<typename V, typename E>
class Graph // 有向图的邻接矩阵实现
{
public:
	vector<V> vertex; // 顶点表
	vector<vector<E> > mat; // 邻接矩阵-边表
	int nodeNum; // 顶点个数
	int edgeNum; // 弧的个数
	void create(); // 图的建立算法
	void show(); // 打印顶点集和邻接矩阵
	void transpose(); // 返回 vertex 与 this->vertex 相同，mat 为 this->mat 转置的图
	void singleSrc(int src); // 单源最短路径，基于 Dijkstra 算法（第1题）
	void floydWarshall(); // 全局最短路径的 Floyd-Warshall 算法（第2题）
	void singleTarget(int dest); // 单目标最短路径问题（第3题）
	void singlePair(int u, int v); // 单顶点对间最短路路径问题（第4题）
	void testAll();
	void warshall(); // Warshall 算法求可达矩阵（第6题）
	void singleSrcHeapOpt(int src); // 单源最短路径，基于堆优化 Dijkstra 算法（第7题）
private:
	/**无打印，不提供对外接口*/
	void dijkstra(int src); // 单源最短路径的 Dijkstra 算法，不含打印结果，刷新数组 D，P，S
	void dijkstraHeapOpt(int src); // 堆优化 Dijkstra 算法，不含打印结果
	/** 辅助数组 */
	/* 存放源点到所有顶点的最短路径长度 */
	vector<E> D; // D[i] = mat[src][i]
	/* 存放源点到所有顶点的当前最短路径上最后经过的顶点的下标 */
	vector<int> P;
	/* 存放源点和已生成的终点 */
	vector<int> S;
	/* 顶点间的最短距离矩阵 */
	vector<vector<E> > dis;
	/* 最短路径矩阵 */
	vector<vector<int> > path;
	/**辅助函数*/
	/* 补全 src，dest 之间的路径，得到一棵二叉树，二叉树的中序遍历即为 src，dest 之间的路径 */
	BinaryTree<int> *routeTree(int src, int dest);
};

template<typename V, typename E>
void Graph<V, E>::create()
{
	cin >> nodeNum >> edgeNum;
	vertex.resize(nodeNum);
	mat.resize(nodeNum, vector<E>(nodeNum));
	for (int i = 0; i < nodeNum; i++)
	{
		cin >> vertex[i];
	}
	int st, ed;
	E e;
	/* 距离初始化为无穷大，但对角线为 0 */
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			if (i != j)
				mat[i][j] = INFTY;
			else
				mat[i][j] = 0;
		}
	}
	for (int i = 0; i < edgeNum; i++)
	{
		cin >> st >> ed >> e;
		mat[st][ed] = e;
	}
}

template<typename V, typename E>
void Graph<V, E>::show()
{
	cout << "顶点: " << endl;
	for (int i = 0; i < nodeNum; i++)
	{
		cout << vertex[i] << ' ';
	}
	cout << endl;
	cout << "邻接矩阵：" << endl;
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			if (mat[i][j] == INFTY)
				cout << "∞" << ' ';
			else
				cout << mat[i][j] << ' ';
		}
		cout << endl;
	}
}

template<typename V, typename E>
void Graph<V, E>::transpose()
{
	vector<vector<E> > temp(mat);
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			mat[i][j] = temp[j][i];
		}
	}
}

template<typename V, typename E>
void Graph<V, E>::dijkstra(int src)
{
	/** 初始化*/
	if (src < 0 || src > nodeNum - 1) // 越界检测
		throw invalid_argument("Vertex not found");
	D.assign(mat[src].begin(), mat[src].end()); // D[i] = mat[src][i]
	P.assign(nodeNum, src); // P[i] = src
	S.assign(nodeNum, false);
	S[src] = true; // 初态为只有一个源点
	/** 算法主体*/
	do
	{   /* 从 S 之外选取一个顶点 w，使 D[w] 最小 */
		int w = 0;
		while (S[w])
			w++;
		for (int i = 0; i < nodeNum; i++)
		{
			if (!S[i])
				if (D[i] < D[w])
					w = i;
		}
		S[w] = true; // 把 w 加入到集合 S
		/* 调整 D 中记录的从 src 到 V-S 每个顶点的最短距离
		 * 并更新最短路径上该顶点的前一个的顶点 */
		for (int v = 0; v < nodeNum; v++)
		{
			/* 对 V-S 中的顶点，比较经过 w 与否路径的长度 */
			if (!S[v] && D[w] + mat[w][v] < D[v])
			{
				D[v] = D[w] + mat[w][v];
				P[v] = w;
			}
		}
	} /* 重复上述操作，直到 S 中包含 V 的所有顶点为止 */
	while (sum(S) != nodeNum);
}

template<typename V, typename E>
void Graph<V, E>::singleSrc(int src)
{
	dijkstra(src);
	/** 打印结果 */
	for (int i = 0; i < nodeNum; i++)
	{
		if (i == src)
			continue;
		cout << vertex[i] << ": ";
		if (D[i] == INFTY)
		{
			cout << "路不存在" << endl;
		}
		else
		{
			cout << "长度: " << D[i] << " 路径: ";
			Stack<int> s; // 借助栈回溯 P
			int curr = P[i];
			s.push(curr);
			while (curr != src)
			{
				curr = P[curr];
				s.push(curr);
			}
			while (!s.isEmpty())
			{
				cout << vertex[s.pop()] << " —> ";
			}
			cout << vertex[i] << endl;
		}
	}
}

template<typename V, typename E>
void Graph<V, E>::floydWarshall()
{
	/**初始化*/
	dis.resize(nodeNum, vector<E>(nodeNum));
	path.resize(nodeNum, vector<int>(nodeNum));
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			dis[i][j] = mat[i][j];
			path[i][j] = -1;
		}
	}
	/**算法主体*/
	/* 选择中转点，从只使用第一个中转点遍历到能使用所有的点作为中转点 */
	for (int k = 0; k < nodeNum; k++)
	{
		/* 选择源点 */
		for (int i = 0; i < nodeNum; i++)
		{
			/* 选择终点 */
			for (int j = 0; j < nodeNum; j++)
			{
				/* 进行一次试探 */
				if (dis[i][k] + dis[k][j] < dis[i][j])
				{
					dis[i][j] = dis[i][k] + dis[k][j];
					path[i][j] = k;
				}
			}
		}
	}
	/**打印结果*/
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			if (i == j)
				continue;
			cout << vertex[i] << " —> " << vertex[j] << ": ";
			if (dis[i][j] == INFTY)
			{
				cout << "路不存在" << endl;
				continue;
			}
			cout << "长度: " << dis[i][j] << " 路径: ";
			cout << vertex[i] << " —> ";
			/* 如果 i，j 之间不止一个中转点 */
			BinaryTree<int> *tree = routeTree(i, j);
			if (tree != NULL)
			{
				vector<int> transit = tree->inOrder();
				for (auto it = transit.begin(); it != transit.end(); it++)
				{
					cout << vertex[*it] << " —> ";
				}
			}
			cout << vertex[j] << endl;
		}
	}
}

template<typename V, typename E>
void Graph<V, E>::singleTarget(int dest)
{
	transpose(); // 将 this 的矩阵转置
	dijkstra(dest);
	/** 打印结果 */
	for (int i = 0; i < nodeNum; i++)
	{
		if (i == dest)
			continue;
		cout << vertex[i] << ": ";
		if (D[i] == INFTY)
		{
			cout << "路不存在" << endl;
		}
		else
		{
			cout << "长度: " << D[i] << " 路径: ";
			for (int curr = i; curr != dest; curr = P[curr])
			{
				cout << vertex[curr] << " —> ";
			}
			cout << vertex[dest] << endl;
		}
	}
	transpose(); // 恢复
}

template<typename V, typename E>
void Graph<V, E>::singlePair(int u, int v)
{
	dijkstra(u);
	if (D[v] == INFTY)
		cout << "路不存在" << endl;
	cout << "长度: " << D[v] << " 路径: ";
	Stack<int> s; // 借助栈回溯 P
	int curr = P[v];
	s.push(curr);
	while (curr != u)
	{
		curr = P[curr];
		s.push(curr);
	}
	while (!s.isEmpty())
	{
		cout << vertex[s.pop()] << " —> ";
	}
	cout << vertex[v] << endl;
}

template<typename V, typename E>
BinaryTree<int> *Graph<V, E>::routeTree(int src, int dest)
{
	if (path[src][dest] == -1)
		return NULL;
	int transit = path[src][dest];
	BinaryTree<int> *node = new BinaryTree<int>(transit);
	node->left = routeTree(src, transit);
	node->right = routeTree(transit, dest);
	return node;
}

template<typename E>
struct Node // 供优先队列使用
{
	int index;
	E cost;

	Node(int index, E cost) : index(index), cost(cost)
	{
	}

	friend bool operator<(Node n1, Node n2)
	{
		return n1.cost > n2.cost; // 距离小的优先级高
	}
};

template<typename V, typename E>
void Graph<V, E>::warshall()
{
	/**先将邻接矩阵转换为0-1阵*/
	vector<vector<int> > Reach(nodeNum, vector<int>(nodeNum));
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			Reach[i][j] = (mat[i][j] != 0) && (mat[i][j] != INFTY);
		}
	}
	/** 算法主体 */
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			if (Reach[j][i] != 0)
			{
				for (int k = 0; k < nodeNum; k++)
				{
					Reach[j][k] = Reach[j][k] | Reach[i][k];
				}
			}
		}
	}
	/** 打印可达矩阵 */
	for (auto it = Reach.begin(); it != Reach.end(); it++)
	{
		for (auto jt = it->begin(); jt != it->end(); jt++)
		{
			cout << *jt << ' ';
		}
		cout << endl;
	}
}

template<typename V, typename E>
void Graph<V, E>::dijkstraHeapOpt(int src)
{
	/** 初始化*/
	priority_queue<Node<E> > pq;
	if (src < 0 || src > nodeNum - 1) // 越界检测
		throw invalid_argument("Vertex not found");
	D.assign(nodeNum, INFTY); // D[i] = INFTY
	D[src] = 0;
	P.assign(nodeNum, src); // P[i] = src
	S.assign(nodeNum, false); // S[i] = false
	/** 算法主体*/
	pq.push(Node<E>(src, 0)); // 源点入队
	while (!pq.empty())
	{
		int w = pq.top().index; // cost 最小的先出队
		pq.pop();
		if (S[w])
			continue;
		S[w] = true;
		for (int v = 0; v < nodeNum; v++)
		{
			if (!S[v] && D[w] + mat[w][v] < D[v])
			{
				D[v] = D[w] + mat[w][v];
				P[v] = w;
				pq.push(Node<E>(v, D[v]));
			}
		}
	}
}

template<typename V, typename E>
void Graph<V, E>::singleSrcHeapOpt(int src)
{
	dijkstraHeapOpt(src);
	/** 打印结果 */
	for (int i = 0; i < nodeNum; i++)
	{
		if (i == src)
			continue;
		cout << vertex[i] << ": ";
		if (D[i] == INFTY)
		{
			cout << "路不存在" << endl;
		}
		else
		{
			cout << "长度: " << D[i] << " 路径: ";
			Stack<int> s; // 借助栈回溯 P
			int curr = P[i];
			s.push(curr);
			while (curr != src)
			{
				curr = P[curr];
				s.push(curr);
			}
			while (!s.isEmpty())
			{
				cout << vertex[s.pop()] << " —> ";
			}
			cout << vertex[i] << endl;
		}
	}
}

template<typename V, typename E>
void Graph<V, E>::testAll()
{
	cout << "建立了一个有向图，如下所示" << endl;
	show();
	cout << "------------------------------------------" << endl;
	cout << "第1题：单源最短路径的 Dijkstra 算法" << endl;
	cout << "设源点为 v0，其到其他顶点的最短路径长度和最短路径如下" << endl;
	singleSrc(0);
	cout << "------------------------------------------" << endl;
	cout << "第2题：全局最短路径的 Floyd-Warshall 算法" << endl;
	cout << "各顶点间的最短路径长度和最短路径如下" << endl;
	floydWarshall();
	cout << "------------------------------------------" << endl;
	cout << "第3题：单目标最短路径问题，基于 Dijkstra 算法" << endl;
	cout << "设目标为 v6，其到其他顶点的最短路径长度和最短路径如下" << endl;
	singleTarget(6);
	cout << "------------------------------------------" << endl;
	cout << "第4题：单顶点对间最短路径问题，基于 Dijkstra 算法" << endl;
	cout << "以顶点对 v3, v10 为例，最短路径长度和最短路径如下" << endl;
	cout << "v3 —> v10: ";
	singlePair(3, 10);
	cout << "v10 —> v3: ";
	singlePair(10, 3);
	cout << "------------------------------------------" << endl;
	cout << "第6题：实现 Warshall 算法，计算有向图的可达矩阵" << endl;
	cout << "可达矩阵如下" << endl;
	warshall();
	cout << "------------------------------------------" << endl;
	cout << "第7题：利用堆结构（优先级队列）改进和优化 Dijkstra 算法" << endl;
	cout << "设源点为 v0，其到其他顶点的最短路径长度和最短路径如下" << endl;
	singleSrcHeapOpt(0);
	clock_t st1_t = clock();
	for (size_t i = 0; i < TEST_NUM; i++)
	{
		dijkstra(0);
	}
	clock_t ed1_t = clock();

	clock_t st2_t = clock();
	for (size_t i = 0; i < TEST_NUM; i++)
	{
		dijkstraHeapOpt(0);
	}
	clock_t ed2_t = clock();

	cout << "测试组数：" << TEST_NUM << endl;
	cout << "优化前的运行时间：" << (double)(ed1_t - st1_t)/CLOCKS_PER_SEC*1000 << "ms" << endl;
	cout << "优化后的运行时间：" << (double)(ed2_t - st2_t)/CLOCKS_PER_SEC*1000 << "ms" << endl;
//	for (auto it = dis.begin(); it != dis.end(); it++)
//	{
//		for (auto jt = it->begin(); jt != it->end(); jt++)
//		{
//			cout << *jt << ' ';
//		}
//		cout << endl;
//	}
}

#endif //LAB3_GRAPH_H