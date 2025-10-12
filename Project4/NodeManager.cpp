#include<iostream>
#include<iomanip>
#include "FileManager.h"
NodeManager::NodeManager(FileManager*fm){

    this->m_Fm = fm;
    this->rootNode = new FileNode(this, fm->name);
    this->currentNode = rootNode;//!!!!   
    rootNode->c_path = "";
    rootNode->m_path=this->currentPath = fm->name + ":"+SEPARATOR;//!!!!   //����C:\\
    this->pathMap[currentPath] = rootNode;
    this->pathHistory.push(currentPath);//!!!!
    int x = 1;
}
bool NodeManager::handleAdd(std::string name,FileNodeType type) {
    FileNode* T = new FileNode(this,name, type);
    int x = 1;
    //this->currentPath = T->m_path + T->c_path;
    this->currentNode->children.push_back(T);
    if(T->m_path!=this->rootNode->m_path)
        this->pathMap[T->m_path +"\\" + T->c_path] = T;//C:\\picture\\1.txt
    else
    {
        this->pathMap[T->m_path + T->c_path] = T;
    }
    int xx = 1;
    return false;
}//�����������
bool NodeManager::handleDelete(const std::vector<std::string>& tokens) {
    
    std::string targetName = tokens[1];    
    std::string targetType = "";
    if (tokens.size() == 2)
    {
        targetType = "";
    }
    else if(tokens.size()==3){
        targetType = tokens[2];
    }
    FileNode* targetNode = nullptr;
    // �ڵ�ǰ�ڵ���ӽڵ��в���
    for (auto it = currentNode->children.begin(); it != currentNode->children.end(); ++it) {
        if ((*it)->name == targetName&&                                   //0.���ж������Ƿ�һ��
            ((fileTypeToString((*it)->type).second=="."+targetType)||       //1.ɾ���ļ� �����������Ŀ¼�е��ļ��������Ƿ���һ��
             fileTypeToString((*it)->type).second==""&& (targetType==""))) {//2.ɾ���ļ��� û���൱�������
            targetNode = *it;
            // ��pathMap���Ƴ�
            std::string fullPath = (*it)->m_path + (*it)->c_path;
            pathMap.erase(fullPath);
            // ɾ���ڵ����
            delete* it;
            // ��children���Ƴ�
            currentNode->children.erase(it);
            return true;
        }      
    }
    return false;
}
bool NodeManager::handleGoto(const std::vector<std::string>& tokens) {
    
    std::string targetName =tokens[1];
    std::string targetPath = currentPath;
    if (targetPath.back() != SEPARATOR) targetPath += SEPARATOR;
    targetPath += targetName;
    auto it = pathMap.find(targetPath);
    int x = 1;
    if (it != pathMap.end()) {
        currentNode = it->second;
        currentPath = targetPath;
        pathHistory.push(targetPath);
        return true;
    }
    else {
        int x = 1;
    }
    return false;
}
bool NodeManager::handleBack() {
    if (pathHistory.size() <= 1) return false;
    pathHistory.pop();
    std::string prevPath = pathHistory.top();
    auto it = pathMap.find(prevPath);
    if (it != pathMap.end()) {
        currentNode = it->second;
        currentPath = prevPath;
        return true;
    }
    return false;
}
bool NodeManager::CValid(std::string name) {

    for (auto& it : this->currentNode->children) {
        if (it->name == name)
            return false;
        return true;
    }
}
