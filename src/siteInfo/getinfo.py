import time
import urllib.request
from bs4 import BeautifulSoup
import random
import ssl

ssl._create_default_https_context = ssl._create_unverified_context
url = "https://bus.mapbar.com/chongqing/xianlu/"
buslist = {}
allSite = ["as","bs","cs"]
siteInfo = ""
print("请耐心等待！")
# 爬取公交名称
request = urllib.request.Request(url)
request.add_header(
    "user-agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.88 Safari/537.36")
request.verify = False
response2 = urllib.request.urlopen(request)
soup = BeautifulSoup(response2.read(), "html.parser",
                     from_encoding="utf-8")

for i in range(3):
    lis = soup.select(".ChinaTxt")[i].select("dd")[0].find_all("a")
    for li in lis:
        buslist[li.get_text()]=li.attrs['href']
# 查找公交线路
for lu in buslist.keys():
    # 打印提示
    print(lu)
    siteInfo += ("\n"+lu+"\n")
    request = urllib.request.Request(buslist[lu])
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
        bustime = random.randint(10, 45)
        siteInfo += (li.select("em")[0].get_text() +
                     " <- "+str(bustime)+" -> ")
    siteInfo += ("\n")
    time.sleep(3)

# 步行
walkinfo = ""
for x in range(80):
    a = random.randint(0, len(allSite)-1)
    b = random.randint(0, len(allSite)-1)
    walk = random.randint(40, 500)
    walkinfo += "< "+allSite[a]+" - "+str(walk)+" - "+allSite[b]+" >"

file = open("./siteinfo.txt", 'w')
for site in allSite:
    file.write(site+"  ")
file.write("\n\n")
file.write(siteInfo)
file.write("\n\n")
file.write(walkinfo)
file.write("\n\n")
print("完成！")
