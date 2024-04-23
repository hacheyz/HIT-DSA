#ifndef HW4_BINARY_SEARCH_H
#define HW4_BINARY_SEARCH_H

#include "record.h"
#include <vector>
#include <cstddef>
#include <iostream>

#define NOT_FOUND -1

using namespace std;

static size_t count; // 查找计数器

template<typename Keytype>
int binarySearch(vector<Record<Keytype> > v, Keytype k)
{
	count = 0;
	int low, high, mid;
	low = 0;
	high = v.size() - 1;
	while (low <= high)
	{
		count++;
		mid = (low + high)/2;
		if (k < v[mid].key)
			high = mid - 1;
		else if (k > v[mid].key)
			low = mid + 1;
		else
			return mid;
	}
	return NOT_FOUND;
}

template<typename Keytype>
void countSearch(vector<Record<Keytype> > v, double& succAsl, double& failAsl)
{
	/* 奇数查找成功 */
	size_t succSum = 0;
	for (int i = 1; i < 2048; i += 2)
	{
		binarySearch(v, i);
		succSum += count;
	}
	succAsl = (double)succSum/RECORD_LENGTH;
	/* 偶数查找失败 */
	size_t failSum = 0;
	for (int i = 0; i < 2048; i += 2)
	{
		binarySearch(v, i);
		failSum += count;
		cout << i << ": " << count << endl;
	}
	failAsl = (double)failSum/RECORD_LENGTH;
}

#endif //HW4_BINARY_SEARCH_H
