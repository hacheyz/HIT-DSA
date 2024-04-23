#include "decode.h"

using namespace std;

void decode(const char *TITLE)
{
	/* 读入编码表 */
	char codeFile[MAX_TITLE_LEN];
	strcpy(codeFile, TITLE);
	strcat(codeFile, ".cd");
	ifstream cd(codeFile, ios::in | ios::binary);
	CHPair codes[CHAR_NUM];
	int cnt = 0;
	memset(codes, 0, sizeof(codes));
	while (cd.peek() != EOF)
	{
		cd.read((char *)&codes[cnt], sizeof(CHPair));
		cnt++;
	}
	cd.close();

	/* 读入压缩文件 */
	char binaryFile[MAX_TITLE_LEN];
	strcpy(binaryFile, TITLE);
	strcat(binaryFile, ".bin");
	struct stat results;
	size_t fileSize = 0;
	if (stat(binaryFile, &results) == 0)
		fileSize = results.st_size;    // 读取文件大小
	else
		exit(11);    // 读取文件信息失败，错误码11

	char restoreFile[MAX_TITLE_LEN];
	strcpy(restoreFile, TITLE);
	strcat(restoreFile, "(restore).txt");	// 译码后的文件
	ofstream restore(restoreFile, ios::out | ios::binary);

	char buffer[fileSize];
	char text[TEXT_BUFFER_LEN];
	memset(text, 0, sizeof(text));
	int textCur = 0;
	char code[MAX_CODE_LEN];
	memset(code, 0, sizeof(code));
	int codeCur = 0;
	bool beforeEnd = false;
	ifstream bin(binaryFile, ios::in | ios::binary);
	bitset<BUFFER_LEN> bitBuffer;
	while (bin.peek() != EOF)
	{
		bin.read((char *)&bitBuffer, sizeof(bitBuffer));
		int bBufCur = 0;
		while (bBufCur < MAX_CODE_LEN)
		{
			if (bitBuffer[bBufCur++] == 0)
				break;
			if (bBufCur == MAX_CODE_LEN)
				beforeEnd = true;
		}
		if (beforeEnd)
			break;
		bBufCur = BUFFER_LEN - 1;	// bitBuffer Cursor，从字节的右侧开始读起
		while (bBufCur != -1)
		{
			if (bitBuffer.test(bBufCur--))
			{
				code[codeCur++] = '1';
			}
			else
			{
				code[codeCur++] = '0';
			}
			char findRet = findChar(code, codes, cnt);
			if (findRet != -1)
			{
				text[textCur++] = findRet;
				if (textCur == TEXT_BUFFER_LEN - 1)
				{
					restore << text;
					textCur = 0;
					memset(text, 0, sizeof(text));
				}
				memset(code, 0, sizeof(code));
				codeCur = 0;
			}
		}
	}

	/* 处理尾部 */
	char end[BUFFER_LEN];
	memset(end, 0, sizeof(end));
	int endCur = 0;
	bin.read(end, sizeof(end));
	int endLen = strlen(end);
	while (endCur != endLen)
	{
		code[codeCur++] = end[endCur++];
		char findRet = findChar(code, codes, cnt);
		if (findRet != -1)
		{
			text[textCur++] = findRet;
			memset(code, 0, sizeof(code));
			codeCur = 0;
		}
	}

	/* 将译码后的文本写入文件中 */
	if (endLen != 0)
		restore << text;
	bin.close();
	restore.close();
}

char findChar(const char *code, CHPair *codes, int num)
{
	for (char i = 0; i < num; i++)
	{
		if (strcmp(code, codes[i].hCode) == 0)
			return codes[i].ch;
	}
	return -1;
}