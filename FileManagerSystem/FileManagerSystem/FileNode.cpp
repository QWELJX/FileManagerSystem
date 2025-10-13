#include "FileNode.h"
#include "NodeManager.h"
size_t FileNode::GetSize() {
	return children.size();
}
bool FileNode::CValid(std::string name) {

	for (auto& it : this->children) {
		if (it->name == name)
			return false;
		return true;
	}
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
FileNode::FileNode(NodeManager* nm, std::string name, FileNodeType type) :nm(nm), name(name), type(type), size(0) {
	this->m_path = nm->currentPath;
	this->c_path = SEPARATOR + name + fileTypeToString(type).second;
}