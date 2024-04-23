#ifndef LAB2_DECODE_H
#define LAB2_DECODE_H

#include "bitset"
#include "store.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>

void decode(const char *TITLE);
char findChar(const char *code, CHPair *codes, int num);

#endif //LAB2_DECODE_H
