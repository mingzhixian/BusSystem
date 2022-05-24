#include "busSystem.h"
using namespace busSystem;

int main(int argc, char const *argv[])
{
	//建立图
	dataInfo();
	//启动fastCgi监听
	http();
	return 0;
}
