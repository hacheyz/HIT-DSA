#include "graph.h"
#include "support/stack.h"
#include "support/queue.h"

template<typename V, typename E, bool directed>
size_t List::Graph<V, E, directed>::nodeNum()
{
	return vertex.size();
}

template<typename V, typename E, bool directed>
size_t List::Graph<V, E, directed>::edgeNum()
{
	size_t cnt = 0;
	for (auto it = vertex.begin(); it != vertex.end(); it++)
	{
		for (Edge *j = it->firstEdge; j != NULL; j = j->next)
		{
			cnt++;
		}
	}
	return directed ? cnt : cnt/2;
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::show()
{
	for (auto it = vertex.begin(); it != vertex.end(); it++)
	{
		cout << it->v << ": ";
		for (Edge *j = it->firstEdge; j != NULL; j = j->next)
		{
			cout << '(' << vertex[j->v].v << ", " << j->e << ") ";
		}
		cout << endl;
	}
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::addNode(V v)
{
	vertex.push_back(Vert(v));
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::addNodesFrom(V *v, size_t vNum)
{
	for (size_t i = 0; i < vNum; i++)
	{
		vertex.push_back(Vert(v[i]));
	}
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::delNode(V v)
{
	auto toDel = findVertex(v);
	vertex.erase(toDel);
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::addEdge(V v1, V v2, E e)
{
	auto it1 = findVertex(v1);
	auto it2 = findVertex(v2);

	size_t offset2 = it2 - vertex.begin();
	Edge *toAdd1 = new Edge(offset2, e);
	toAdd1->next = it1->firstEdge;
	it1->firstEdge = toAdd1;
	if (!directed)
	{
		size_t offset1 = it1 - vertex.begin();
		Edge *toAdd2 = new Edge(offset1, e);
		toAdd2->next = it2->firstEdge;
		it2->firstEdge = toAdd2;
	}
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::delEdge(V v1, V v2)
{
	auto it = findVertex(v1);
	Edge *p = it->firstEdge, *q;
	while (p != NULL)
	{
		if (vertex[p->v].v == v2)
		{
			break;
		}
		q = p;
		p = p->next;
	}
	if (p == NULL)
		throw invalid_argument("EdgeNode does not exist");
	Edge *toDel;
	if (p == it->firstEdge)
	{
		toDel = it->firstEdge;
		it->firstEdge = it->firstEdge->next;
		delete toDel;
	}
	else
	{
		toDel = p;
		p = p->next;
		q->next = p;
		delete toDel;
	}
	if (!directed)
	{
		auto it2 = findVertex(v2);
		Edge *p2 = it->firstEdge, *q2;
		while (p2 != NULL)
		{
			if (vertex[p2->v].v == v2)
			{
				break;
			}
			q2 = p2;
			p2 = p2->next;
		}
		if (p2 == NULL)
			throw invalid_argument("EdgeNode does not exist");
		Edge *toDel2;
		if (p2 == it2->firstEdge)
		{
			toDel2 = it2->firstEdge;
			it2->firstEdge = it2->firstEdge->next;
			delete toDel2;
		}
		else
		{
			toDel2 = p2;
			p2 = p2->next;
			q2->next = p2;
			delete toDel2;
		}
	}
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::getSucc(V v)
{
	auto it = findVertex(v);
	cout << "Successors of " << v << ": ";
	for (Edge *e = it->firstEdge; e != NULL; e = e->next)
	{
		cout << vertex[e->v].v << ' ';
	}
	cout << endl;
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::getPred(V v)
{
	cout << "Precursors of " << v << ": ";
	for (auto it = vertex.begin(); it != vertex.end(); it++)
	{
		for (Edge *e = it->firstEdge; e != NULL; e = e->next)
		{
			if (vertex[e->v].v == v)
			{
				cout << it->v << ' ';
				break;
			}
		}
	}
	cout << endl;
}

template<typename V, typename E, bool directed>
bool List::Graph<V, E, directed>::isEdge(V v1, V v2)
{
	auto it = findVertex(v1);
	for (auto e = it->firstEdge; e != NULL; e = e->next)
	{
		if (vertex[e->v].v == v2)
			return true;
	}
	return false;
}

template<typename V, typename E, bool directed>
typename vector<List::Vertex<V, E, directed>>::iterator List::Graph<V, E, directed>::findVertex(V v)
{
	auto it = vertex.begin();
	while (it != vertex.end())
	{
		if (it->v == v)
			return it;
		it++;
	}
	if (it == vertex.end())
		throw invalid_argument("Vertex does not exist");
	return it;
}

template<typename V, typename E, bool directed>
Matrix::Graph<V, E, directed> List::Graph<V, E, directed>::toMatrix()
{
	Matrix::Graph<V, E, directed> M;
	List::Graph<V, E, directed>& L = *this;
	for (auto it = L.vertex.begin(); it != L.vertex.end(); it++)
	{
		M.addNode(it->v);
	}
	for (auto it = L.vertex.begin(); it != L.vertex.end(); it++)
	{
		V v1 = it->v;
		for (auto j = it->firstEdge; j != NULL; j = j->next)
		{
			M.addEdge(v1, vertex[j->v].v, j->e);
		}
	}
	return M;
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::initDFS()
{
	DFSNum.clear();
	DFSNum.resize(nodeNum());
	DFSSeq.clear();
	DFSTree.destroy();
	vector<V> vs;
	for (auto it = vertex.begin(); it != vertex.end(); it++)
	{
		vs.push_back(it->v);
	}
	DFSTree.importNodesFrom(vs);
	visited.clear();
	visited.resize(nodeNum());
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::DFS()
{
	initDFS();
	size_t vNum = nodeNum();
	size_t cnt = 1;
	cout << "DFS: ";
	for (size_t i = 0; i < vNum; i++)
	{
		if (!visited[i])
			DFSi(i, cnt);
	}
	cout << endl;
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::DFSi(size_t i, size_t& cnt)
{
	cout << vertex[i].v << ' ';
	visited[i] = true;
	DFSNum[i] = cnt++;
	DFSSeq.push_back(vertex[i].v);
	for (auto j = vertex[i].firstEdge; j != NULL; j = j->next)
	{
		if (!visited[j->v])
		{
			DFSTree.addSon(i, j->v);
			DFSi(j->v, cnt);
		}
	}
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::DFSNonRec()
{
	initDFS();
	using Pair = pair<size_t, Edge *>;
	Stack<Pair> s;
	size_t vNum = nodeNum();
	size_t cnt = 1;
	cout << "DFS: ";
	size_t p;
	for (size_t i = 0; i < vNum; i++)
	{
		if (!visited[i])
		{
			cout << vertex[i].v << ' ';
			visited[i] = true;
			DFSNum[i] = cnt++;
			DFSSeq.push_back(vertex[i].v);
			p = i;
		}
		Edge *next = NULL;
		for (auto jp = vertex[p].firstEdge; jp != NULL; jp = jp->next)
		{
			if (next)
			{
				jp = next;
				next = NULL;
			}
			size_t j = jp->v;
			if (!visited[j])
			{
				cout << vertex[j].v << ' ';
				visited[j] = true;
				DFSNum[j] = cnt++;
				DFSSeq.push_back(vertex[j].v);
				DFSTree.addSon(p, j);
				if (vertex[j].firstEdge != NULL) // 只有有出边的点才加入到栈中
				{
					s.push(Pair(p, jp));
					p = j;
					next = vertex[p].firstEdge - 1;
				}
			}
			if (jp->next == NULL)
			{
				if (!s.isEmpty())
				{
					Pair temp = s.pop();
					p = temp.first;
					jp = temp.second;
				}
			}
		}
	}
	cout << endl;
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::initBFS()
{
	BFSNum.clear();
	BFSNum.resize(nodeNum());
	BFSSeq.clear();
	BFSTree.destroy();
	vector<V> vs;
	for (auto it = vertex.begin(); it != vertex.end(); it++)
	{
		vs.push_back(it->v);
	}
	BFSTree.importNodesFrom(vs);
	visited.clear();
	visited.resize(nodeNum());
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::BFS()
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
	cout << endl;
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::BFSi(size_t i, size_t& cnt)
{
	cout << vertex[i].v << ' ';
	visited[i] = true;
	BFSNum[i] = cnt++;
	BFSSeq.push_back(vertex[i].v);
	Queue<size_t> q;
	q.push(i);
	size_t p;
	while (!q.isEmpty())
	{
		p = q.pop();
		for (auto jp = vertex[p].firstEdge; jp != NULL; jp = jp->next)
		{
			size_t j = jp->v;
			if (!visited[j])
			{
				cout << vertex[j].v << ' ';
				visited[j] = true;
				BFSNum[j] = cnt++;
				BFSSeq.push_back(vertex[j].v);
				BFSTree.addSon(p, j);
				q.push(j);
			}
		}
	}
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::calcDeg()
{
	size_t vNum = nodeNum();
	if (!directed)    // 无向图只需计算度
	{
		for (size_t i = 0; i < vNum; i++)
		{
			size_t degSum = 0;
			cout << vertex[i].v << ": ";
			for (Edge *jp = vertex[i].firstEdge; jp != NULL; jp = jp->next)
			{
				degSum++;
			}
			cout << degSum << endl;
		}
	}
	else // 有向图需要计算入度、出度、度，按顺序打印
	{
		vector<size_t> inSum(vNum, 0); // 存放各结点的入度，以空间换时间
		for (size_t i = 0; i < vNum; i++)
		{
			for (Edge *jp = vertex[i].firstEdge; jp != NULL; jp = jp->next)
			{
				inSum[jp->v]++;
			}
		}
		for (size_t i = 0; i < vNum; i++)
		{
			size_t outSum = 0;
			size_t degSum;
			cout << vertex[i].v << ": ";
			for (Edge *jp = vertex[i].firstEdge; jp != NULL; jp = jp->next)
			{
				outSum++;
			}
			degSum = inSum[i] + outSum;
			cout << inSum[i] << ' ' << outSum << ' ' << degSum << endl;
		}
	}
}

template<typename V, typename E, bool directed>
void List::Graph<V, E, directed>::create()
{
	size_t vNum, eNum;
	cin >> vNum >> eNum;
	V v;
	for (size_t i = 0; i < vNum; i++)
	{
		cin >> v;
		vertex.push_back(Vert(v));
	}
	size_t st, ed, e;
	for (size_t i = 0; i < eNum; i++)
	{
		cin >> st >> ed >> e;
		Edge *p = new Edge(ed, e);
		p->next = vertex[st].firstEdge;
		vertex[st].firstEdge = p;
		if (!directed)
		{
			p = new Edge(st, e);
			p->next = vertex[ed].firstEdge;
			vertex[ed].firstEdge = p;
		}
	}
}