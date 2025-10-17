//第四个

#pragma once
#include<vector>
#include "FileNodeType.h"
class FileManager;
class FileNode {
private:
	FileManager* m_Fm;//指针负责管理所有FileNode的节点，
public:
	std::vector<FileNode*> children;

	std::string name;
	//路径
	std::string path;
	/*std::string c_path;*///多余变量 直接用name和fileTypeToString(type).second代替std::string c_path
	FilePermission permission;
	FileNodeType type;

	size_t size;
	FileNode(FileManager* fm, std::string name, FileNodeType type = FileNodeType::DIRECTORY, FilePermission permission = FilePermission::FULL_CONTROL);//如名字后没有具体的文件类型，就默认是文件夹
	size_t GetSize();



};

