#include "dataInfo.h"
using namespace dataInfo;
#include "http.h"
using namespace http;

int main(int argc, char const *argv[])
{
	//建立图
	dataInfoRun();
	//启动fastCgi监听
	httpRun();
	return 0;
}
