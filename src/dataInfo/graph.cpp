#include "dataInfo.h"
namespace dataInfo
{
	//初始化图
	GraphLink::GraphLink()
	{
		//初始化最大节点个数以及当前节点个数、当前边数
		MaxVertices = 300;
		NumVertices = NumEdges = 0;

		//分配顶点链表空间
		nodeTable = (Vertex *)malloc(sizeof(Vertex) * MaxVertices);
		//将所有顶点的边置空
		for (int i = 0; i < MaxVertices; ++i)
		{
			nodeTable[i].adj = NULL;
		}
	}

	//显示图
	void GraphLink::showGraphLink()
	{
		//按照当前顶点数目打印边链
		for (int i = 0; i < NumVertices; i++)
		{
			//打印站点的下标以及站点名字
			cout << i << nodeTable[i].data.name << " : ";
			Edge *p = nodeTable[i].adj;
			//打印该顶点每一条边
			while (NULL != p)
			{
				cout << nodeTable[p->idx].data.name << " <- "
					 << "bus:";
				int i = 0;
				while (p->bus[i] != "")
				{
					cout << p->bus[i] << " ";
					i++;
				}
				cout << "bustime:" << p->busTime << "walk:" << p->walk << "walktime:" << p->walkTime << " -> ";
				;
				p = p->link;
			}
			//换行
			cout << endl;
		}
	}

	//插入顶点
	void GraphLink::insertVertex(T v)
	{
		//判断是否超出图的最大范围
		if (NumVertices >= MaxVertices)
			return;
		nodeTable[NumVertices++].data = v;
	}

	//查找顶点在顶点链表的下标
	int GraphLink::getVertexIndex(T v)
	{
		for (int i = 0; i < NumVertices; ++i)
		{
			if (v == nodeTable[i].data)
				return i;
		}
		//为找到返回-1
		return -1;
	}

	//获取边
	Edge *GraphLink::getEdge(T v1, T v2)
	{
		//查找顶点在图中的下标
		int p1 = getVertexIndex(v1);
		int p2 = getVertexIndex(v2);
		Edge *p = nodeTable[p1].adj;
		//顶点不存在或边链为空则退出
		if (p1 == -1 || p2 == -1 || p == NULL)
			return NULL;
		//判断第一个边是否是目标边
		if (p->idx == p2)
		{
			//返回第一条边
			return p;
		}
		//寻找边
		Edge *tmp = p;
		while (tmp->link != NULL && tmp->link->idx != p2)
		{
			tmp = tmp->link;
		}
		//没有找到边
		if (tmp->link == NULL)
		{
			return NULL;
		}
		//找到边
		else
		{
			return tmp->link;
		}
	}

	//创建边，传入顶点的边链和新边参数，服务于insertEdgeTail函数
	void GraphLink::createEdgeTail(Edge **e, int idx, string bus[20], int busTime, int walk, int walkTime)
	{
		//分配新边的空间
		Edge *p = (Edge *)malloc(sizeof(Edge));
		//给新边赋值
		p->idx = idx;
		for (int i = 0; i < 20; i++)
		{
			p->bus[i] = bus[i];
		}
		p->busTime = busTime;
		p->walk = walk;
		p->walkTime = walkTime;
		p->link = NULL;
		//如果穿传进来的边链为空边则直接赋值
		if (NULL == *e)
		{
			*e = p;
		}
		//否则找到边连的最右边新建边
		else
		{
			Edge *tmp = *e;
			while (tmp->link != NULL)
			{
				tmp = tmp->link;
			}
			tmp->link = p;
		}
	}

	//创建边，传入顶点的边链和新边参数，服务于insertEdgeHead函数
	void GraphLink::createEdgeHead(Edge **e, int p1, int p2, string bus[20], int busTime, int walk, int walkTime)
	{
		// todo,找到边添加信息
		Edge *p = (Edge *)malloc(sizeof(Edge));
		p->idx = p2;
		int i = 0;
		while (bus[i] != "")
		{
			p->bus[i] = bus[i];
			i++;
		}
		p->busTime = busTime;
		p->walk = walk;
		p->walkTime = walkTime;
		p->link = *e;
		*e = p;
	}

	//插入边关系(尾插）
	void GraphLink::insertEdgeTail(T v1, T v2, string bus[20], int busTime, int walk, int walkTime)
	{
		//查找顶点在图中的下标
		int p1 = getVertexIndex(v1);
		int p2 = getVertexIndex(v2);
		//顶点不存在则退出
		if (p1 == -1 || p2 == -1)
			return;
		Edge *edge1 = getEdge(v1, v2);
		if (edge1 != NULL)
		{
			//如果已存在边，则增加公交
			Edge *edge2 = getEdge(v2, v1);
			int i = 0;
			while (edge1->bus[i] != "")
			{
				i++;
			}
			edge1->bus[i] = bus[0];
			i = 0;
			while (edge2->bus[i] != "")
			{
				i++;
			}
			edge2->bus[i] = bus[0];
		}
		else
		{
			//分别在顶点对应的边链末尾创建新边
			createEdgeTail(&(nodeTable[p1].adj), p2, bus, busTime, walk, walkTime);
			NumEdges++;
			createEdgeTail(&(nodeTable[p2].adj), p1, bus, busTime, walk, walkTime);
			NumEdges++;
		}
	}

	//插入边关系(头插）,一般使用头插入，因为尾插入需要循环找到末尾，浪费时间
	void GraphLink::insertEdgeHead(T v1, T v2, string bus[20], int busTime, int walk, int walkTime)
	{
		//查找顶点在图中的下标
		int p1 = getVertexIndex(v1);
		int p2 = getVertexIndex(v2);
		//顶点不存在则退出
		if (p1 == -1 || p2 == -1)
			return;
		Edge *edge1 = getEdge(v1, v2);

		if (edge1 != NULL)
		{
			//如果已存在边，则增加公交
			Edge *edge2 = getEdge(v2, v1);
			int i = 0;
			while (edge1->bus[i] != "")
			{
				i++;
			}
			edge1->bus[i] = bus[0];
			i = 0;
			while (edge2->bus[i] != "")
			{
				i++;
			}
			edge2->bus[i] = bus[0];
		}
		else
		{
			//分别在顶点对应的边链开头创建新边
			createEdgeHead(&(nodeTable[p1].adj), p1, p2, bus, busTime, walk, walkTime);
			NumEdges++;
			createEdgeHead(&(nodeTable[p2].adj), p2, p1, bus, busTime, walk, walkTime);
			NumEdges++;
		}
	}

	//删除边，服务于removeEdge函数
	int delateEdge(Edge **p, int i)
	{
		//如果边链不存在则返回
		if (NULL == *p)
			return -1;
		Edge *f;
		//判断第一个边是否是目标边
		if ((*p)->idx == i)
		{
			//删除第一条边
			f = *p;
			*p = (*p)->link;
			free(f);
			return 0;
		}
		//寻找要删除的边
		Edge *tmp = *p;
		while (tmp->link != NULL && tmp->link->idx != i)
		{
			tmp = tmp->link;
		}
		//没有找到边
		if (tmp->link == NULL)
		{
			return -1;
		}
		//找到边
		else
		{
			f = tmp->link;
			tmp->link = tmp->link->link;
			free(f);
			return 0;
		}
	}

	//删除边
	void GraphLink::removeEdge(T v1, T v2)
	{
		//查找顶点在图中的下标
		int p1 = getVertexIndex(v1);
		int p2 = getVertexIndex(v2);
		//顶点不存在则退出
		if (p1 == -1 || p2 == -1)
			return;

		//删除边
		int r = delateEdge(&(nodeTable[p1].adj), p2);
		//如果删除成功则继续删除另一个顶点对应的边
		if (r == 0)
		{
			NumEdges--;
			delateEdge(&(nodeTable[p2].adj), p1);
			NumEdges--;
		}
	}

	//删除顶点
	void GraphLink::removeVertex(T v)
	{
		//查找顶点下标
		int p = getVertexIndex(v);
		//顶点不存在则返回
		if (p == -1)
			return;
		//删除目标顶点以外的顶点与目标顶点之间的边
		for (int i = 0; i < NumVertices; ++i)
		{
			if (i == p)
			{
				continue;
			}
			else
			{
				delateEdge(&(nodeTable[i].adj), p);
			}
		}
		//删除目标顶点行的所有边
		Edge *te = nodeTable[p].adj;
		Edge *tmp;
		while (te != NULL)
		{
			tmp = te;
			te = te->link;
			free(tmp);
		}
		//让被删除顶点那行，指向最后一个顶点那行。
		nodeTable[p].data = nodeTable[NumVertices - 1].data;
		nodeTable[p].adj = nodeTable[NumVertices - 1].adj;
		//此处删除的本质为将最后一行提前到p的位置，然后把最后一行删掉。
		//获取p的边链(值与最后一行的边链相同)
		tmp = nodeTable[p].adj;
		Edge *q;
		while (tmp != NULL)
		{
			//获取最后一行的边链的边所对应的另一个顶点的边链
			q = nodeTable[tmp->idx].adj;
			//查找出q与最后一行有关系的边
			while (q != NULL && q->idx != NumVertices - 1)
			{
				q = q->link;
			}
			//将该边所对应的顶点位置改为p的位置
			q->idx = p;
			//最后一行的边向右移
			tmp = tmp->link;
		}
		//目前顶点数目减少
		NumVertices--;
	}

	//清空图
	GraphLink::~GraphLink()
	{
		//释放所有边的内存空间
		Edge *t = NULL;
		Edge *p = NULL;
		//删除每个顶点的边链
		for (int i = 0; i < NumVertices; ++i)
		{
			t = nodeTable[i].adj;
			while (NULL != t)
			{
				p = t;
				t = t->link;
				free(p);
			}
		}
		//释放所有顶点的内存空间
		free(nodeTable);
		nodeTable = NULL;
		MaxVertices = NumVertices = NumEdges = 0;
	}

	//获取两点之间最短路径：Dijkstra算法
	void GraphLink::dijkstra(T v1, T v2, int mode)
	{
	}
}