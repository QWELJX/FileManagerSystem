//第四个

#pragma once
#include<vector>
#include "FileNodeType.h"
class NodeManager;
class FileNode {
private:
	NodeManager* nm;
public:
	std::vector<FileNode*> children;

	std::string name;
	//路径
	std::string m_path;
	std::string c_path;

	FileNodeType type;

	size_t size;
	FileNode(NodeManager* nm, std::string name, FileNodeType type = FileNodeType::DIRECTORY);
	size_t GetSize();

	bool CValid(std::string name);

};