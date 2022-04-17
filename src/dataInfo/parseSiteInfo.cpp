#include "../main/busSystem.h"
namespace datainfo
{
	//获取所有站点
	void parseAllSite(string* allSite)
	{
		int i = 0;
		FILE *f = fopen("siteinfo.txt", "r");
		char siteName[20];
		cout << f << endl;
		fscanf(f, "%s", siteName);
		/* while (true)
		{
			//读取站名，遇到空格结束
			fscanf(f, "%s", siteName);
			cout << "11"<<endl;
			//结束标志
			if (siteName == "\n")
				break;
			allSite[i++] = siteName;
			//读取空格
			fscanf(f, "%2c", string(siteName));
		} */
		fclose(f);
	}
	//获取站点之间的公交信息
	void  parseSite()
	{
	}

}