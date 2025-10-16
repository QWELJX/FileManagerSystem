//第二

#pragma once
#include <string>
#include<unordered_map>
#include<stack>
#include "FileNode.h"
#include "FileNodeType.h"
#include "PathUtils.h"
class FileManager {

private:

	
public:
	
	//自定义命令行
	//std::string name;//管理器名字//冗余变量 根节点带名字 

	FileNode* rootNode;//根节点
	FileNode* currentNode;//当前节点
	std::string currentPath;//当前路径
	std::unordered_map<std::string, FileNode*> pathMap;//路径表(快速找节点，利于绝对路径)
	std::stack<std::string> pathHistory;// 路径历史栈，支持多级返回,利于相对路径

	FileManager(std::string name);
	void Show();
	void CallBack(std::string);//文件管理器回调函数 用于给CMD返回信息
	//------------------------------------------------------------------------------------------------
	/*FileNode* SearchNode(std::string);*/
	//操作
	//添加文件
	bool handleAdd(std::string name, FileNodeType type = FileNodeType::DIRECTORY);
	//删除文件
	bool handleDelete(const std::vector<std::string>& tokens);
	////跳转 
	bool handleGoto(const std::vector<std::string>& tokens);
	////回退
	bool handleBack();
	bool isNameAvailable(std::string name);
};
