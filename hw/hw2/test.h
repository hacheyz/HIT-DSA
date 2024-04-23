#ifndef HW2_TEST_H
#define HW2_TEST_H

#include "binary_tree.h"

template<typename T>
void testTree(BinTree<T> t);	// 打印二叉树t的测试信息

template<typename T>
void printSeq(vector<T> v);		// 打印一个序列

template<typename T>
void testTree(BinTree<T> t)
{
	printf("%-18s", "show:");
	t.show();
	printf("%-18s", "preOrder:");
	t.preOrder();
	printf("%-18s", "preOrderNonRec:");
	t.preOrderNonRec();
	printf("%-18s", "preOrderSeq:");
	printSeq(t.preOrderSeq);
	printf("%-18s", "inOrder:");
	t.inOrder();
	printf("%-18s", "inOrderNonRec:");
	t.inOrderNonRec();
	printf("%-18s", "inOrderSeq:");
	printSeq(t.inOrderSeq);
	printf("%-18s", "postOrder:");
	t.postOrder();
	printf("%-18s", "postOrderNonRec:");
	t.postOrderNonRec();
	printf("%-18s", "postOrderSeq:");
	printSeq(t.postOrderSeq);
	printf("%-18s", "levelOrder:");
	t.levelOrder();
	printf("%-18s", "levelOrderSeq:");
	printSeq(t.levelOrderSeq);
	printf("%-18s", "isComplete:");
	cout << t.isComplete() << endl;
	printf("%-18s", "width:");
	cout << t.width() << endl << endl;
	printf("%-18s", "newWidth:");
	cout << t.newWidth() << endl << endl;
}

template<typename T>
void printSeq(vector<T> v)
{
	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << *it << ' ';
	}
	cout << endl;
}

#endif //HW2_TEST_H
