#include "FileNode.h"
#include "NodeManager.h"
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
FileNode::FileNode(NodeManager* nm, std::string name, FileNodeType type):nm(nm), name(name), type(type), size(0) {
	//c:/picture/a.txt
	this->m_path = nm->currentPath;									//�����ļ��е�·��c:/picture
	this->c_path =   name + fileTypeToString(type).second;//�ڵ����·������/a.txt
	int x = 1;
}
