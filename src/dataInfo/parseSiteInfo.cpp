#include "../main/busSystem.h"
namespace datainfo
{
	//获取所有站点
	void parseAllSite(GraphLink *g)
	{
		int i = 0;
		FILE *f = fopen("./siteInfo/siteinfo.txt", "r");
		//存取每个站点名
		char siteName[24];
		char tmp = ' ';
		T *p = (T *)malloc(sizeof(T));
		while (true)
		{
			//读取站名，遇到空格结束
			fscanf(f, "%s", siteName);
			//存取站名
			p->name = siteName;
			//插入图中
			insertVertex(g, *p);
			//读取空格
			fscanf(f, "%c%c%c", &tmp, &tmp, &tmp);
			//结束标志
			if (tmp == '\n')
				break;
			else
				//文件读取指针后退一步
				fseek(f, -1, SEEK_CUR);
		}
		free(p);
		fclose(f);
	}
	//获取站点之间的公交信息
	void parseSite(GraphLink *g)
	{
	}

}