#include "public.h"

#ifndef _DATA_INFO
#define _DATA_INFO
namespace dataInfo
{
    //节点结构
    class T
    {
    public:
        string name = "";
        //重载相等操作符
        bool operator==(const T &obj)
        {
            return (name == obj.name);
        }
    };

    //边的结构
    class Edge
    {
    public:
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
        Edge *link;
    };

    //顶点的结构
    class Vertex
    {
    public:
        //顶点的值
        T data;
        //边
        Edge *adj;
    };

    //图的结构
    class GraphLink
    {
    private:
        //最大节点数目
        int MaxVertices;
        //目前节点数目
        int NumVertices;
        //边的数目
        int NumEdges;
        //顶点的链表
        Vertex *nodeTable;

        //创建边，传入顶点的边链和新边参数，服务于insertEdgeTail函数
        void createEdgeTail(Edge **e, int idx, string bus[20], int busTime, int walk, int walkTime);

        //创建边，传入顶点的边链和新边参数，服务于insertEdgeHead函数
        void createEdgeHead(Edge **e, int p1, int p2, string bus[20], int busTime, int walk, int walkTime);

        //获取边
        Edge *getEdge(T v1, T v2);

        //模式选择，服务于最短路径算法
        inline int minTime(int busTime, int walkTime, int mode);

        // dijkstra算法，服务于getShortest
        string *dijkstra(T v1, int mode);

    public:
        //初始化图
        GraphLink();

        //显示图
        void showGraphLink();

        //插入顶点
        void insertVertex(T v);

        //查找顶点在顶点链表的下标
        int getVertexIndex(T v);

        //插入边关系(尾插）
        void insertEdgeTail(T v1, T v2, string bus[20], int busTime, int walk, int walkTime);

        //插入边关系(头插）
        void insertEdgeHead(T v1, T v2, string bus[20], int busTime, int walk, int walkTime);

        //更新边关系
        void setEdgeWalk(T v1, T v2, int walk, int walkTime);

        //删除边
        void removeEdge(T v1, T v2);

        //删除顶点
        void removeVertex(T v);

        //获取两点之间最短路径
        string getShortest(T v1, T v2, int mode);
        //清空图
        ~GraphLink();
    };

    //初始化数据,用于建立图
    extern void dataInfoRun();

    //获取程序的内存使用
    extern void GetProcessMemory();

    //堆
}
#endif