#include "evaluate.h"

using namespace std;

void evaluate(const char *TITLE)
{
	compare(TITLE);
	calcCompress(TITLE);
}

void compare(const char *TITLE)
{
	char ori[MAX_TITLE_LEN];
	strcpy(ori, TITLE);
	strcat(ori, ".txt");

	char res[MAX_TITLE_LEN];
	strcpy(res, TITLE);
	strcat(res, "(restore).txt");

	struct stat oriStat;
	size_t oriSize = 0;
	if (stat(ori, &oriStat) == 0)
		oriSize = oriStat.st_size;    // 读取文件大小
	else
		exit(11);    // 读取文件信息失败，错误码11

	struct stat resStat;
	size_t resSize = 0;
	if (stat(res, &resStat) == 0)
		resSize = resStat.st_size;
	else
		exit(11);

	if (oriSize != resSize)
	{
		cout << "译码后文件与原文件不一致" << endl;
		cout << "文件大小不一致" << endl;
		return;
	}

	size_t size = oriSize;
	ifstream oriFile(ori, ios::in | ios::binary);
	ifstream resFile(res, ios::in | ios::binary);
	if (size <= TEXT_BUFFER_LEN)
	{
		char oriText[oriSize];
		oriFile.read(oriText, oriSize);
		oriFile.close();

		char resText[resSize];
		resFile.read(resText, resSize);
		resFile.close();

		for (size_t i = 0; i < oriSize; i++)
		{
			if (oriText[i] != resText[i])
			{
				cout << "译码后文件与原文件不一致" << endl;
				cout << oriText[i] << "!=" << resText[i] << endl;
				return;
			}
		}
	}
	else
	{
		char oriBuffer[TEXT_BUFFER_LEN];
		char resBuffer[TEXT_BUFFER_LEN];
		while (oriFile.peek() != EOF)
		{
			memset(oriBuffer, 0, sizeof(oriBuffer));
			memset(resBuffer, 0, sizeof(resBuffer));
			oriFile.read(oriBuffer, TEXT_BUFFER_LEN);
			resFile.read(resBuffer, TEXT_BUFFER_LEN);
			for (size_t i = 0; i < TEXT_BUFFER_LEN; i++)
			{
				if (oriBuffer[i] != resBuffer[i])
				{
					cout << "译码后文件与原文件不一致" << endl;
					cout << oriBuffer[i] << "!=" << resBuffer[i] << endl;
					return;
				}
			}
		}
	}

	cout << "无差异" << endl;
}

void calcCompress(const char *TITLE)
{
	char ori[MAX_TITLE_LEN];
	strcpy(ori, TITLE);
	strcat(ori, ".txt");

	char bin[MAX_TITLE_LEN];
	strcpy(bin, TITLE);
	strcat(bin, ".bin");

	struct stat oriStat;
	size_t oriSize = 0;
	if (stat(ori, &oriStat) == 0)
		oriSize = oriStat.st_size;    // 读取文件大小
	else
		exit(11);    // 读取文件信息失败，错误码11

	struct stat binStat;
	size_t binSize = 0;
	if (stat(bin, &binStat) == 0)
		binSize = binStat.st_size;
	else
		exit(11);

	double compressRate = 1.0*binSize/oriSize;
	cout << "文件压缩率为 " << compressRate*100 << '%' << endl;
}