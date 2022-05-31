#include "dataInfo.h"
using namespace dataInfo;
#include "siteInfo.h"
using namespace siteInfo;
#include "daemon.h"
using namespace busDaemon;

int main(int argc, char const *argv[])
{
	//新建图
	GraphLink site;

	//新建缓存
	Hash cache;

	//解析文件信息
	parse(&site);

	//测试用--显示图
	// site.showGraphLink();

	//启动后台守护进程
	daemonRun(&site, &cache);
	return 0;
}
