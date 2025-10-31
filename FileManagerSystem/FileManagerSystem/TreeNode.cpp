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
//����

#pragma region ��װ�ӿ�
std::string TreeNode::GetName() { return this->name; }
std::string TreeNode::GetPath() { return this->path; }
TreeNodeType TreeNode::GetType() { return this->type; }
size_t TreeNode::GetSize() { return this->size; }
void TreeNode::SetName(std::string n) { this->name = n; }
void TreeNode::SetPath(std::string p) { this->path = p; }
void TreeNode::SetType(TreeNodeType t) { this->type = t; }
void TreeNode::SetSize(size_t s) { this->size = s; }
#pragma endregion


#pragma endregion
#pragma region �ļ���
DirectoryNode::DirectoryNode(std::string name, std::string path) :TreeNode(name, TreeNodeType::DIRECTORY, path) {

}
DirectoryNode::DirectoryNode(std::string name) :TreeNode(name, TreeNodeType::DIRECTORY) {
	this->SetPath(PathUtils::join(FileManager::getInstance().GetCurrentPath(), name));

}
void DirectoryNode::Show() {
    std::cout << "**************************************************" << std::endl;

    /// ��ͷ - ����
    std::cout << std::setw(6) << std::left << "���"
        << std::setw(20) << std::left << "����"
        << std::setw(12) << std::left << "����"
        << std::setw(10) << std::right << "��С(B)" << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;

    //// ������
    int i;
    for (i = 0; i < this->GetChildrenSize(); ++i) {
        auto child = this->GetOneChild(i);
		auto type = child->GetType();
        std::string name = child->GetName() +'.'+ treeNodeTypeToString(type).first;

        std::cout << std::setw(6) << std::left << i
            << std::setw(16) << std::left << (name.length() > 12 ? name.substr(0, 12) + "..." : name)
            << std::setw(12) << std::left << treeNodeTypeToString(type).second
            << std::setw(10) << std::right << child->GetSize() << std::endl;
    }
    for (int j = 0; j < 10 - i; ++j) std::cout << std::endl;
    std::cout << std::endl << "--------------------------------------------------" << std::endl;
    std::cout << "**************************************************" << std::endl;
}
#pragma region �ӿڷ�װ
void DirectoryNode::AddChild(TreeNode* child) {
    children.push_back(child);
}
size_t DirectoryNode::GetChildrenSize() { return children.size(); }
TreeNode* DirectoryNode::GetOneChild(size_t index) {
    if (index >= children.size())return nullptr;
    return children[index];
}
bool DirectoryNode::isNameAvailable(DirectoryNode T) {
    for (TreeNode* it : T.GetChild()) {
        if (it->GetName() == T.GetName() && it->GetType() == T.GetType())
            return false;
    }
    return true;
}
bool  DirectoryNode::RemoveChild(const std::string& childName) {
    return false;
}
bool  DirectoryNode::RemoveChild(size_t t) {
    return false;
}
const std::vector<TreeNode*>& DirectoryNode::GetChild() const {
    return this->children;
}
#pragma endregion


#pragma endregion


