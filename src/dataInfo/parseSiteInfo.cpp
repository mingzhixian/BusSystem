#include "../main/busSystem.h"
namespace datainfo
{
	FILE *f = fopen("./siteInfo/siteinfo.txt", "r");
	//获取所有站点
	void parseAllSite(GraphLink *g)
	{
		int i = 0;
		//存取每个站点名
		char siteName[40];
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
	}
	//获取站点之间的公交信息
	void parseSite(GraphLink *g)
	{
		char tmp = ' ';
		char luName[40];
		//读取换行符，使指针移动至站点与站点之间信息的位置
		fscanf(f, "%c", &tmp);
		while (true)
		{
			//读取每一路开头的换行符
			fscanf(f, "%c", &tmp);
			//判断文件读取完成
			if (tmp == EOF)
			{
				return;
			}
			//读取公交的名字
			fscanf(f, "%s", luName);
			//读取公交名字后面换行符
			fscanf(f, "%c", &tmp);
			while (true)
			{
			}
			//读取每一路结尾的换行符
			fscanf(f, "%c", &tmp);
		}
		fclose(f);
	}
}