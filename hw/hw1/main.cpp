/* 此文件用于测试 */

#include "seq_list.h"
#include "link_list.h"
#include "static_link_list.h"
#include <iostream>

using namespace std;

int main()
{
	int arr[] = {0, 1, 2, 3, 5, 5, 8, 6};
	int arr0[] = {2, 3, 4};

	/* 顺序存储测试 */
	cout << "SeqList: " << endl;
	SeqList<int> seqL;
	for (int i=0; i<sizeof(arr)/sizeof(int); ++i)
	{
		seqL.append(arr[i]);	// 注释这条语句以测试空表
	}
	seqL.travel();	//	0	1	2	3	5	5	8	6
	cout << seqL.length() << endl;  // 8
	cout << seqL.isEmpty() << '\t' << seqL.isFull() << endl;  // 0   0
	seqL.insert(4, 4);
	seqL.travel();	//  0	1	2	3	4	5	5	8	6
	seqL.remove(7);
	seqL.travel();	//  0	1	2	3	4	5	5	6
	seqL.removeGiven(6).travel();	//	0	1	2	3	4	5	5
	seqL.removeDuplicate().travel();// 	0	1	2	3	4	5
	seqL.reverse().travel();	//  5	4	3	2	1	0
	seqL.reverse();				//	复位
	seqL.leftShift(2).travel(); //  2	3	4	5	0	1
	seqL.rightShift(2).travel();//  0	1	2	3	4	5
	SeqList<int> seqL0;
	for (int i=0; i<sizeof(arr0)/sizeof(int); ++i)
	{
		seqL0.append(arr0[i]);	// 注释这条语句以测试空表试空表
	}
	seqL.merge(seqL0).travel();	//	0	1	2	2	3	3	4	4	5
	cout << endl;

	/* 链式存储测试 */
	cout << "LinkList: " << endl;
	LinkList<int> linkL;
	for (int i=0; i<sizeof(arr)/sizeof(int); ++i)
	{
		linkL.append(arr[i]);
	}
	linkL.travel();	//	0	1	2	3	5	5	8	6
	cout << linkL.length() << endl;  // 8
	cout << linkL.isEmpty() << '\t' << linkL.isFull() << endl;  // 0   0
	linkL.insert(4, linkL.head->next->next->next->next->next);
	linkL.travel();	//  0	1	2	3	4	5	5	8	6
	linkL.remove(linkL.prev(linkL.back()));
	linkL.travel();	//  0	1	2	3	4	5	5	6
	linkL.removeGiven(6);
	linkL.travel();	//	0	1	2	3	4	5	5
	linkL.removeDuplicate().travel();	//  0	1	2	3	4	5
	linkL.reverse().travel();			//	5	4	3	2	1	0
	linkL.reverse();	// 复位
	linkL.leftShift(2).travel();	//	2	3	4	5	0	1
	linkL.rightShift(2).travel();	//  0	1	2	3	4	5
	LinkList<int> linkL0;
	for (int i=0; i<sizeof(arr0)/sizeof(int); ++i)
	{
		linkL0.append(arr0[i]);
	}
	linkL.merge(linkL0).travel();	//	0	1	2	2	3	3	4	4	5
	cout << endl;

	/* 静态链表测试 */
	cout << "StaticList: " << endl;
	StaticList<int> staticL;
	for (int i=0; i<sizeof(arr)/sizeof(int); ++i)
	{
		staticL.append(arr[i]);
	}
	staticL.travel();	//	0	1	2	3	5	5	8	6
	cout << staticL.length() << endl;  // 8
	cout << staticL.isEmpty() << '\t' << staticL.isFull() << endl;  // 0   0
	staticL.insert(4, staticL.next(staticL.next(staticL.next(staticL.next(staticL.next(staticL.head))))));
	staticL.travel();	//  0	1	2	3	4	5	5	8	6
	staticL.remove(staticL.prev(staticL.back()));
	staticL.travel();			//  0	1	2	3	4	5	5	6
	staticL.reverse().travel();	//  6	5	5	4	3	2	1	0

	return 0;
}
