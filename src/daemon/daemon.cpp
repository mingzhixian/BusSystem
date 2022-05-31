#include "daemon.h"
namespace busDaemon
{
	GraphLink *site;
	Hash *cache;
	int fdIn;
	int fdOut;

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
		char fifoIn[] = "/tmp/BusSystemFifoIn";
		char fifoOut[] = "/tmp/BusSystemFifoOut";
		//判断fifo文件是否存在
		int ret1 = access(fifoIn, F_OK);
		int ret2 = access(fifoOut, F_OK);
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
		//打开文件
		fdIn = open(fifoIn, O_RDWR);
		fdOut = open(fifoOut, O_WRONLY);
		if (fdIn == -1)
		{
			perror("打开管道失败");
			exit(1);
		}
		if (fdOut == -1)
		{
			perror("打开管道失败");
			exit(1);
		}
		//不断读取fifo中的数据
		while (true)
		{
			char req[300];
			read(fdIn, req, 300);
			//新开线程处理请求
			handleRequest(req);
			// thread tmpThread(handleRequest, req);
		}
	}

	string handleRequest(char *req)
	{
		char tmp1[1000];
		strcpy(tmp1, req);
		write(fdOut, tmp1, 1000);
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
		char tmpAnswer2[1000];
		strcpy(tmpAnswer2, tmpAnswer1.c_str());
		//添加id信息，用于客户端区分不同请求的答案
		sscanf(tmpAnswer2, "{%s", tmpAnswer2);
		char answer[1000] = "{\"id\":\"";
		strcat(answer, tmpId);
		strcat(answer, "\",");
		strcat(answer, tmpAnswer2);
		write(fdOut, answer, 1000);
	}
}