#include "../main/busSystem.h"
namespace datainfo
{
	void text()
	{
		string allSite[300];
		parseAllSite(allSite);
		int i=0;
		while (allSite[i]!="\0")
		{
			cout << allSite[i] << endl;
		}
	}
}
