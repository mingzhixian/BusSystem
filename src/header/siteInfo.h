#include "public.h"
#include "dataInfo.h"
using namespace dataInfo;
#ifndef _SITE_INFO
#define _SITE_INFO
namespace sitInfo
{
	//解析所有站点
	extern void parseAllSite(GraphLink *g);

	//解析所有站与站之间的关系
	extern void parseSite(GraphLink *g);
};
#endif