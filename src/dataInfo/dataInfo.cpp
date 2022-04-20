#include "../main/busSystem.h"
#include <unistd.h>
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
		// showGraphLink(&site);
		
		//清空图--在linux下效果不会明显显示，因为数据量较小，系统不会真正释放，具体参见https://blog.csdn.net/weixin_30819085/article/details/101325304
		destroyGraphLink(&site);
	}

	//获取程序的内存使用
	void GetProcessMemory()
	{
		FILE *file = fopen("/proc/self/status", "r");
		char line[256];
		while (fgets(line, 256, file) != NULL)
		{
			if (strncmp(line, "VmSize:", 7) == 0)
			{
				cout << line;
				break;
			}
			else if (strncmp(line, "VmRSS:", 6) == 0)
			{
				cout << line;
				break;
			}
		}
		fclose(file);
	}
}
