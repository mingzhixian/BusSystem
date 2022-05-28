#include "public.h"
#include "dataInfo.h"
#include <fstream>
using namespace dataInfo;
#ifndef _SITE_INFO
#define _SITE_INFO
namespace siteInfo
{
	//解析
	extern void parse(GraphLink *g);

	//解析所有站点
	extern void parseAllSite(GraphLink *g);

	//解析所有站与站之间的关系
	extern void parseSite(GraphLink *g);

	//解析步行信息
	extern void parseWalk(GraphLink *g);
};
#endif