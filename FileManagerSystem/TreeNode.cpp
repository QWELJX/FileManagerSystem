#include "TreeNode.h"
#include "FileManager.h"
#include<iostream>
#include<iomanip>
#pragma region TreeNode

TreeNode::TreeNode(std::string name, TreeNodeType type, std::string path) :name(name), type(type), path(path), size(0) {}
TreeNode::TreeNode(std::string name, TreeNodeType type) :name(name), type(type), size(0) {

    this->path = PathUtils::join(FileManager::getInstance().GetCurrentPath(), name);
}
TreeNode::TreeNode(std::string name) :name(name), size(0) {

    this->type = TreeNodeType::DIRECTORY;
    this->path = PathUtils::join(FileManager::getInstance().GetCurrentPath(), name);
}
TreeNode::~TreeNode() {

}
//工具

#pragma region 封装接口
std::string TreeNode::GetName() { return this->name; }
std::string TreeNode::GetPath() {
std::cout << "路径内容: " << this->path << ", 长度: " << this->path.length() << std::endl;
       return this->path; }
TreeNodeType TreeNode::GetType() { return this->type; }
size_t TreeNode::GetSize() { return this->size; }
void TreeNode::SetName(std::string n) { this->name = n; }
void TreeNode::SetPath(std::string p) { this->path = p; }
void TreeNode::SetType(TreeNodeType t) { this->type = t; }
void TreeNode::SetSize(size_t s) { this->size = s; }
#pragma endregion


#pragma endregion
#pragma region 文件夹
DirectoryNode::DirectoryNode(std::string name, std::string path) :TreeNode(name, TreeNodeType::DIRECTORY, path) {
 
}
DirectoryNode::DirectoryNode(std::string name) :TreeNode(name, TreeNodeType::DIRECTORY) {

}

DirectoryNode::~DirectoryNode() {

    for (auto child : children) {
		std::string childPath = child->GetPath();
		delete child;
		FileManager::getInstance().RemoveNodeFromPathMap(childPath);
    }
	
}
void DirectoryNode::Show() {
    std::cout << "**************************************************" << std::endl;

    /// 表头 - 对齐
    std::cout << std::setw(6) << std::left << "序号"
        << std::setw(20) << std::left << "名称"
        << std::setw(12) << std::left << "类型"
        << std::setw(10) << std::right << "大小(B)" << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;

    //// 数据行
    int i;
    for (i = 0; i < this->GetChildrenSize(); ++i) {
        auto child = this->GetOneChild(i);
		auto type = child->GetType();
        std::string name = child->GetName() + treeNodeTypeToString(type).first;

        std::cout << std::setw(6) << std::left << i
            << std::setw(16) << std::left << (name.length() > 12 ? name.substr(0, 12) + "..." : name)
            << std::setw(12) << std::left << treeNodeTypeToString(type).second
            << std::setw(10) << std::right << child->GetSize() << std::endl;
    }
    for (int j = 0; j < 10 - i; ++j) std::cout << std::endl;
    std::cout << std::endl << "--------------------------------------------------" << std::endl;
    std::cout << "**************************************************" << std::endl;
}
#pragma region 接口封装
void DirectoryNode::AddChild(TreeNode* child) {
	FileManager::getInstance().SetNodeInPathMap(child->GetPath(), child);
    children.push_back(child);
}
size_t DirectoryNode::GetChildrenSize() { return children.size(); }
TreeNode* DirectoryNode::GetOneChild(size_t index) {
    if (index >= children.size())return nullptr;
    return children[index];
}
bool DirectoryNode::isNameAvailable(std::string fileName) {
    for (TreeNode* it : this->GetChild()) {
        if ((it->GetName()+treeNodeTypeToString(it->GetType()).first) ==fileName)
            return false;
    }
    return true;
}
bool  DirectoryNode::RemoveChild(const std::string& childName) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if ((*it)->GetName() == childName ) {
            std::string childPath = (*it)->GetPath();
            delete* it;
            FileManager::getInstance().RemoveNodeFromPathMap(childPath);
            children.erase(it);
            return true;
        }
	}
    return false;
}
bool  DirectoryNode::RemoveChild(TreeNode* p) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if ((*it)->GetName() == p->GetName() && (*it)->GetType() == p->GetType()) {
            // 用于 move：只从 children 容器中移除，但不 delete 指针（所有权由调用者转移）
            children.erase(it);
            return true;
        }
	}
    return false;
}
const std::vector<TreeNode*>& DirectoryNode::GetChild() const {
    return this->children;
}
#pragma endregion


#pragma endregion
#pragma region 文件
FileNode::FileNode(std::string name,TreeNodeType type, std::string path):TreeNode(name,type,path) {

}
FileNode::FileNode(std::string name, TreeNodeType type) :TreeNode(name,type){

}
FileNode* FileNode::Create(std::string name, std::string extension, std::string path) {
    TreeNodeType temp = stringToTreeNodeType(extension);
    if (temp != TreeNodeType::UNKNOWN) {
        return new FileNode(name, temp, path);
    }
    else {
        return new FileNode(name + extension, temp, path);
    }
}
FileNode::~FileNode() {
	
    FileManager::getInstance().RemoveNodeFromPathMap(this->GetPath());
}
void FileNode::Show(){

}
#pragma endregion


