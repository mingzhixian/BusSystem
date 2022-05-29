#include "dataInfo.h"
using namespace dataInfo;
#include "siteInfo.h"
using namespace siteInfo;
#include "http.h"
using namespace http;

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

	T v1, v2;
	v1.name = "D";
	v2.name = "B";
	cout << site.getShortest(v1, v2, 1, &cache) << endl;
	cout << cache.findItem(v1, v2).route[1] << endl;
	//清空图--在linux下效果不会明显显示，因为数据量较小，系统不会真正释放，具体参见https://blog.csdn.net/weixin_30819085/article/details/101325304
	site.~GraphLink();

	//启动fastCgi监听
	httpRun();
	return 0;
}
