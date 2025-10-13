#include<iostream>
#include<iomanip>
#include "FileManager.h"
NodeManager::NodeManager(FileManager* fm) {

    this->m_Fm = fm;
    this->rootNode = new FileNode(this, fm->name);
    this->currentNode = rootNode;
    this->currentPath = fm->name + ":" + SEPARATOR;
    this->pathMap[currentPath] = rootNode;
    this->pathHistory.push(currentPath);
}
bool NodeManager::handleAdd(std::string name, FileNodeType type) {
    FileNode* T = new FileNode(this, name, type);
    this->pathMap[T->m_path + T->c_path] = T;
    this->currentNode->children.push_back(T);
    return false;
}
bool NodeManager::handleDelete(const std::vector<std::string>& tokens) {
    return true;
}
bool NodeManager::handleGoto(const std::vector<std::string>& tokens) {
    return true;
}
bool NodeManager::handleBack(const std::vector<std::string>& tokens) {
    return true;
}