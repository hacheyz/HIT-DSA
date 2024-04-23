#ifndef LAB2_ENCODE_H
#define LAB2_ENCODE_H

#include "store.h"
#include "huffman_tree.h"
#include "stack.h"
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <bitset>

void getHuffmanCode(HuffmanTree HT, CHPair *codes);    // 根据 Huffman 树得到每个字符的编码
void showHuffmanCodes(CHPair *codes, int num);        // 打印字符集的哈夫曼编码表
void saveHuffmanCodes(const char *TITLE, CHPair *codes, int num);        // 将字符集的哈夫曼编码表保存为文件
void encode(char *text, size_t textLen, const char *TITLE, CHPair *codes, int codeNum);

#endif //LAB2_ENCODE_H
