#include "public.h"
#include "dataInfo.h"
using namespace dataInfo;
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <csignal>
#include <fstream>
#include <thread>

#ifndef _BUS_DAEMON
#define _BUS_DAEMON
namespace busDaemon
{
	//运行守护进程
	extern void daemonRun(GraphLink *site, Hash *cache);
	//处理信号
	extern void daemonHandler();
	//解析处理请求并返回结果
	extern void handleRequest(char *req);
};
#endif