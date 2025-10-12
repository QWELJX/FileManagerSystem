#include "FileNode.h"
#include "NodeManager.h"
size_t FileNode::GetSize() {
	return children.size();
}

//FileNode::FileNode() {
//	nm=
//	type = FileNodeType::DIRECTORY;
//	size = 0;
//	std::string TEMP = "新建文件夹";
//	size_t tempi = 1;
//	while (!CValid(TEMP)) {
//		TEMP += tempi++;
//	}
//	name = TEMP;
//}
FileNode::FileNode(NodeManager* nm, std::string name, FileNodeType type):nm(nm), name(name), type(type), size(0) {
	//c:/picture/a.txt
	this->m_path = nm->currentPath;									//所在文件夹的路径c:/picture
	this->c_path =   name + fileTypeToString(type).second;//节点组件路径，如/a.txt
	int x = 1;
}
