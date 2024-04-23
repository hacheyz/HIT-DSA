#ifndef LAB2_EVALUATE_H
#define LAB2_EVALUATE_H

#include "store.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <sys/stat.h>

void evaluate(const char *TITLE);
void compare(const char *TITLE); 		// 比较原文件和译码后的文件是否完全相同
void calcCompress(const char *TITLE);    // 计算压缩率

#endif //LAB2_EVALUATE_H
