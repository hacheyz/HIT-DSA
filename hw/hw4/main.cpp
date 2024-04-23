#include "record.h"
#include "binary_search_tree.h"
#include "binary_search.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
//#include <time.h>

using namespace std;

template<typename T>
void printVec(vector<Record<T>> vec)
{
	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		cout << it->key << ' ';
	}
	cout << endl;
}

int main()
{
	/**产生两个序列*/
	vector<Record<int>> v; // 0 到 2048 所有的奇数
	for (int i = 1; i < 2048; i += 2)
	{
		v.push_back(Record<int>(i));
	}
//	srand((unsigned)time(0)); // 根据时间戳设置种子
	srand(1); // 为保证可重复性, 设置固定种子
	vector<Record<int>> vr(v); // v 的乱序版本, r for random
	random_shuffle(vr.begin(), vr.end());
	/**产生两个树*/
	BST<int> T;
	T.create(v);
	BST<int> Tr;
	Tr.create(vr);
	/**计算两棵 BST 的查找成功和查找失败的平均查找长度*/
	double BSTSuccAsl, BSTFailAsl;
	double BSTSuccAslr, BSTFailAslr;
	T.countSearch(BSTSuccAsl, BSTFailAsl);
	Tr.countSearch(BSTSuccAslr, BSTFailAslr);
	cout << "使用 BST 查找: " << endl;
	cout << "顺序奇数序列的查找成功和查找失败的平均查找长度: " << endl;
	cout << BSTSuccAsl << ' ' << BSTFailAsl << endl;
	cout << "乱序奇数序列的查找成功和查找失败的平均查找长度: " << endl;
	cout << BSTSuccAslr << ' ' << BSTFailAslr << endl;
	/**创建中序序列*/
	vector<Record<int>> ino(T.sort());
	vector<Record<int>> inor(Tr.sort());
	/**计算折半查找的查找成功和查找失败的平均查找长度*/
	double binSearchSuccAvl, binSearchFailAvl;
	double binSearchSuccAvlr, binSearchFailAvlr;
	countSearch(ino, binSearchSuccAvl, binSearchFailAvl);
	countSearch(inor, binSearchSuccAvlr, binSearchFailAvlr);
	cout << "--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--" << endl;
	cout << "使用折半查找: " << endl;
	cout << "顺序奇数序列构建的 BST 树的中序序列的查找成功和查找失败的平均查找长度: " << endl;
	cout << binSearchSuccAvl << ' ' << binSearchFailAvl << endl;
	cout << "乱序奇数序列构建的 BST 树的中序序列的查找成功和查找失败的平均查找长度: " << endl;
	cout << binSearchSuccAvlr << ' ' << binSearchFailAvlr << endl;


	return 0;
}
