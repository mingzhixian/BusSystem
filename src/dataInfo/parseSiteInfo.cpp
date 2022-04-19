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
			fscanf(f, "%c%c%c", &tmp, &tmp, &tmp);
			//存取站名
			p->name = siteName;
			//插入图中
			insertVertex(g, *p);
			//结束标志
			if (tmp == '\n')
				break;
			else
				//文件读取指针后退一步
				fseek(f, -1, SEEK_CUR);
		}
		//读取换行符，使指针移动至站点与站点之间信息的位置,在第一行所有站点后有两个换行符
		fscanf(f, "%c", &tmp);
		free(p);
	}
	//获取站点之间的公交信息
	void parseSite(GraphLink *g)
	{
		char tmp = ' ';
		string bus[20];
		int bustime, walk, walktime;
		T v1, v2;
		while (true)
		{
			char luName[100] = {0}, site1[100] = {0}, site2[100] = {0};
			//读取每一路开头的换行符
			tmp=fgetc(f);
			//判断文件读取完成
			if (tmp == EOF)
			{
				return;
			}
			//读取公交的名字和换行符
			fscanf(f, "%s%c", luName, &tmp);
			bus[0] = luName;
			while (true)
			{
				if (strlen(site2) == 0)
				{
					fscanf(f, "%s <- bustime:%d walk:%d walktime:%d -> %s", site1, &bustime, &walk, &walktime, site2);
				}
				else
				{
					strcpy(site1, site2);
					fscanf(f, " <- bustime:%d walk:%d walktime:%d ->%c%c", &bustime, &walk, &walktime, &tmp, &tmp);
					if (tmp != '\n')
					{
						//文件读取指针后退一步
						fseek(f, -1, SEEK_CUR);
						fscanf(f, "%s", site2);
					}
					else
					{
						memset(site2, 0, 40);
					}
				}
				if (strlen(site2) == 0)
				{
					break;
				}
				v1.name = string(site1);
				v2.name = string(site2);
				insertEdgeHead(g, v1, v2, bus, bustime, walk, walktime);
			}
		}
		fclose(f);
	}
}