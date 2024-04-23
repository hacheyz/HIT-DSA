#include "encode.h"

using namespace std;

void getHuffmanCode(HuffmanTree HT, CHPair *codes)
{
	int cnt = 0;
	for (int i = 0; i < HT.size; i++) // 从结点向上回溯
	{
		if (HT.nodes[i].ch != 0)	// 如果是叶子节点
		{
			HTNode leaf = HT.nodes[i];
			codes[cnt].ch = leaf.ch;
			Stack<char> s;		// 借助栈实现编码逆置
			int p = leaf.parent;
			int q = i;
			while (1)
			{
				if (HT.nodes[p].lChild == q)
					s.push('0');
				else
					s.push('1');
				q = p;
				p = HT.nodes[p].parent;	// 向上回溯
				if (p == STATIC_NULL)
					break;
			}
			int j = 0;
			while (!s.isEmpty())
			{
				char top = s.pop();
				codes[cnt].hCode[j++] = top;
			}
			codes[cnt].hCode[j] = 0;
			codes[cnt].len = j;
			cnt++;
		}
	}
}

void showHuffmanCodes(CHPair *codes, int num)
{
	cout << "字符集的哈夫曼编码表" << endl;
	for (int i = 0; i < num; i++)
	{
		if (codes[i].ch == '\n')
			printf("%02x-'\\n': %s\n", codes[i].ch, codes[i].hCode);
		else if (codes[i].ch == '\r')
			printf("%02x-'\\r': %s\n", codes[i].ch, codes[i].hCode);
		else
			printf("%02x-'%c' : %s\n", codes[i].ch, codes[i].ch, codes[i].hCode);
	}
}

void saveHuffmanCodes(const char *TITLE, CHPair *codes, int num)
{
	char codeFile[MAX_TITLE_LEN];
	strcpy(codeFile, TITLE);
	strcat(codeFile, ".cd");
	ofstream out(codeFile, ios::out | ios::binary);
	for (int i = 0; i < num; i++)
	{
		out.write((char *)(codes + i), sizeof(CHPair));
	}
	out.close();
}

void encode(char *text, size_t textLen, const char *TITLE, CHPair *codes, int codeNum)
{
	char binaryFile[MAX_TITLE_LEN];
	strcpy(binaryFile, TITLE);
	strcat(binaryFile, ".bin");
	ofstream out(binaryFile, ios::out | ios::binary);
	CHPair alignedCodes[CHAR_NUM];
	memset(alignedCodes, 0, sizeof(alignedCodes));
	/* 将 codes 的下标对齐到 ch 的 ASCII 值 */
	for (int i = 0; i < codeNum; i++)
	{
		alignedCodes[codes[i].ch] = codes[i];
	}
	char charBuffer[BUFFER_LEN];    // 0-1 字符缓冲区，存满后写入 bitBuffer
	memset(charBuffer, 0, sizeof(charBuffer));
	int cBufCur = 0;
	/* 对文件进行编码 */
	for (size_t i = 0; i < textLen; i++)
	{
		CHPair thisChar = alignedCodes[text[i]];
		char *code = thisChar.hCode;
		int codeLen = thisChar.len;
		int space = BUFFER_LEN - cBufCur;
		if (space >= codeLen)
		{
			strcat(charBuffer, code);
			cBufCur += codeLen;
		}
		else
		{
			int codeCur = 0;
			while (cBufCur < BUFFER_LEN)
			{
				charBuffer[cBufCur++] = code[codeCur++];
			}
			bitset<BUFFER_LEN> bitBuffer(charBuffer);    // 0-1 bit 缓冲区，将 charBuffer 直接转换为位数据
			out.write((char *)&bitBuffer, sizeof(bitBuffer));
			memset(charBuffer, 0, sizeof(charBuffer));
			cBufCur = 0;
			while (codeCur < codeLen)
			{
				charBuffer[cBufCur++] = code[codeCur];
				codeCur++;
			}
		}
	}
	if (charBuffer[0] != 0)
	{
		bitset<BUFFER_LEN> bitBuffer(ALL_ONE_SEQ);
		out.write((char *)&bitBuffer, sizeof(bitBuffer));
		out << charBuffer;
	}
	out.close();
}