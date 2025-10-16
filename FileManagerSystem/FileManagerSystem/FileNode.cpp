#include "FileNode.h"
#include "FileManager.h"
size_t FileNode::GetSize() {
	return children.size();
}

//FileNode::FileNode() {
//	nm=
//	type = FileNodeType::DIRECTORY;
//	size = 0;
//	std::string TEMP = "�½��ļ���";
//	size_t tempi = 1;
//	while (!CValid(TEMP)) {
//		TEMP += tempi++;
//	}
//	name = TEMP;
//}
FileNode::FileNode(FileManager* fm, std::string name, FileNodeType type, FilePermission permission):m_Fm(fm),name(name),size(0){
	this->type = type;
	this->permission = permission;
	this->path = m_Fm->currentPath;									//�����ļ��е�·��c:/picture
}
