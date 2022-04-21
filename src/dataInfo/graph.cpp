#include "dataInfo"
namespace datainfo
{
	//初始化图
	void initGraphLink(GraphLink *g)
	{
		//初始化最大节点个数以及当前节点个数、当前边数
		g->MaxVertices = 300;
		g->NumVertices = g->NumEdges = 0;

		//分配顶点链表空间
		g->nodeTable = (Vertex *)malloc(sizeof(Vertex) * g->MaxVertices);
		//将所有顶点的边置空
		for (int i = 0; i < g->MaxVertices; ++i)
		{
			g->nodeTable[i].adj = NULL;
		}
	}

	//显示图
	void showGraphLink(GraphLink *g)
	{
		//如果图为空则返回
		if (NULL == g)
			return;
		//按照当前顶点数目打印边链
		for (int i = 0; i < g->NumVertices; i++)
		{
			//打印站点的下标以及站点名字
			cout << i << g->nodeTable[i].data.name << " : ";
			Edge *p = g->nodeTable[i].adj;
			//打印该顶点每一条边
			while (NULL != p)
			{
				cout << g->nodeTable[p->idx].data.name << " <- "
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
	void insertVertex(GraphLink *g, T v)
	{
		//判断是否超出图的最大范围
		if (g->NumVertices >= g->MaxVertices)
			return;
		g->nodeTable[g->NumVertices++].data = v;
	}

	//查找顶点在顶点链表的下标
	int getVertexIndex(GraphLink *g, T v)
	{
		for (int i = 0; i < g->NumVertices; ++i)
		{
			if (v == g->nodeTable[i].data)
				return i;
		}
		//为找到返回-1
		return -1;
	}

	//获取边
	Edge *getEdge(GraphLink *g, T v1, T v2)
	{
		//查找顶点在图中的下标
		int p1 = getVertexIndex(g, v1);
		int p2 = getVertexIndex(g, v2);
		Edge *p = g->nodeTable[p1].adj;
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
	void createEdgeTail(Edge **e, int idx, string bus[20], int busTime, int walk, int walkTime)
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
	void createEdgeHead(Edge **e, int p1, int p2, string bus[20], int busTime, int walk, int walkTime)
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
	void insertEdgeTail(GraphLink *g, T v1, T v2, string bus[20], int busTime, int walk, int walkTime)
	{
		//查找顶点在图中的下标
		int p1 = getVertexIndex(g, v1);
		int p2 = getVertexIndex(g, v2);
		//顶点不存在则退出
		if (p1 == -1 || p2 == -1)
			return;
		Edge *edge1 = getEdge(g, v1, v2);
		if (edge1 != NULL)
		{
			//如果已存在边，则增加公交
			Edge *edge2 = getEdge(g, v2, v1);
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
			createEdgeTail(&(g->nodeTable[p1].adj), p2, bus, busTime, walk, walkTime);
			g->NumEdges++;
			createEdgeTail(&(g->nodeTable[p2].adj), p1, bus, busTime, walk, walkTime);
			g->NumEdges++;
		}
	}

	//插入边关系(头插）,一般使用头插入，因为尾插入需要循环找到末尾，浪费时间
	void insertEdgeHead(GraphLink *g, T v1, T v2, string bus[20], int busTime, int walk, int walkTime)
	{
		//查找顶点在图中的下标
		int p1 = getVertexIndex(g, v1);
		int p2 = getVertexIndex(g, v2);
		//顶点不存在则退出
		if (p1 == -1 || p2 == -1)
			return;
		Edge *edge1 = getEdge(g, v1, v2);

		if (edge1 != NULL)
		{
			//如果已存在边，则增加公交
			Edge *edge2 = getEdge(g, v2, v1);
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
			createEdgeHead(&(g->nodeTable[p1].adj), p1, p2, bus, busTime, walk, walkTime);
			g->NumEdges++;
			createEdgeHead(&(g->nodeTable[p2].adj), p2, p1, bus, busTime, walk, walkTime);
			g->NumEdges++;
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
	void removeEdge(GraphLink *g, T v1, T v2)
	{
		//查找顶点在图中的下标
		int p1 = getVertexIndex(g, v1);
		int p2 = getVertexIndex(g, v2);
		//顶点不存在则退出
		if (p1 == -1 || p2 == -1)
			return;

		//删除边
		int r = delateEdge(&(g->nodeTable[p1].adj), p2);
		//如果删除成功则继续删除另一个顶点对应的边
		if (r == 0)
		{
			g->NumEdges--;
			delateEdge(&(g->nodeTable[p2].adj), p1);
			g->NumEdges--;
		}
	}

	//删除顶点
	void removeVertex(GraphLink *g, T v)
	{
		//查找顶点下标
		int p = getVertexIndex(g, v);
		//顶点不存在则返回
		if (p == -1)
			return;
		//删除目标顶点以外的顶点与目标顶点之间的边
		for (int i = 0; i < g->NumVertices; ++i)
		{
			if (i == p)
			{
				continue;
			}
			else
			{
				delateEdge(&(g->nodeTable[i].adj), p);
			}
		}
		//删除目标顶点行的所有边
		Edge *te = g->nodeTable[p].adj;
		Edge *tmp;
		while (te != NULL)
		{
			tmp = te;
			te = te->link;
			free(tmp);
		}
		//让被删除顶点那行，指向最后一个顶点那行。
		g->nodeTable[p].data = g->nodeTable[g->NumVertices - 1].data;
		g->nodeTable[p].adj = g->nodeTable[g->NumVertices - 1].adj;
		//此处删除的本质为将最后一行提前到p的位置，然后把最后一行删掉。
		//获取p的边链(值与最后一行的边链相同)
		tmp = g->nodeTable[p].adj;
		Edge *q;
		while (tmp != NULL)
		{
			//获取最后一行的边链的边所对应的另一个顶点的边链
			q = g->nodeTable[tmp->idx].adj;
			//查找出q与最后一行有关系的边
			while (q != NULL && q->idx != g->NumVertices - 1)
			{
				q = q->link;
			}
			//将该边所对应的顶点位置改为p的位置
			q->idx = p;
			//最后一行的边向右移
			tmp = tmp->link;
		}
		//目前顶点数目减少
		g->NumVertices--;
	}

	//清空图
	void destroyGraphLink(GraphLink *g)
	{
		//释放所有边的内存空间
		Edge *t = NULL;
		Edge *p = NULL;
		//删除每个顶点的边链
		for (int i = 0; i < g->NumVertices; ++i)
		{
			t = g->nodeTable[i].adj;
			while (NULL != t)
			{
				p = t;
				t = t->link;
				free(p);
			}
		}
		//释放所有顶点的内存空间
		free(g->nodeTable);
		g->nodeTable = NULL;
		g->MaxVertices = g->NumVertices = g->NumEdges = 0;
	}

	//获取两点之间最短路径：算法
	void floyd(GraphLink *g)
	{
	}
}