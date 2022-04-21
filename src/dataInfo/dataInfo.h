#include <iostream>
#include <string.h>
#include <malloc.h>

using namespace std;

#ifndef _DATA_INFO
#define _DATA_INFO
namespace datainfo
{
    //图文件

    //节点结构
    typedef struct T
    {
        string name = "";
        //重载相等操作符
        bool operator==(const T &obj)
        {
            return (name == obj.name);
        }
    } T;

    //边的结构
    typedef struct Edge
    {
        //顶点的下标
        int idx;
        //公交车
        string bus[20];
        //公交时间
        int busTime;
        //步行
        int walk;
        //步行时间
        int walkTime;
        //指向下一个边的指针
        struct Edge *link;
    } Edge;

    //顶点的结构
    typedef struct Vertex
    {
        //顶点的值
        T data;
        //边
        Edge *adj;
    } Vertex;

    //图的结构
    typedef struct GraphLink
    {
        //最大节点数目
        int MaxVertices;
        //目前节点数目
        int NumVertices;
        //边的数目
        int NumEdges;
        //顶点的链表
        Vertex *nodeTable;
    } GraphLink;

    //初始化图
    extern void initGraphLink(GraphLink *g);

    //显示图
    extern void showGraphLink(GraphLink *g);

    //插入顶点
    extern void insertVertex(GraphLink *g, T v);

    //查找顶点在顶点链表的下标
    extern int getVertexIndex(GraphLink *g, T v);

    //获取边
    extern Edge *getEdge(GraphLink *g, T v1, T v2);

    //插入边关系(尾插）
    extern void insertEdgeTail(GraphLink *g, T v1, T v2, string bus[20], int busTime, int walk, int walkTime);

    //插入边关系(头插）
    extern void insertEdgeHead(GraphLink *g, T v1, T v2, string bus[20], int busTime, int walk, int walkTime);

    //删除边
    extern void removeEdge(GraphLink *g, T v1, T v2);

    //删除顶点
    extern void removeVertex(GraphLink *g, T v);

    //清空图
    extern void destroyGraphLink(GraphLink *g);

    //获取两点之间最短路径：算法
    extern void floyd(GraphLink *g);

    // dataInfo主文件

    //初始化数据
    extern void run();

    //获取程序的内存使用
    extern void GetProcessMemory();

    //解析siteinfo文件

    //解析所有站点
    extern void parseAllSite(GraphLink *g);

    //解析所有站与站之间的关系
    extern void parseSite(GraphLink *g);
}
#endif