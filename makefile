busSystem:out main.o dataInfo.o
	gcc ./out/src/*.o -o busSystem

out:
	mkdir -p ./out/src

main.o:src/main/busSystem.h src/main/main.cpp
	gcc -c main.c -o ./out/src/main.o

dataInfo.o:src/dataInfo/*.cpp src/main/busSystem.h
	gcc -c dataInfo.cpp -o ./out/src/dataInfo.o

clean:
	rm -rf ./out