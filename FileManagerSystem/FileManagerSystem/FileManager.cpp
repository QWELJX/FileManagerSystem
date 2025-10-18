#include<iostream>
#include<iomanip>
#include "FileManager.h"
#include "CMDManager.h"
void FileManager::CallBack(std::string content) {
    CMDManager::getInstance().appendContent(content);
}

FileManager::FileManager() {
    std::string rootName = "C:";

    this->rootDirectory = new DirectoryNode(rootName);
    this->currentDirectory = rootDirectory;
	this->currentPath = rootName;
    this->pathMap[rootName] = rootDirectory;

	this->rootDirectory->AddChild(new DirectoryNode("users"));
	this->rootDirectory->AddChild(new DirectoryNode("program files"));
     
};

void FileManager::Show() {
    this->currentDirectory->Show();
    //std::cout << "**************************************************" << std::endl;

    //// ��ͷ - ����
    //std::cout << std::setw(6) << std::left << "���"
    //    << std::setw(20) << std::left << "����"
    //    << std::setw(12) << std::left << "����"
    //    << std::setw(10) << std::right << "��С(B)" << std::endl;

    //std::cout << "--------------------------------------------------" << std::endl;

    //// ������
    //int i;
    //for (i = 0; i < this->currentNode->GetSize(); ++i) {
    //    auto child = this->currentNode->children[i];
    //    std::string name = child->name + fileTypeToString(child->type).second;

    //    std::cout << std::setw(6) << std::left << i
    //        << std::setw(16) << std::left << (name.length() > 12 ? name.substr(0, 12) + "..." : name)
    //        << std::setw(12) << std::left << fileTypeToString(child->type).first
    //        << std::setw(10) << std::right << child->size << std::endl;
    //}
    //for (int j = 0; j < 10 - i; ++j) std::cout << std::endl;
    //std::cout << std::endl << "--------------------------------------------------" << std::endl;
    //std::cout << "**************************************************" << std::endl;
}
bool FileManager::handleAdd(std::string name, FileNodeType type) {
    if (this->currentDirectory->GetPermission() == FilePermission::READ_ONLY || this->currentDirectory->GetPermission() == FilePermission::EXECUTE_ONLY)
    {
		CallBack("��ǰĿ¼û��дȨ�ޣ��޷�����ļ���Ŀ¼\n");
        return false;
    }
    FileNode* T = new FileNode(this, name, type);
    this->currentDirectory->children.push_back(T);
    this->pathMap[this->currentPath+SEPARATOR+T->name] = T;//C:\\picture\\1.txt
    return true;
}//�����������
bool FileManager::handleDelete(const std::vector<std::string>& tokens) {

    std::string targetName = tokens[1];
    std::string targetType = "";
    if (tokens.size() == 2)
    {
        targetType = "";
    }
    else if (tokens.size() == 3) {
        targetType = tokens[2];
    }
    FileNode* targetNode = nullptr;
    // �ڵ�ǰ�ڵ���ӽڵ��в���
    for (auto it = currentDirectory->children.begin(); it != currentDirectory->children.end(); ++it) {
        if ((*it)->name == targetName &&                                   //0.���ж������Ƿ�һ��
            ((fileTypeToString((*it)->type).second == "." + targetType) ||       //1.ɾ���ļ� �����������Ŀ¼�е��ļ��������Ƿ���һ��
                fileTypeToString((*it)->type).second == "" && (targetType == ""))) {//2.ɾ���ļ��� û���൱�������
            targetNode = *it;
            // ��pathMap���Ƴ�
          
          /*  pathMap.erase(fullPath);*/
            // ɾ���ڵ����
            delete* it;
            // ��children���Ƴ�
            currentDirectory->children.erase(it);
            return true;
        }
    }
    return false;
}
bool FileManager::handleGoto(const std::vector<std::string>& tokens) {

    std::string targetName = tokens[1];
    std::string targetPath = currentPath;
    if (targetPath.back() != SEPARATOR) targetPath += SEPARATOR;
    targetPath += targetName;
    auto it = pathMap.find(targetPath);
    int x = 1;
    if (it != pathMap.end()) {
        currentDirectory = it->second;
        currentPath = targetPath;
        pathHistory.push(targetPath);
        return true;
    }
    else {
        int x = 1;
    }
    return false;
}
bool FileManager::handleBack() {
    if (pathHistory.size() <= 1) return false;
    pathHistory.pop();
    std::string prevPath = pathHistory.top();
    auto it = pathMap.find(prevPath);
    if (it != pathMap.end()) {
        currentDirectory = it->second;
        currentPath = prevPath;
        return true;
    }
    return false;
}
bool FileManager::isNameAvailable(std::string name) {
  /*  if(pathMap[currentPath+pa])*/
    for (auto& it : this->currentNode->children) {
        if (it->name == name)
            return false;
        return true;
    }
}
