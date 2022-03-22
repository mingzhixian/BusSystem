# 重庆公交线路换乘推荐系统
## 目的
根据用户所在站和目的站会自动寻找最节省时间、步行最少、换乘最少的方案。
## 部署
1. 根据实际情况修改siteInfo中的站点信息（格式参考siteInfo/rule.md）
2. 编译软件(如未进行第一步可直接进入第三步，无需编译)
3. 运行软件
	- 参数说明:
	- p：http端口号，默认8090
	- 
## 使用
项目默认使用http网页访问提供信息。
- 访问数据格式：{"source":"西南大学站","purpose":"解放碑站","model":"1"}</br>
	model:1--最节省时间、2--步行最少、3--换乘最少
- 返回数据格式：{"route":"4(西南大学站-红旗河沟站)-8(红旗河沟站-解放碑站)","meter":"400","transfer":"1"}
## 项目结构
.                               			&emsp;BusSystem<br>
├── lib  									&emsp;外部包引入<br>
├── README.md 								&emsp;说明文件<br>
└── src 									&emsp;<br>
&emsp;&emsp;&emsp;├── dataInfo 				&emsp;程序内部信息存储<br>
&emsp;&emsp;&emsp;├── http 					&emsp;http服务器<br>
&emsp;&emsp;&emsp;├── main					&emsp;主函数<br>
&emsp;&emsp;&emsp;├── pathCalculate			&emsp;路径计算<br>
&emsp;&emsp;&emsp;└── siteInfo				&emsp;站点信息<br>
## 项目说明
### 数据存储
