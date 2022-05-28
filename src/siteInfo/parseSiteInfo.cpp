#include "siteInfo.h"
namespace siteInfo
{
	FILE *f = fopen("needToSed/src/siteInfo/siteinfo.txt", "r");
	void parse(GraphLink *g)
	{
		char tmp;
		//获取所有站点
		parseAllSite(g);
		//读取换行符
		fscanf(f, "%c%c", &tmp, &tmp);
		//获取站点之间的公交信息
		parseSite(g);
		//读取换行符
		fscanf(f, "%c%c", &tmp, &tmp);
		//获取站点之间走路信息
		// parseWalk(g);
		//关闭f
		fclose(f);
	}

	void parseAllSite(GraphLink *g)
	{
		int i = 0;
		//存取每个站点名
		char siteName[80];
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
			g->insertVertex(*p);
			//结束标志
			if (tmp == '\n')
			{
				//文件读取指针后退一步
				fseek(f, -1, SEEK_CUR);
				break;
			}
			else
			{
				//文件读取指针后退一步
				fseek(f, -1, SEEK_CUR);
			}
		}
		free(p);
	}

	void parseSite(GraphLink *g)
	{
		char tmp = ' ';
		string bus[20];
		int bustime, walk = 10000, walktime = 10000;
		T v1, v2;
		while (true)
		{
			char luName[100] = {0}, site1[100] = {0}, site2[100] = {0};
			//读取每一路开头的换行符
			tmp = fgetc(f);
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
				//第一次读取
				if (strlen(site2) == 0)
				{
					fscanf(f, "%s <- %d -> %s", site1, &bustime, site2);
				}
				//之后的读取
				else
				{
					strcpy(site1, site2);
					fscanf(f, " <- %d ->%c%c", &bustime, &tmp, &tmp);
					if (tmp != '\n')
					{
						//文件读取指针后退一步
						fseek(f, -1, SEEK_CUR);
						fscanf(f, "%s", site2);
					}
					else
					{
						//如果是最后一个则将site2置空
						memset(site2, 0, 40);
					}
				}
				if (strlen(site2) == 0)
				{
					break;
				}
				v1.name = string(site1);
				v2.name = string(site2);
				g->insertEdgeHead(v1, v2, bus, bustime, walk, walktime);
			}
		}
	}

	void parseWalk(GraphLink *g)
	{
		T v1, v2;
		int walk;
		while (true)
		{
			char site1[100] = {0}, site2[100] = {0}, tmp = 0;
			fscanf(f, "%c", &tmp);
			//结束标志
			if (tmp == '\n')
			{
				break;
			}
			else
			{
				fseek(f, -1, SEEK_CUR);
				fscanf(f, "< %s - %d - %s >", site1, walk, site2);
				v1.name = string(site1);
				v2.name = string(site2);
				g->setEdgeWalk(v1, v2, walk, (int)(walk / 1.2 / 60));
			}
		}
	}
}