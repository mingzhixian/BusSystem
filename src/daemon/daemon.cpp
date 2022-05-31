#include "daemon.h"
namespace busDaemon
{
	GraphLink *site;
	Hash *cache;

	void daemonRun(GraphLink *s, Hash *c)
	{
		//全局化常用参数
		site = s;
		cache = c;
		//启动守护进程，关闭主进程
		pid_t pid = -1;
		//创建子进程
		pid = fork();
		if (-1 == pid)
		{
			perror("创建守护进程失败！");
			exit(1);
		}
		//父进程退出
		if (pid > 0)
		{
			exit(0);
		}
		//创建新会话
		pid = setsid();
		if (-1 == pid)
		{
			perror("守护进程创建新会话失败");
		}
		//改变当前工作目录
		int ret = -1;
		ret = chdir("/");
		if (-1 == ret)
		{
			perror("守护进程更改目录失败");
		}
		//设置权限掩码
		umask(0);
		//关闭文件描述符
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);

		//打开监听信号程序
		daemonHandler();
	}

	void daemonHandler()
	{
		//建立读取管道
		char fifoIn[] = "/tmp/BusSystemFifoIn";
		//判断fifo文件是否存在
		int ret1 = access(fifoIn, F_OK);
		//若fifo不存在就创建fifo
		if (ret1 == -1)
		{
			int r = mkfifo(fifoIn, 0664);
			//判断文件是否创建成功
			if (r == -1)
			{
				perror("创建管道失败");
				exit(1);
			}
		}
		//打开文件
		int fdIn = open(fifoIn, O_RDWR);
		if (fdIn == -1)
		{
			perror("打开管道失败");
			exit(1);
		}
		//不断读取fifo中的数据
		char *req;
		while (true)
		{
			//新开线程处理请求
			req = new char[10000];
			memset(req, 0, 10000);
			read(fdIn, req, 10000);
			thread tmpThread(handleRequest, req);
			tmpThread.detach();
		}
	}
	
	void handleRequest(char *req)
	{
		//解析请求
		const char *rule = "{\"id\":\"%[^\"]\",\"source\":\"%[^\"]\",\"purpose\":\"%[^\"]\",\"mode\":\"%[^\"]\"}";
		char source[100];
		char purpose[100];
		char tmpId[2];
		char tmpMode[2];
		sscanf(req, rule, tmpId, source, purpose, tmpMode);
		int mode = tmpMode[0] - '0';
		//生成节点
		T v1, v2;
		v1.name = source;
		v2.name = purpose;
		//从缓存中读取
		string tmpAnswer1 = cache->findItem(v1, v2).route[mode];
		//如果缓存中没有则计算
		if (tmpAnswer1.length() == 0)
		{
			tmpAnswer1 = site->getShortest(v1, v2, mode, cache);
		}
		//转换为char数组
		char tmpAnswer2[10000];
		strcpy(tmpAnswer2, tmpAnswer1.c_str());
		//添加id信息，用于客户端区分不同请求的答案
		sscanf(tmpAnswer2, "{%s", tmpAnswer2);
		char answer[10000] = "{\"id\":\"";
		strcat(answer, tmpId);
		strcat(answer, "\",");
		strcat(answer, tmpAnswer2);
		//打开管道
		char fifoOut[] = "/tmp/BusSystemFifoOut";
		int ret2 = access(fifoOut, F_OK);
		if (ret2 == -1)
		{
			int r = mkfifo(fifoOut, 0664);
			//判断文件是否创建成功
			if (r == -1)
			{
				perror("创建管道失败");
				exit(1);
			}
		}
		int fdOut = open(fifoOut, O_WRONLY);
		if (fdOut == -1)
		{
			perror("打开管道失败");
			exit(1);
		}
		delete req;
		write(fdOut, answer, 10000);
	}
}