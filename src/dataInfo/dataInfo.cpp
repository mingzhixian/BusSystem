#include "../main/busSystem.h"
namespace datainfo
{
	//新建图
	GraphLink site;
	void run()
	{
		//初始化图
		initGraphLink(&site);
		//解析站点，并作为顶点插入图
		parseAllSite(&site);
		//解析所有站点之间的信息，并作为边插入图
		parseSite(&site);
		//测试用--显示图
		//showGraphLink(&site);
	}
}
