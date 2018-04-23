// testcppjson.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "json\value.h"
#include "json\reader.h"
#include "json\writer.h"
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
using namespace Json;

//节点信息，保存在节点/Server/Server-x/Online的信息，信息是json，需要转化成字符串才可以保存到zookeeper中去
typedef struct tag_OnlineNodeData {
	int m_iStatus;                 //当前服务器的状态
	int m_iIrisNum;                //当前服务器的虹膜数量
	int m_iDataVersion;            //当前服务器数据库数据的版本
	std::string m_strIP;           //thrfit服务对应的ip地址
	int m_iPort;                   //thrift服务对应的端口
	int m_iBestConNum;             //根据机器属性等配置的最佳连接数量
	std::string m_strName;         //节点名称
	std::string m_strPath;         //路径(没有加上节点名称，节点名称需要自行增加)
}OnlineNodeData;

//https://github.com/QilimiWxu/JsoncppTest.git
//https://github.com/QilimiWxu/JsoncppTest.git
//  jsoncpp 博客  https://www.cnblogs.com/esCharacter/p/7657676.html
//                https://blog.csdn.net/yc461515457/article/details/52749575
int main()
{
	Json::Value jsonRoot;//定义一个根目录
	Json::Value jsonItem;//定义一个子对象
	int i = 0;
	//jsonItem["item1"] = "one";//添加数据
	//jsonItem["item2"] = 2;//添加数据

	//jsonRoot.append(jsonItem);

	//std::string jsonTsr1= jsonRoot.toStyledString();

	//jsonItem.clear();//清除jsonItem

	jsonItem["m_iStatus"] = 0;
	jsonItem["m_iIrisNum"] = 0;
	jsonItem["m_iDataVersion"] = 1;
	jsonItem["m_strIP"] = "127.0.0.1";
	jsonItem["m_iPort"] = 9906;
	jsonItem["m_iBestConNum"] = 20;
	jsonItem["m_strName"] = "Server-2";
	jsonItem["m_strPath"] = "/Server";
	jsonRoot["OnlineNodeData"] = jsonItem;

	std:;string jsonTsr2 = jsonRoot.toStyledString();

	OnlineNodeData data;
	Json::Value jsonRoot1;//定义一个根目录
	Json::Value jsonItem1;//定义一个子对象

	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;

	JSONCPP_STRING errs;

	Json::CharReader* reader = builder.newCharReader();

	if (!reader->parse(jsonTsr2.data(), jsonTsr2.data() + 
		jsonTsr2.size(), &jsonRoot, &errs)) //从jsonStr中读取数据到jsonRoot
	{
		if (!jsonRoot["OnlineNodeData"].isNull()) {
			jsonItem1 = jsonRoot["OnlineNodeData"];
			data.m_iStatus = jsonItem1["m_iStatus"].asInt();
			data.m_iIrisNum = jsonItem1["m_iIrisNum"].asInt();
			data.m_iDataVersion = jsonItem1["m_iDataVersion"].asInt();
			data.m_strIP = jsonItem1["m_strIP"].asString();
			data.m_iPort = jsonItem1["m_iPort"].asInt();
			data.m_iBestConNum = jsonItem1["m_iBestConNum"].asInt();
			data.m_strName = jsonItem1["m_strName"].asString();
			data.m_strPath = jsonItem1["m_strPath"].asString();
		}
		return 1;
	}
	if (!jsonRoot["OnlineNodeData"].isNull()) {
		jsonItem1 = jsonRoot["OnlineNodeData"];
		data.m_iStatus = jsonItem1["m_iStatus"].asInt();
		data.m_iIrisNum = jsonItem1["m_iIrisNum"].asInt();
		data.m_iDataVersion = jsonItem1["m_iDataVersion"].asInt();
		data.m_strIP = jsonItem1["m_strIP"].asString();
		data.m_iPort = jsonItem1["m_iPort"].asInt();
		data.m_iBestConNum = jsonItem1["m_iBestConNum"].asInt();
		data.m_strName = jsonItem1["m_strName"].asString();
		data.m_strPath = jsonItem1["m_strPath"].asString();
	}

    return 0;
}

