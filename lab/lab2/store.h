#ifndef LAB2_STORE_H
#define LAB2_STORE_H

#include <climits>
#include <cstddef>

#define MAX_CODE_LEN 27    // 最大 Huffman 编码码长
#define BUFFER_LEN 512    // 读写二进制编码文件的缓冲区长度
#define TEXT_BUFFER_LEN 65536    // 读入文件的缓冲区长度
#define MAX_TITLE_LEN 128    // 最大标题长度
#define ALL_ONE_SEQ "1111111111111111111111111111"    // 全一字符串，MAX_CODE_LEN+1 位


const int CHAR_NUM = CHAR_MAX + 1;    // ASCII 字符集的字符个数

struct CFPair    // Character-Frequency Pair
{
	char ch;
	size_t freq;
};

struct CHPair    // Character-Huffman Code Pair
{
	char ch;
	char hCode[MAX_CODE_LEN];
	int len;
};

#endif //LAB2_STORE_H
