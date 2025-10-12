//���ĸ�

#pragma once
#include<vector>
#include "FileNodeType.h"
class NodeManager;
class FileNode {
private:
	NodeManager* nm;//ָ�븺���������FileNode�Ľڵ㣬
public:
	std::vector<FileNode*> children;

	std::string name;
	//·��
	std::string m_path;
	std::string c_path;

	FileNodeType type;
	
	size_t size;
	FileNode(NodeManager*nm,std::string name, FileNodeType type = FileNodeType::DIRECTORY);//�����ֺ�û�о�����ļ����ͣ���Ĭ�����ļ���
	size_t GetSize();

	bool CValid(std::string name);
	
};

