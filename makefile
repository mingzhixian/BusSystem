busSystem: start main http run over
	
#编译开始前操作	
start:
	mkdir -p ./out/tmp
	p=`pwd` && n=$${p//\//\\\/} && sed -i "s/needToSed/$$n/" ./src/dataInfo/parseSiteInfo.cpp

#编译整个项目
main:dataInfo.o graph.o parseSiteInfo.o main.o http.o hash.o
	g++ ./out/tmp/*.o -o ./out/busSystem

#运行程序
run:
	./out/busSystem

#建立图
dataInfo.o:
	g++ -c ./src/dataInfo/dataInfo.cpp -o ./out/tmp/dataInfo.o

#图相关操作集
graph.o:
	g++ -c ./src/dataInfo/graph.cpp -o ./out/tmp/graph.o

#解析信息文件工具
parseSiteInfo.o:
	g++ -c ./src/siteInfo/parseSiteInfo.cpp -o ./out/tmp/parseSiteInfo.o

#http服务器（fastCgi）
http.o:
	g++ -c ./http/http.cpp -o ./out/tmp/http.o

#缓存工具(哈希表)
hash.o:
	g++ -c ./cache/hash.cpp -o ./out/tmp/hash.o

#主程序
main.o:
	g++ -c ./src/main/main.cpp -o ./out/tmp/main.o

#编译完成后操作
over:
	p=`pwd` && n=$${p//\//\\\/} && sed -i "s/$$n/needToSed/" ./src/dataInfo/parseSiteInfo.cpp

#清理中间文件
clean:
	rm -rf ./out