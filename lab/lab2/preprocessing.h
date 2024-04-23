#ifndef LAB2_PREPROCESSING_H
#define LAB2_PREPROCESSING_H

#include "store.h"
#include <iostream>

#define REDUNDANT_SPACE 100

/* 读入名为 TITLE.txt 的文件，将文本保存于 buffer 中，将每个字符出现的次数存入 fullBucket 中
 * 返回文件的字符个数 */
size_t readAndCount(const char *TITLE, char *& buffer, size_t fullBucket[]);

/* 移除 fullBucket 中值为 0 的元素，将所有非 0 元素存入 bucket 中
 * 返回非 0 元素个数 */
int removeNonExist(size_t fullBucket[], CFPair bucket[]);

/* 打印所有至少出现一次的字符及其频率 */
void showFrequency(CFPair bucket[], int realNum);

#endif //LAB2_PREPROCESSING_H
