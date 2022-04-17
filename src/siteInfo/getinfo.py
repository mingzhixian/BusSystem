import time
import urllib.request
from bs4 import BeautifulSoup
import random
import ssl

ssl._create_default_https_context = ssl._create_unverified_context
url = "https://bus.mapbar.com/chongqing/xianlu/"
urllist = ["502lu", "505lu", "506lu", "507lu", "508lu", "515lu", "518lu", "521lu", "521luhuanxian", "522lu", "533lu", "551lu", "555lu", "556lu", "558lu", "560lu", "562lu",
           "563lu", "566ludazhan", "570lu", "581lu", "585lu", "588lu", "589lu", "591lu", "592lu", "595lu", "598lu", "598luqujian", "beiqiyinxiangqichegongsitongqinche", "557lu"]
allSite=[]
siteInfo=""
print("请耐心等待！")
for lu in urllist:
    print(lu)
    siteInfo+=("\n"+lu+"\n")
    request = urllib.request.Request(url + lu)
    request.add_header(
        "user-agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.88 Safari/537.36")
    request.verify = False
    response2 = urllib.request.urlopen(request)

    soup = BeautifulSoup(response2.read(), "html.parser",
                         from_encoding="utf-8")
    lis = soup.select("#scrollTr")[0].find_all('li')
    for li in lis:
        if li.select("em")[0].get_text() not in allSite:
            allSite.append(li.select("em")[0].get_text())
        siteInfo+=(li.select("em")[0].get_text() +
                   " <-"+str(random.randint(10, 45))+"-> ")
    siteInfo+=("\n")
    time.sleep(5)
file = open("./siteinfo.txt", 'w')
for site in allSite:
    file.write(site+"  ")
file.write("\n\n")
file.write(siteInfo)
print("完成！")
