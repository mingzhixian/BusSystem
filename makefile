busSystem: start main http run over
	
start:
	mkdir -p ./out/tmp
	p=`pwd` && n=$${p//\//\\\/} && sed -i "s/needToSed/$$n/" ./src/dataInfo/parseSiteInfo.cpp

main:dataInfo.o graph.o parseSiteInfo.o main.o http.o
	g++ ./out/tmp/*.o -o ./out/busSystem

run:
	./out/busSystem

dataInfo.o:
	g++ -c ./src/dataInfo/dataInfo.cpp -o ./out/tmp/dataInfo.o

graph.o:
	g++ -c ./src/dataInfo/graph.cpp -o ./out/tmp/graph.o

parseSiteInfo.o:
	g++ -c ./src/dataInfo/parseSiteInfo.cpp -o ./out/tmp/parseSiteInfo.o

main.o:
	g++ -c ./src/main/main.cpp -o ./out/tmp/main.o

http.o:
	g++ -c ./http/http.cpp -o ./out/tmp/http.o

over:
	p=`pwd` && n=$${p//\//\\\/} && sed -i "s/$$n/needToSed/" ./src/dataInfo/parseSiteInfo.cpp

clean:
	rm -rf ./out