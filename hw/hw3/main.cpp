#include "graph_matrix.cpp"
#include "graph_list.cpp"
#include "test.h"
#include <iostream>
#include <cstdio>

int main()
{
	/* 重定向输入自 "in.txt" */
	freopen("in.txt", "r", stdin);

	/* 图 M 存于 https://graphonline.ru/ch/?graph=HrTSeDQOGCPUilYh */
	Matrix::Graph<string, int, false> M;
	M.create();
	testMatrixGraph(M);

	/* 图 L 存于 http://graphonline.ru/ch/?graph=xvYnonKnPSlnGVoo */
	List::Graph<string, int, true> L;
	L.create();
	testListGraph(L);

	return 0;
}
