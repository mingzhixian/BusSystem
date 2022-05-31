#include "dataInfo.h"
namespace dataInfo
{
	//初始化图
	GraphLink::GraphLink()
	{
		//初始化最大节点个数以及当前节点个数、当前边数
		MaxVertices = 3000;
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
				cout << "bustime:" << p->busTime << " walk: " << p->walk << " walktime: " << p->walkTime << " -> ";
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

	//更新边关系（不需要更新的值置为NULL即可）
	void GraphLink::setEdgeWalk(T v1, T v2, int walk, int walkTime)
	{
		//查找顶点在图中的下标
		int p1 = getVertexIndex(v1);
		int p2 = getVertexIndex(v2);
		//顶点不存在则退出
		if (p1 == -1 || p2 == -1)
			return;

		Edge *edge1 = getEdge(v1, v2);
		Edge *edge2 = getEdge(v2, v1);

		//如果存在公交线路
		if (edge1 != NULL && edge2 != NULL)
		{
			edge1->walk = walk == NULL ? edge1->walk : walk;
			edge2->walk = walk == NULL ? edge2->walk : walk;
			edge1->walkTime = walkTime == NULL ? edge1->walkTime : walkTime;
			edge2->walkTime = walkTime == NULL ? edge2->walkTime : walkTime;
		}
		//如果两站之间不存在公交线路
		else
		{
			string bus[20];
			insertEdgeHead(v1, v2, bus, 10000, walk, walkTime);
		};
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

	// Dijkstra算法
	string *GraphLink::dijkstra(T v1, int mode, Hash *cache)
	{
		// s存储已求出最短路径的顶点(以及相应的最短路径长度)，u记录还未求出最短路径的顶点(以及该顶点到起点s的距离),isS记录已经进入s的顶点，已经进入s则为true,p记录当前路径下到达他的上一个节点
		int s[NumVertices], u[NumVertices], p[NumVertices];
		bool isS[NumVertices] = {false};
		for (int i = 0; i < NumVertices; i++)
		{
			s[i] = 10000;
			u[i] = 10000;
			p[i] = 10000;
		}
		//堆
		// Heap h(u, NumVertices);
		//初始化
		//查找开始节点的下标
		int p1 = getVertexIndex(v1);
		isS[p1] = true;
		s[p1] = 0;
		p[p1] = p1;
		Edge *q = nodeTable[p1].adj;
		//寻找该顶点每一条边
		while (NULL != q)
		{
			u[q->idx] = minTime(q->busTime, q->walkTime, mode);
			// h.update(q->idx, minTime(q->busTime, q->walkTime, mode));
			p[q->idx] = p1;
			q = q->link;
		}
		//循环遍历,循环NumVertices-1次，找出除初识节点的所有节点
		for (int i = 0; i < NumVertices - 1; i++)
		{
			//寻找u中最小顶点
			int mini = 0, tmp_minTime = 10000;
			for (int z = 0; z < NumVertices; z++)
			{
				if (u[z] < tmp_minTime && !isS[z])
				{
					tmp_minTime = u[z];
					mini = z;
				}
			}
			/* int *tmpH = h.removeFirst();
			cout << mini << "  " << tmpH[1] << endl;
			cout << tmp_minTime << "  " << tmpH[0] << endl;
			cout << endl; */
			s[mini] = tmp_minTime;
			isS[mini] = true;
			//开始检查最小点所连的边
			q = nodeTable[mini].adj;
			//寻找该顶点每一条边
			while (NULL != q)
			{
				//没有在s中的
				if (!isS[q->idx])
				{
					int time = minTime(q->busTime, q->walkTime, mode) + tmp_minTime;
					if (u[q->idx] > time)
					{
						u[q->idx] = time;
						/* cout << "update:" << q->idx << "  :" << time << endl;
						h.update(q->idx, time);
						h.print(); */
						p[q->idx] = mini;
					}
				}
				q = q->link;
			}
		}
		//返回结果
		string *finish = new string[NumVertices];
		for (int i = 0; i < NumVertices; i++)
		{
			finish[i] = "";
			//排除本站到本站
			if (i == p1)
			{
				continue;
			}

			//找出总起点到i站的最短路径（倒序，path[0]为终点）
			int z = i, path[NumEdges], changeSite = 0;
			while (z != p1)
			{
				path[changeSite++] = z;
				z = p[z];
			}
			path[changeSite] = z;
			//组装为json数据
			string tmpFinish = "{\"route\":[";
			int tmpWalk = 0, tmpWalkTime = 0, tmpBusTime = 0;
			//循环至到达终点，path[0]为终点。
			//上一站的公交车和本站的公交车
			string busOld = "", busNow = "";
			while (changeSite != 0)
			{
				//获取本站到下一站的边
				Edge *q = getEdge(nodeTable[path[changeSite]].data, nodeTable[path[changeSite - 1]].data);
				//检查上一站的公交能否到达下一站
				busNow = "";
				//步行情况
				if (q->busTime == 10000)
				{
					tmpWalk += q->walk;
					tmpWalkTime += q->walkTime;
					busNow = "-1";
				}
				//坐车情况
				else if (q->walkTime == 10000)
				{
					int tmpI = 0;
					while (q->bus[tmpI] != "")
					{
						if (busOld == q->bus[tmpI])
						{
							busNow = busOld;
						}
						tmpI++;
					};
					//上一站的公交不能到达下一站，则换乘
					if (busNow == "")
					{
						busNow = q->bus[0];
					}
					tmpBusTime += q->busTime;
				}
				//既可以坐车也可以走路情况
				else
				{
					//时间最短优先
					if (mode == 1)
					{
						tmpWalk += q->walk;
						tmpWalkTime += q->walkTime;
						busNow ="-1";
					}
					//步行最少优先
					else
					{
						int tmpI = 0;
						while (q->bus[tmpI] != "")
						{
							if (busOld == q->bus[tmpI])
							{
								busNow = busOld;
							}
							tmpI++;
						};
						//上一站的公交不能到达下一站，则换乘
						if (busNow == "")
						{
							busNow = q->bus[0];
						}
						tmpBusTime += q->busTime;
					}
				}

				//组装数据
				tmpFinish += "{\"bus\":\"" + busNow + "\",\"source\":\"" + nodeTable[path[changeSite]].data.name + "\",\"purpose\":\"" + nodeTable[path[changeSite - 1]].data.name + "\"}";
				changeSite--;
				//最后一个不加逗号
				if (changeSite != 0)
				{
					tmpFinish += ",";
				}
			}
			tmpFinish += "],\"meter\":\"" + to_string(tmpWalk) + "\",\"busTime\":\"" + to_string(tmpBusTime) + "\",\"walkTime\":\"" + to_string(tmpWalkTime) + "\"}";
			//添加到返回值中
			finish[i] = tmpFinish;
			//加入缓存
			cache->addItem(nodeTable[p1].data, nodeTable[i].data, mode, tmpFinish);
		}
		return finish;
	}

	//获取两点之间最短路径
	string GraphLink::getShortest(T v1, T v2, int mode, Hash *cache)
	{
		//利用dijkstra算法求出起点到所有节点的最短路径
		string *f = dijkstra(v1, mode, cache);
		//获取起点到终点的最短路径
		int p2 = getVertexIndex(v2);
		return f[p2];
	}

	//模式选择，服务于最短路径算法
	inline int GraphLink::minTime(int busTime, int walkTime, int mode)
	{
		//只有公交或只有步行时
		if (busTime == 10000 || walkTime == 10000)
		{
			return busTime > walkTime ? walkTime : busTime;
		}
		//又有公交又有步行时
		if (mode == 1)
		{
			return busTime > walkTime ? walkTime : busTime;
		}
		else if (mode == 2)
		{
			return busTime;
		}
	}
}