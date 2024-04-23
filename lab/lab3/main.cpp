#include "graph.h"
#include <iostream>
#include <cstdio>

int main()
{
	/* 图存于 http://graphonline.ru/ch/?graph=nkKxPVqMqNypXYoI */
	freopen("in.txt", "r", stdin); // 输入重定向
	Graph<string, int> G;
	G.create(); // 构建图
	G.testAll(); // 测试每道题的算法

	return 0;
}
