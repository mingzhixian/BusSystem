HEADER=./src/header
SOURCE=./src
OUT=./out
TMP=./out/tmp

busSystem: start main over
	
#编译开始前操作	
start:
	mkdir -p $(TMP)
	p=`pwd` && n=$${p//\//\\\/} && sed -i "s/needToSed/$$n/" $(SOURCE)/siteInfo/parseSiteInfo.cpp

#编译整个项目
main:dataInfo.o graph.o parseSiteInfo.o main.o http.o hash.o
	g++ $(TMP)/*.o -o $(OUT)/busSystem

#运行程序
run:busSystem 
	$(OUT)/busSystem

#建立图
dataInfo.o:
	g++ -c -I $(HEADER) $(SOURCE)/dataInfo/dataInfo.cpp -o $(TMP)/dataInfo.o

#图相关操作集
graph.o:
	g++ -c -I $(HEADER) $(SOURCE)/dataInfo/graph.cpp -o $(TMP)/graph.o

#解析信息文件工具
parseSiteInfo.o:
	g++ -c -I $(HEADER) $(SOURCE)/siteInfo/parseSiteInfo.cpp -o $(TMP)/parseSiteInfo.o

#http服务器（fastCgi）
http.o:
	g++ -c -I $(HEADER) $(SOURCE)/http/http.cpp -o $(TMP)/http.o

#缓存工具(哈希表)
hash.o:
	g++ -c -I $(HEADER) $(SOURCE)/cache/hash.cpp -o $(TMP)/hash.o

#主程序
main.o:
	g++ -c -I $(HEADER) $(SOURCE)/main/main.cpp -o $(TMP)/main.o

#编译完成后操作
over:
	p=`pwd` && n=$${p//\//\\\/} && sed -i "s/$$n/needToSed/" $(SOURCE)/siteInfo/parseSiteInfo.cpp

#清理中间文件
clean:
	rm -rf $(TMP)