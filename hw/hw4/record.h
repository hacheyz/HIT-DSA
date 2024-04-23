#ifndef HW4_RECORD_H
#define HW4_RECORD_H

#define RECORD_LENGTH 1024 // 测试用例大小 (查找成功 & 查找失败)

template<typename Keytype>
class Record
{
public:
	Keytype key; // 记录的关键字
	// Field other; // 记录的其他项

	Record(Keytype key) : key(key)
	{
	}
};

#endif //HW4_RECORD_H
