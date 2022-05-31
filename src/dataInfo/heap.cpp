#include "dataInfo.h"
namespace dataInfo
{
	//构造函数
	Heap::Heap(const int h[], int n) : num(n)
	{
		data = new int *[num];
		for (int i = 0; i < num; i++)
		{
			data[i] = new int[2];
		}
		site = new int[num];
		for (int i = 0; i < num; i++)
		{
			data[i][0] = h[i];
			data[i][1] = i;
			site[i] = i;
		}
		for (int i = num / 2 - 1; i >= 0; i--)
			siftDown(i);
	}
	//交换值
	inline void Heap::swap(int i, int j)
	{
		int tmp2 = site[data[i][1]];
		site[data[i][1]] = site[j];
		site[data[j][1]] = tmp2;
		int *tmp1 = data[i];
		data[i] = data[j];
		data[j] = tmp1;
	}
	//向上递归
	void Heap::siftDown(int pos)
	{
		while (!isLeaf(pos))
		{
			//获取子节点的site中的位置。
			int j = leftchild(pos);
			int rc = rightchild(pos);
			//找出左右孩子中最大的一个
			if ((rc < num) && prior(data[rc], data[j]))
				j = rc;
			//如果根已经是子节点中最大的一个则返回。
			if (prior(data[pos], data[j]))
				return;
			//交换，使根节点成为最大的一个。
			swap(pos, j);
			//向下递归子节点。（因为子节点与根节点交换发生了变动）
			pos = j;
		}
	}
	//上溯
	void Heap::siftUp(int pos)
	{
		while ((pos != 0) && (prior(data[pos], data[parent(pos)])))
		{
			swap(pos, parent(pos));
			pos = parent(pos);
		}
	}
	//更新
	void Heap::update(int i, int d)
	{
		for (int ii = 0; ii < num; ii++)
		{
			cout << site[ii];
		}
		cout << endl;
		int pos = site[i];
		data[pos][0] = d;
		siftUp(pos);
		siftDown(pos);
	}
	//判断是否为叶节点
	inline bool Heap::isLeaf(int pos)
	{
		return (pos >= num / 2) && (pos < num);
	}
	//返回左节点
	inline int Heap::leftchild(int pos)
	{
		return 2 * pos + 1;
	}
	//返回右节点
	inline int Heap::rightchild(int pos)
	{
		return 2 * pos + 2;
	}
	//返回父节点
	inline int Heap::parent(int pos)
	{
		return (pos - 1) / 2;
	}
	//判断大小-小根堆
	inline bool Heap::prior(int *a, int *b)
	{
		return a[0] > b[0] ? false : true;
	}
	//返回堆的大小
	int Heap::size() const
	{
		return num;
	}
	//移除根节点
	int *Heap::removeFirst()
	{
		if (num <= 0)
		{
			cout << "堆已空。" << endl;
			throw -1;
		}
		swap(0, --num);
		if (num != 0)
			siftDown(0);
		return data[num];
	}
	//打印
	void Heap::print()
	{
		for (int i = 0; i < num; i++)
		{
			cout << data[i][1] << " " << data[i][0] << endl;
		}
	}
}