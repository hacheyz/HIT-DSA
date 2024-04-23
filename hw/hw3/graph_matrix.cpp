#include "support/stack.h"
#include "support/queue.h"
#include "graph.h"

template<typename V, typename E, bool directed>
size_t Matrix::Graph<V, E, directed>::nodeNum()
{
	return vertex.size();
}

template<typename V, typename E, bool directed>
size_t Matrix::Graph<V, E, directed>::edgeNum()
{
	size_t cnt = 0;
	for (auto it = mat.begin(); it != mat.end(); it++)
	{
		for (auto jt = it->begin(); jt != it->end(); jt++)
		{
			if (*jt != 0)
			{
				cnt++;
			}
		}
	}
	return directed ? cnt : (cnt/2);
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::show()
{
	for (auto it = mat.begin(); it != mat.end(); it++)
	{
		for (auto jt = it->begin(); jt != it->end(); jt++)
		{
			cout << *jt << ' ';
		}
		cout << endl;
	}
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::addNode(V v)
{
	size_t size = vertex.size();
	vertex.push_back(v);
	mat.resize(size + 1);
	for (auto it = mat.begin(); it != mat.end(); it++)
	{
		it->resize(size + 1);
	}
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::addNodesFrom(V *v, size_t vNum)
{
	size_t size = vertex.size();
	for (size_t i = 0; i < vNum; i++)
	{
		vertex.push_back(v[i]);
	}
	mat.resize(size + vNum);
	for (auto it = mat.begin(); it != mat.end(); it++)
	{
		it->resize(size + vNum);
	}
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::delNode(V v)
{
	auto toDel = findVertex(v);
	vertex.erase(toDel);
	size_t offset = toDel - vertex.begin();
	mat.erase(mat.begin() + offset);
	for (auto it = mat.begin(); it != mat.end(); it++)
	{
		it->erase(it->begin() + offset);
	}
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::addEdge(V v1, V v2, E e)
{
	auto it1 = findVertex(v1);
	auto it2 = findVertex(v2);
	size_t offset1 = it1 - vertex.begin();
	size_t offset2 = it2 - vertex.begin();
	mat[offset1][offset2] = e;
	if (!directed)
		mat[offset2][offset1] = e;
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::delEdge(V v1, V v2)
{
	auto it1 = findVertex(v1);
	auto it2 = findVertex(v2);
	size_t offset1 = it1 - vertex.begin();
	size_t offset2 = it2 - vertex.begin();
	if (mat[offset1][offset2] == 0)
		throw invalid_argument("Graph::delEdge: edge (v1, v2) does not exist");
	mat[offset1][offset2] = 0;
	if (!directed)
		mat[offset2][offset1] = 0;
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::getSucc(V v)
{
	auto cur = findVertex(v);
	auto curLine = mat[cur - vertex.begin()];
	cout << "Successors of " << v << ": ";
	for (auto it = curLine.begin(); it != curLine.end(); it++)
	{
		if (*it != 0)
			cout << vertex[it - curLine.begin()] << ' ';
	}
	cout << endl;
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::getPred(V v)
{
	auto cur = findVertex(v);
	size_t offset = cur - vertex.begin();
	cout << "Precursors of " << v << ": ";
	for (auto it = mat.begin(); it != mat.end(); it++)
	{
		if ((*it)[offset] != 0)
			cout << vertex[it - mat.begin()] << ' ';
	}
	cout << endl;
}

template<typename V, typename E, bool directed>
bool Matrix::Graph<V, E, directed>::isEdge(V v1, V v2)
{
	auto it1 = findVertex(v1);
	auto it2 = findVertex(v2);
	size_t offset1 = it1 - vertex.begin();
	size_t offset2 = it2 - vertex.begin();
	return mat[offset1][offset2] != 0;
}

template<typename V, typename E, bool directed>
typename vector<V>::iterator Matrix::Graph<V, E, directed>::findVertex(V v)
{
	auto it = vertex.begin();
	while (it != vertex.end())
	{
		if (*it == v)
			return it;
		it++;
	}
	if (it == vertex.end())
		throw invalid_argument("Vertex does not exist");
	return it;
}

template<typename V, typename E, bool directed>
List::Graph<V, E, directed> Matrix::Graph<V, E, directed>::toList()
{
	List::Graph<V, E, directed> L;
	Matrix::Graph<V, E, directed>& M = *this;
	for (auto it = M.vertex.begin(); it != M.vertex.end(); it++)
	{
		L.addNode(*it);
	}
	for (auto it = M.mat.begin(); it != M.mat.end(); it++)
	{
		for (auto jt = it->begin(); jt != it->end(); jt++)
		{
			if (*jt != 0)
			{
				size_t offset1 = it - M.mat.begin();
				size_t offset2 = jt - it->begin();
				if (!L.isEdge(M.vertex[offset1], M.vertex[offset2]))
					L.addEdge(M.vertex[offset1], M.vertex[offset2], *jt);
			}
		}
	}
	return L;
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::initDFS()
{
	DFSNum.clear();
	DFSNum.resize(nodeNum());
	DFSSeq.clear();
	DFSTree.destroy();
	DFSTree.importNodesFrom(vertex);
	visited.clear();
	visited.resize(nodeNum());
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::DFS()
{
	initDFS();
	size_t vNum = nodeNum();
	size_t cnt = 1;
	cout << "DFS: ";
	for (size_t i = 0; i < vNum; i++)
	{
		if (!visited[i])
			DFSi(i, cnt); // 从顶点出发的一次深度优先搜索
	}
	cout << endl;
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::DFSi(size_t i, size_t& cnt)
{
	cout << vertex[i] << ' ';
	visited[i] = true;
	DFSNum[i] = cnt++;
	DFSSeq.push_back(vertex[i]);
	size_t vNum = nodeNum();
	for (size_t j = 0; j < vNum; j++)
	{
		if (mat[i][j] != 0 && !visited[j])
		{
			DFSTree.addSon(i, j);
			DFSi(j, cnt);
		}
	}
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::DFSNonRec()
{
	initDFS();
	using Pair = pair<size_t, size_t>;
	Stack<Pair> s; // 保存当前程序运行状态：当前顶点的下标，循环变量的值
	size_t vNum = nodeNum();
	size_t cnt = 1;
	cout << "DFS: ";
	size_t p;
	for (size_t i = 0; i < vNum; i++) // 访问每个顶点
	{
		if (!visited[i])
		{
			cout << vertex[i] << ' ';
			visited[i] = true;
			DFSNum[i] = cnt++;
			DFSSeq.push_back(vertex[i]);
			p = i;
			for (size_t j = 0; j < vNum; j++) // 对每个顶点，访问与其邻接的顶点
			{
				if (mat[p][j] != 0 && !visited[j]) // 如果存在邻接顶点未访问
				{
					cout << vertex[j] << ' ';
					visited[j] = true;
					DFSNum[j] = cnt++;
					DFSSeq.push_back(vertex[j]);
					DFSTree.addSon(p, j);
					if (j != vNum - 1) // 只有非已遍历到末尾的顶点才有继续遍历的价值
					{
						s.push(Pair(p, j));
						p = j; // 直接将 p 置为该点
						j = -1; // 初始化循环变量
					}
				}
				if (j == vNum - 1) // 遍历邻接顶点结束
				{
					if (!s.isEmpty()) // 栈不空，说明这棵树还有顶点待访问邻接顶点
					{
						Pair temp = s.pop();
						p = temp.first; // 将该点取出
						j = temp.second; // 继续循环
					}
					/* 否则，已经结束内层循环，访问下一棵树 */
				}
			}
		}
	}
	cout << endl;
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::initBFS()
{
	BFSNum.clear();
	BFSNum.resize(nodeNum());
	BFSSeq.clear();
	BFSTree.destroy();
	BFSTree.importNodesFrom(vertex);
	visited.clear();
	visited.resize(nodeNum());
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::BFS()
{
	initBFS();
	size_t vNum = nodeNum();
	size_t cnt = 1;
	cout << "BFS: ";
	for (size_t i = 0; i < vNum; i++)
	{
		if (!visited[i])
			BFSi(i, cnt); // 从顶点 i 开始的一次先广遍历
	}
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::BFSi(size_t i, size_t& cnt)
{
	cout << vertex[i] << ' ';
	visited[i] = true;
	BFSNum[i] = cnt++;
	BFSSeq.push_back(vertex[i]);
	size_t vNum = nodeNum();
	Queue<size_t> q;
	q.push(i);
	size_t p;
	while (!q.isEmpty())
	{
		p = q.pop();
		for (size_t j = 0; j < vNum; j++)
		{
			if (mat[p][j] != 0 && !visited[j])
			{
				cout << vertex[j] << ' ';
				visited[j] = true;
				BFSNum[j] = cnt++;
				BFSSeq.push_back(vertex[j]);
				BFSTree.addSon(p, j);
				q.push(j);
			}
		}
	}
	cout << endl;
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::calcDeg()
{
	size_t vNum = nodeNum();
	if (!directed) // 无向图只需计算度
	{
		for (size_t i = 0; i < vNum; i++)
		{
			size_t degSum = 0;
			cout << vertex[i] << ": ";
			for (size_t j = i + 1; j < vNum; j++)
			{
				if (mat[i][j] != 0)
					degSum++;
			}
			cout << degSum << endl;
		}
	}
	else // 有向图需要计算入度、出度、度，按顺序打印
	{
		for (size_t i = 0; i < vNum; i++)
		{
			size_t inSum = 0;
			size_t outSum = 0;
			size_t degSum;
			cout << vertex[i] << ": ";
			for (size_t j = 0; j < vNum; j++)
			{
				if (mat[j][i] != 0)
					inSum++;
				if (mat[i][j] != 0)
					outSum++;
			}
			degSum = inSum + outSum;
			cout << inSum << ' ' << outSum << ' ' << degSum << endl;
		}
	}
}

template<typename V, typename E, bool directed>
void Matrix::Graph<V, E, directed>::create()
{
	size_t vNum, eNum;
	cin >> vNum >> eNum;
	vertex.resize(vNum);
	mat.resize(vNum, vector<E>(vNum));
	for (size_t i = 0; i < vNum; i++)
	{
		cin >> vertex[i];
	}
	for (size_t i = 0; i < vNum; i++)
	{
		for (size_t j = 0; j < vNum; j++)
		{
			mat[i][j] = 0;
		}
	}
	size_t st, ed;
	E e;
	for (size_t i = 0; i < eNum; i++)
	{
		cin >> st >> ed >> e;
		mat[st][ed] = e;
		if (!directed)
			mat[ed][st] = e;
	}
}
