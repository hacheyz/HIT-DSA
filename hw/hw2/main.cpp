#include "binary_tree.h"
#include "test.h"
#include <vector>

using namespace std;

int main()
{
	cout << "# TREE TYPE: char normal" << endl;
	BinTree<char> tChar;	// 一般二叉树，数据域类型为char
	vector<char> vChar = { 'A', 'B', 'C', '$', 'E', '$', 'G', '$', '$', 'J'};
	tChar.create(vChar);
	testTree(tChar);

	cout << "# TREE TYPE: char large" << endl;
	BinTree<char> tLarge;	// 较大的二叉树，数据域类型为char
	vector<char> vLarge = {
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', '$', 'I', '$',
			'J', 'K', 'L', 'M', '$', '$', '$', '$', 'N', 'O', '$',
			'$', '$', '$', 'P', 'Q', '$', '$', '$', '$', '$', '$',
			'$', '$', '$', '$', '$', '$', '$', 'R'
	};
 	tLarge.create(vLarge);
	testTree(tLarge);

	cout << "# TREE TYPE: int complete" << endl;
	BinTree<int> tInt;	// 完全二叉树（满二叉树），数据域类型为int
	vector<int> vInt = { 1, 2, 3, 4, 5, 6, 7};
	tInt.create(vInt);
	testTree(tInt);

	cout << "# TREE TYPE: int empty" << endl;
	BinTree<int> tEmpty;	// 空树，数据域类型为int
	vector<int> vEmpty;
	tEmpty.create(vEmpty);
	testTree(tEmpty);

	return 0;
}
