#include "public.h"
#include "dataInfo.h"
using namespace dataInfo;

#ifndef _CACHE
#define _CACHE
namespace cache
{
	class item
	{
	private:
		string name;
		string drink;
		item *next;

	public:
		item() : name("empty"), drink("empty"), next(nullptr) {}
		item(string n, string d) : name(n), drink(d), next(nullptr) {}
	};
	class Hash
	{
	private:
		static const int tableSize = 10; // 存储量可改变
		item *HashTable[tableSize];

	public:
		int hashFunction(string key);
		Hash();
		~Hash();
		void AddItem(string name, string drink);
		int NumberOfItemsInIndex(int index);
		void PrintTable();
		void PrintItemsInIndex(int index);
		void FindDrink(string name);
		void RemoveItem(string name);
	};
	class cache
	{
	private:
		/* data */
	public:
		cache(/* args */);
		~cache();
	};
};
#endif