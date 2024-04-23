#include "preprocessing.h"
#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <cstring>

using namespace std;

size_t readAndCount(const char *TITLE, char *& buffer, size_t fullBucket[])
{
	struct stat results;
	size_t fileSize = 0;
	char source[MAX_TITLE_LEN];
	strcpy(source, TITLE);
	strcat(source, ".txt");
	if (stat(source, &results) == 0)
		fileSize = results.st_size;    // 读取文件大小
	else
		exit(11);    // 读取文件信息失败，错误码11
	buffer = (char *)malloc(sizeof(char)*(fileSize + REDUNDANT_SPACE));
	ifstream text(source, ios::in | ios::binary);
	text.read(buffer, fileSize);

	size_t sum = 0;    // 所有桶内元素数量之和
	bool nonASCII = false;
	for (size_t i = 0; i < fileSize; i++)
	{
		if (!(buffer[i] >= 0 && buffer[i] <= 127))
		{
			cout << i << ' ' << buffer[i] << endl;
			nonASCII = true;
		}
		fullBucket[buffer[i]]++;
		sum++;
	}
	if (nonASCII)    // 检查文件是否仅由ASCII编码
	{
		cout << "有超出ASCII码表示范围的字符" << endl;
		exit(21);
	}
	text.close();
	return fileSize;
}

int removeNonExist(size_t fullBucket[], CFPair bucket[])
{
	int cnt = 0;
	for (int i = 0; i < CHAR_NUM; i++)
	{
		if (fullBucket[i] > 0)
		{
			bucket[cnt].ch = i;
			bucket[cnt].freq = fullBucket[i];
			cnt++;
		}
	}
	return cnt;
}

void showFrequency(CFPair bucket[], int realNum)
{
	cout << "文本中各字符的使用频率" << endl;
	size_t sum = 0;
	for (int i=0; i<realNum; i++)
	{
		sum += bucket[i].freq;
	}
	for (int i = 0; i < realNum; i++)
	{
		if (bucket[i].ch == '\n')
			printf("'\\n': ");
		else if (bucket[i].ch == '\r')
			printf("'\\r': ");
		else
			printf("'%c' : ", bucket[i].ch);
		cout << 1.0*bucket[i].freq/sum << endl;
	}
}