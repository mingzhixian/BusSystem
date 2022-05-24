#include "public.h"
#include "dataInfo.h"
using namespace dataInfo;

#ifndef _CACHE
#define _CACHE
namespace cache
{
	//哈希表中每一个实例
	class HashItem
	{
	public:
		//顶点1
		T data1;
		//顶点2
		T data2;
		//转乘信息,计算模式：时间最短优先1、步行最短优先0
		string route[2] = {"", ""};
		HashItem *next = NULL;

		HashItem(){};
		HashItem(T v1, T v2, string s, int m, HashItem *n = NULL) : data1(v1), data2(v2), next(n) { route[m] = s; }
	};

	//哈希表
	class Hash
	{
	private:
		//哈希表的大小
		int size = 0;
		//哈希散列算法最大多少种种情况，并非越大越好，合理取值，一般在所有情况的五分之一至十分之一
		static const int maxSize = 2048;
		//本哈希散列算法最大2048种情况，每一个指针为一个链，即data[4]为哈希散列结果为4的所有item的链表。
		HashItem *data[maxSize] = {NULL};

	public:
		//哈希散列算法
		int hashFunction(T v1, T v2);
		//销毁哈希表
		~Hash();
		//添加一个实例，成功返回1,否则返回0
		int addItem(T v1, T v2, int m, string s);
		//删除一个实例，成功返回1,否则返回0
		int removeItem(T v1, T v2);
		//获取哈希表的大小
		inline int getSize() { return size; };
		//查询一个实例，找不到返回空HashItem
		HashItem findItem(T v1, T v2);
	};

};
#endif