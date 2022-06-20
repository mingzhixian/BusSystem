HEADER=./src/header
SOURCE=./src
OUT=./out
TMP=./out/tmp
CC=g++

busSystem: start link over
	
#编译开始前操作	
start:
	mkdir -p $(TMP)
	p=`pwd` && n=$${p//\//\\\/} && sed -i "s/needToSed/$$n/" $(SOURCE)/siteInfo/parseSiteInfo.cpp

#连接
link:compile
	$(CC) $(TMP)/*.o -o $(OUT)/busSystem

#编译
CPP=$(wildcard $(SOURCE)/*/*.cpp)
O=$(patsubst %.cpp,%.o,$(notdir $(CPP)))
CODE=$(CC) -c -I $(HEADER) $(i) -o $(TMP)/$(patsubst %.cpp,%.o,$(notdir $(i)));
compile:
	$(foreach i ,$(CPP), $(CODE))
	
#编译完成后操作
over:
	p=`pwd` && n=$${p//\//\\\/} && sed -i "s/$$n/needToSed/" $(SOURCE)/siteInfo/parseSiteInfo.cpp

#运行程序
run:busSystem 
	$(OUT)/busSystem

#运行测试用用户端软件
testUsr:compileTestUsr
	$(OUT)/testUsr

compileTestUsr:
	$(CC) -o $(OUT)/testUsr ./testUsr/testUsr.cpp 

#清理中间文件
clean:
	rm -rf $(TMP)
