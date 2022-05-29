#include "public.h"
#include "dataInfo.h"
namespace dataInfo
{
	//销毁哈希表
	Hash::~Hash()
	{
		//清除每一种情况
		for (int i = 0; i < maxSize; i++)
		{
			//如果该种情况不为空，则清除该链
			if (data[i] != NULL)
			{
				HashItem *p = data[i];
				while (p->next)
				{
					HashItem *q = p->next;
					p->next = p->next->next;
					delete q;
				}
				data[i] = NULL;
				delete p;
			}
		}
	}

	//哈希散列算法
	int Hash::hashFunction(T v1, T v2)
	{
		//获取实例的信息
		string tmp1 = v1.name + v2.name;
		char tmp2[tmp1.size() + 1];
		strcpy(tmp2, tmp1.c_str());
		char *tmp3 = tmp2;

		//哈希计算
		int hash1 = 5381;
		while (*tmp3)
		{
			hash1 += (hash1 << 5) + (*tmp3++);
		}

		//反转信息
		tmp1 = v2.name + v1.name;
		strcpy(tmp2, tmp1.c_str());
		tmp3 = tmp2;

		//哈希计算
		int hash2 = 5381;
		while (*tmp3)
		{
			hash2 += (hash2 << 5) + (*tmp3++);
		}

		//返回值
		return ((hash1 + hash2) & 0x7FFFFFFF) % maxSize;
	}

	//添加一个实例，成功返回1,否则返回0
	int Hash::addItem(T v1, T v2, int m, string s)
	{
		int index = hashFunction(v1, v2);
		//此种情况没有实例
		if (data[index] == NULL)
		{
			data[index] = new HashItem(v1, v2, s, m);
			return 1;
		}
		//此情况存在实例，则检查其后面是否存在本实例，不存在则新加（为提高速度使用头插入）
		else
		{
			//寻找该实例
			HashItem *p = data[index];
			while (p)
			{
				//找到添加
				if ((p->data1 == v1 && p->data2 == v2) || (p->data1 == v2 && p->data2 == v1))
				{
					p->route[m] = s;
					return 1;
				}
				p = p->next;
			}
			//找不到该实例则新建一个
			p = new HashItem(v1, v2, s, m, data[index]->next);
			data[index]->next = p;
			return 1;
		}
		return 0;
	}

	//删除一个实例，成功返回1,否则返回0
	int Hash::removeItem(T v1, T v2)
	{
		int index = hashFunction(v1, v2);
		//此种情况没有实例
		if (data[index] == NULL)
		{
			return 1;
		}
		//此情况存在实例，则在其后面查找本实例并删除
		else
		{
			HashItem *p = data[index];
			HashItem *q = p;
			//检查第一个是否为该实例
			if (p->data1 == v1 && p->data2 == v2 || p->data1 == v2 && p->data2 == v1)
			{
				data[index] = p->next;
				delete q;
				return 1;
			}
			//不是第一个则开始检查后面的
			p = p->next;
			while (p)
			{
				//找到删除
				if ((p->data1 == v1 && p->data2 == v2) || (p->data1 == v2 && p->data2 == v1))
				{
					q->next = p->next;
					delete p;
					return 1;
				}
				q = p;
				p = p->next;
			}
			//一直未找到则返回0
			return 0;
		}
	}

	//获取一个实例，找不到返回空HashItem
	HashItem Hash::findItem(T v1, T v2)
	{
		int index = hashFunction(v1, v2);
		HashItem *p = data[index];
		while (p)
		{
			//找到添加
			if ((p->data1 == v1 && p->data2 == v2) || (p->data1 == v2 && p->data2 == v1))
			{
				return *p;
			}
			p = p->next;
		}
		//找不到返回空HashItem
		return HashItem();
	}
};