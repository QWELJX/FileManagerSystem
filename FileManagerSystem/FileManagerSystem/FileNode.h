//���ĸ�

#pragma once
#include<vector>
#include "FileNodeType.h"
class FileManager;
class FileNode {
private:
	FileManager* m_Fm;//ָ�븺���������FileNode�Ľڵ㣬
public:
	std::vector<FileNode*> children;

	std::string name;
	//·��
	std::string path;
	/*std::string c_path;*///������� ֱ����name��fileTypeToString(type).second����std::string c_path
	FilePermission permission;
	FileNodeType type;

	size_t size;
	FileNode(FileManager* fm, std::string name, FileNodeType type = FileNodeType::DIRECTORY, FilePermission permission = FilePermission::FULL_CONTROL);//�����ֺ�û�о�����ļ����ͣ���Ĭ�����ļ���
	size_t GetSize();



};

