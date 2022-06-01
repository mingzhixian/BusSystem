#include <iostream>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <csignal>
using namespace std;

void t()
{
	char fifo[] = "/tmp/BusSystemFifoIn";
	//判断fifo文件是否存在
	int ret = access(fifo, F_OK);
	//若fifo不存在就创建fifo
	if (ret == -1)
	{
		cout << "创建管道" << endl;
		int r = mkfifo(fifo, 0664);
		//判断文件是否创建成功
		if (r == -1)
		{
			perror("创建管道失败");
			exit(1);
		}
	}
	//打开文件
	int fd = open(fifo, O_WRONLY);
	cout << "打开管道" << endl;
	if (fd == -1)
	{
		perror("打开管道失败");
		exit(1);
	}
	//写入fifo中的数据
	cout << "写入1" << endl;
	char req1[10000] = "{\"id\":\"1\",\"source\":\"中渡口站\",\"purpose\":\"罗马假日站\",\"mode\":\"1\"}";
	write(fd, req1, 10000);
	cout << "写入2" << endl;
	char req2[10000] = "{\"id\":\"2\",\"source\":\"钢材市场站\",\"purpose\":\"龙井湾站\",\"mode\":\"1\"}";
	write(fd, req2, 10000);
	cout << "写入3" << endl;
	char req3[10000] = "{\"id\":\"3\",\"source\":\"大庙站\",\"purpose\":\"华新街站\",\"mode\":\"1\"}";
	write(fd, req3, 10000);
	cout << "写入完成" << endl;
	close(fd);
}

void o()
{
	char fifo[] = "/tmp/BusSystemFifoOut";
	//判断fifo文件是否存在
	int ret = access(fifo, F_OK);
	//若fifo不存在就创建fifo
	if (ret == -1)
	{
		cout << "创建管道" << endl;
		int r = mkfifo(fifo, 0664);
		//判断文件是否创建成功
		if (r == -1)
		{
			perror("创建管道失败");
			exit(1);
		}
	}
	//打开文件
	int fd = open(fifo, O_RDWR);
	cout << "打开管道" << endl;
	if (fd == -1)
	{
		perror("打开管道失败");
		exit(1);
	}
	char answer[10000];
	for (int i = 0; i < 3; i++)
	{
		read(fd, answer, 10000);
		cout << answer << endl;
	}
	close(fd);
}

int main(int argc, char const *argv[])
{
	t();
	sleep(2);
	o();
	return 0;
}
