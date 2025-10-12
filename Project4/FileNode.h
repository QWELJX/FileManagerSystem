//第四个

#pragma once
#include<vector>
#include "FileNodeType.h"
class NodeManager;
class FileNode {
private:
	NodeManager* nm;//指针负责管理所有FileNode的节点，
public:
	std::vector<FileNode*> children;

	std::string name;
	//路径
	std::string m_path;
	std::string c_path;

	FileNodeType type;
	
	size_t size;
	FileNode(NodeManager*nm,std::string name, FileNodeType type = FileNodeType::DIRECTORY);//如名字后没有具体的文件类型，就默认是文件夹
	size_t GetSize();

	bool CValid(std::string name);
	
};

