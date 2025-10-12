#include<iostream>
#include<iomanip>
#include "FileManager.h"
NodeManager::NodeManager(FileManager*fm){

    this->m_Fm = fm;
    this->rootNode = new FileNode(this, fm->name);
    this->currentNode = rootNode;//!!!!
    this->currentPath = fm->name + ":"+SEPARATOR;//!!!!   //例如C:\\
    this->pathMap[currentPath] = rootNode;
    this->pathHistory.push(currentPath);//!!!!
}
bool NodeManager::handleAdd(std::string name,FileNodeType type) {
    FileNode* T = new FileNode(this,name, type);
    this->pathMap[T->m_path + T->c_path] = T;//C:\\picture\\1.txt
    //this->currentPath = T->m_path + T->c_path;
    this->currentNode->children.push_back(T);
    return false;
}//对树进行添加
bool NodeManager::handleDelete(const std::vector<std::string>& tokens) {
    return true;
}
bool NodeManager::handleGoto(const std::vector<std::string>& tokens) {

    return true;
}
bool NodeManager::handleBack() {
    //FileNode* T = this->currentNode;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return true;
}
