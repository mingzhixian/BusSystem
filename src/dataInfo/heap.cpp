#include "dataInfo.h"
namespace dataInfo
{
	template <typename E>
	class heap
	{
	private:
		E *Heap;	 //堆序列的指针
		int maxsize; //堆的最大容量
		int n;		 //堆里面的元素数量

		//将元素放在它应在的位置
		void siftdown(int pos)
		{
			while (!isLeaf(pos))
			{
				int j = leftchild(pos);
				int rc = rightchild(pos);
				if ((rc < n) && prior(Heap[rc], Heap[j]))
					j = rc;
				if (prior(Heap[pos], Heap[j]))
					return;
				swap(Heap, pos, j);
				pos = j;
			}
		}

	public:
		//构造函数
		heap(E *h, int num, int max)
		{
			Heap = h;
			n = num;
			maxsize = max;
			buildHeap();
		}
		//返回堆的大小
		int size() const
		{
			return n;
		}
		//判断是否为叶节点
		bool isLeaf(int pos) const
		{
			return (pos >= n / 2) && (pos < n);
		}
		//返回左节点
		int leftchild(int pos) const
		{
			return 2 * pos + 1;
		}
		//返回右节点
		int rightchild(int pos) const
		{
			return 2 * pos + 2;
		}
		//返回父节点
		int parent(int pos) const
		{
			return (pos - 1) / 2;
		}
		//建堆
		void buildHeap()
		{
			for (int i = n / 2 - 1; i >= 0; i--)
				siftdown(i);
		}
		//插入一个元素
		void insert(const E &it)
		{
			assert(n < maxsize, "Heap is full");
			int curr = n++;
			Heap[curr] = it;
			while ((curr != 0) && (prior(Heap[curr], Heap[parent(curr)])))
			{
				swap(Heap, curr, parent(curr));
				curr = parent(curr);
			}
		}
		//移除根节点
		E removefirst()
		{
			assert(n > 0, "Heap is empty");
			swap(Heap, 0, --n);
			if (n != 0)
				siftdown(0);
			return Heap[n];
		}
		//移除任意一个元素
		E remove(int pos)
		{
			assert((pos >= 0) && (pos < n), "Bad position");
			if (pos == (n - 1))
				n--;
			else
			{
				swap(Heap, pos, --n);
				while ((pos) != 0 && (prior(Heap[pos], Heap[parent(pos)])))
				{
					swap(Heap, pos, parent(pos));
					pos = parent(pos);
				}
				if (n != 0)
					siftdown(pos);
			}
			return Heap[n];
		}
		//判断第一个参数是否再第二个参数之前
		bool prior(E a, E b)
		{

			if (a > b)
				return true;
			else
				return false;
		}
		//交换值
		void swap(E *heap, int i, int j)
		{
			E temp;
			temp = heap[i];
			heap[i] = heap[j];
			heap[j] = temp;
		}
		//打印
		void print()
		{
			for (int i = 0; i < n; i++)
			{
				cout << Heap[i] << " ";
			}
			cout << endl;
		}
	};
}