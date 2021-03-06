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


std::string TestWrite1() {
	Json::Value jsonRoot;//定义一个根目录
	Json::Value jsonItem;//定义一个子对象
	jsonItem["item1"] = "one";//添加数据
	jsonItem["item2"] = 2;//添加数据

	jsonRoot.append(jsonItem);
	cout << "TestWrite1 success!" << endl;
	return jsonRoot.toStyledString();
}

void TestRead1(std::string &_val) {
	Json::Value jsonRoot;//定义一个根目录
	Json::Value jsonItem;//定义一个子对象

	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	JSONCPP_STRING errs;

	Json::CharReader* reader = builder.newCharReader();

	if (!reader->parse(_val.data(), _val.data() +
		_val.size(), &jsonRoot, &errs)) //从jsonStr中读取数据到jsonRoot
	{
		//失败
		cout << "TestRead1 failed!" << endl;
	}
	else {
		if (!jsonRoot[NULL].isNull()) {
			jsonItem = jsonRoot[NULL];
			cout << "item1 = " << jsonItem["item1"].asString() << endl;
			cout << "item2 = " << jsonItem["item2"].asInt() << endl;

			cout << "TestRead1 success!" << endl;
		}
	}
}

std::string TestWrite2() {
	Json::Value jsonRoot;//定义一个根目录
	Json::Value jsonItem;//定义一个子对象
	jsonItem["item1"] = 1.0;
	jsonItem["item2"] = 2.0;
	jsonRoot["Item1"] = jsonItem;
	cout << "TestWrite2 success!" << endl;
	return jsonRoot.toStyledString();
}

void TestRead2(std::string &_val) {
	Json::Value jsonRoot;//定义一个根目录
	Json::Value jsonItem;//定义一个子对象

	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	JSONCPP_STRING errs;

	Json::CharReader* reader = builder.newCharReader();

	if (!reader->parse(_val.data(), _val.data() +
		_val.size(), &jsonRoot, &errs)) //从jsonStr中读取数据到jsonRoot
	{
		//失败
		cout << "TestRead2 failed!" << endl;
	}
	else {
		if (!jsonRoot["Item1"].isNull()) {
			jsonItem = jsonRoot["Item1"];
			cout << "item1 = " << jsonItem["item1"].asDouble() << endl;
			cout << "item2 = " << jsonItem["item2"].asDouble() << endl;

			cout << "TestRead2 success!" << endl;
		}
	}
}

std::string TestWrite3() {
	Json::Value jsonRoot;//定义一个根目录
	Json::Value jsonItem;//定义一个子对象
	jsonItem["m_iStatus"] = 0;
	jsonItem["m_iIrisNum"] = 0;
	jsonItem["m_iDataVersion"] = 1;
	jsonItem["m_strIP"] = "127.0.0.1";
	jsonItem["m_iPort"] = 9906;
	jsonItem["m_iBestConNum"] = 20;
	jsonItem["m_strName"] = "Server-2";
	jsonItem["m_strPath"] = "/Server";
	jsonRoot["OnlineNodeData"] = jsonItem;
	cout << "TestWrite3 success!" << endl;
	return jsonRoot.toStyledString();
}

void TestRead3(std::string &_val) {
	Json::Value jsonRoot;//定义一个根目录
	Json::Value jsonItem;//定义一个子对象

	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	JSONCPP_STRING errs;

	Json::CharReader* reader = builder.newCharReader();

	if (!reader->parse(_val.data(), _val.data() +
		_val.size(), &jsonRoot, &errs)) //从jsonStr中读取数据到jsonRoot
	{
		//失败
		cout << "TestRead3 failed!" << endl;
	}
	else {
		if (!jsonRoot["OnlineNodeData"].isNull()) {
			OnlineNodeData data;
			jsonItem = jsonRoot["OnlineNodeData"];
			data.m_iStatus = jsonItem["m_iStatus"].asInt();
			data.m_iIrisNum = jsonItem["m_iIrisNum"].asInt();
			data.m_iDataVersion = jsonItem["m_iDataVersion"].asInt();
			data.m_strIP = jsonItem["m_strIP"].asString();
			data.m_iPort = jsonItem["m_iPort"].asInt();
			data.m_iBestConNum = jsonItem["m_iBestConNum"].asInt();
			data.m_strName = jsonItem["m_strName"].asString();
			data.m_strPath = jsonItem["m_strPath"].asString();

			cout << "m_iStatus = " << data.m_iStatus << endl;
			cout << "m_iIrisNum = " << data.m_iIrisNum << endl;
			cout << "m_iDataVersion = " << data.m_iDataVersion << endl;
			cout << "m_strIP = " << data.m_strIP << endl;
			cout << "m_iPort = " << data.m_iPort << endl;
			cout << "m_iBestConNum = " << data.m_iBestConNum << endl;
			cout << "m_strName = " << data.m_strName << endl;
			cout << "m_strPath = " << data.m_strPath << endl;
			cout << "TestRead3 success!" << endl;
		}
	}
}









int main() {
	//测试一
	std::string test1 = TestWrite1();
	TestRead1(test1);
	// 测试二
	std::string test2 = TestWrite2();
	TestRead2(test2);

	//测试三
	std::string test3 = TestWrite3();
	TestRead3(test3);
	return 0;
}



