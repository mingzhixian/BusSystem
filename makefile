busSystem: start main http run over
	
start:
	mkdir -p ./out/tmp/src
	mkdir -p ./out/tmp/http
	p=`pwd` && n=$${p//\//\\\/} && sed -i "s/needToSed/$$n/" ./src/dataInfo/parseSiteInfo.cpp

main:dataInfo.o graph.o parseSiteInfo.o main.o
	g++ ./out/tmp/src/*.o -o ./out/busSystem

http:http.o
	g++ ./out/tmp/http/*.o -o ./out/http

run:
	./out/busSystem
	./out/http

dataInfo.o:
	g++ -c ./src/dataInfo/dataInfo.cpp -o ./out/tmp/src/dataInfo.o

graph.o:
	g++ -c ./src/dataInfo/graph.cpp -o ./out/tmp/src/graph.o

parseSiteInfo.o:
	g++ -c ./src/dataInfo/parseSiteInfo.cpp -o ./out/tmp/src/parseSiteInfo.o

main.o:
	g++ -c ./src/main/main.cpp -o ./out/tmp/src/main.o

http.o:
	g++ -c ./http/http.cpp -o ./out/tmp/http/http.o

over:
	p=`pwd` && n=$${p//\//\\\/} && sed -i "s/$$n/needToSed/" ./src/dataInfo/parseSiteInfo.cpp

clean:
	rm -rf ./out