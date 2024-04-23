#include "preprocessing.h"
#include "huffman_tree.h"
#include "store.h"
#include "encode.h"
#include "decode.h"
#include "evaluate.h"
#include <cstring>

using namespace std;

int main()
{
	/* 预处理阶段 */
	char title[] = "We choose to go to the moon";
	size_t fullBucket[CHAR_NUM];    // CHAR_NUM = CHAR_MAX + 1
	memset(fullBucket, 0, sizeof(fullBucket));
	size_t fileSize = 0;
	char *buffer = NULL;
	fileSize = readAndCount(title, buffer, fullBucket);	// 读入文件并计数
	CFPair bucket[CHAR_NUM];
	memset(bucket, 0, sizeof(bucket));
	int realNum = removeNonExist(fullBucket, bucket);	// 移除不存在的字符
	showFrequency(bucket, realNum);						// 打印字符频率

	/* 编码阶段 */
	HuffmanTree HT(bucket, realNum);
	HT.merge();					// 二叉树合并
	CHPair codes[realNum];
	memset(codes, 0, sizeof(codes));
	getHuffmanCode(HT, codes);	 				// 计算哈夫曼编码
	saveHuffmanCodes(title, codes, realNum);	// 保存哈夫曼编码于文件中
	showHuffmanCodes(codes, realNum);			// 打印哈夫曼编码表
	encode(buffer, fileSize, title, codes, realNum);	// 对文本进行编码，并保存为二进制文件

	/* 译码和评价阶段 */
	decode(title);		// 对二进制文件解码，并保存为文本文件
	evaluate(title);		// 将原始文件与译码后的文件进行比较

	return 0;
}
