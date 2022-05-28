#include "dataInfo.h"
#include "siteInfo.h"
using namespace siteInfo;
namespace dataInfo
{
	//新建图
	GraphLink site;
	//运行
	void dataInfoRun()
	{
		//解析文件信息
		parse(&site);

		//测试用--显示图
		site.showGraphLink();

		//清空图--在linux下效果不会明显显示，因为数据量较小，系统不会真正释放，具体参见https://blog.csdn.net/weixin_30819085/article/details/101325304
		//site.~GraphLink();
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
