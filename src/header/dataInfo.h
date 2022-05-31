#include "public.h"

#ifndef _DATAINFO
#define _DATAINFO
namespace dataInfo
{
    class Hash;
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
        string *dijkstra(T v1, int mode, Hash *cache);

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
        string getShortest(T v1, T v2, int mode, Hash *cache);
        //清空图
        ~GraphLink();
    };

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
        //哈希散列算法
        int hashFunction(T v1, T v2);

    public:
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

    //堆
    class Heap
    {
    private:
        int **data; //数组，用于存放数据
        int num;    //堆里面的元素数量

        //交换值
        inline void swap(int i, int j);
        //判断大小-小根堆
        inline bool prior(int *a, int *b);
        //向下递归
        void siftDown(int pos);
        //上溯
        void siftUp(int pos);
        //判断是否为叶节点
        inline bool isLeaf(int pos);
        //返回左节点
        inline int leftchild(int pos);
        //返回右节点
        inline int rightchild(int pos);
        //返回父节点
        inline int parent(int pos);

    public:
        //构造函数
        Heap(const int h[], int n);
        //返回堆的大小
        int size() const;
        //移除根节点
        int *removeFirst();
        //打印
        void print();
    };

}
#endif