
#include<iostream>
#include<iomanip>
#include "FileManager.h"
#include "CMDManager.h"
//FileManager::FileManager() {
//   
//    m_NM = new FileManager(this);
//

//}//û��
void FileManager::CallBack(std::string content) {
    CMDManager::getInstance().appendContent(content);
}
FileManager::FileManager(std::string name) {
	std::string rootName = name + ":" + SEPARATOR;
    this->rootNode = new FileNode(this,rootName,FileNodeType::DIRECTORY,FilePermission::NONE_CONTROL);
    this->currentNode = rootNode;//!!!!   
    rootNode->path = "";
    this->pathMap[currentPath+SEPARATOR+rootName] = rootNode;
    /*this->pathHistory.push(SEPARATOR+rootName);*/ //���� ϸ����ljx
	//����ڵ� c:\ ��ô����[\Project,\FileManager,\File] ��ǰ��File�µ�ĳ���ڵ� �������·�� ���� cd . �ᵯ��ջ��Ԫ�� (����ָFile)
	// cd .. �ᵯ��ջ2�� (FileManager) ���ܷ����ϼ�Ŀ¼ ���ܴ������·��

};

void FileManager::Show() {
    std::cout << "**************************************************" << std::endl;

    // ��ͷ - ����
    std::cout << std::setw(6) << std::left << "���"
        << std::setw(20) << std::left << "����"
        << std::setw(12) << std::left << "����"
        << std::setw(10) << std::right << "��С(B)" << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;

    // ������
    int i;
    for (i = 0; i < this->currentNode->GetSize(); ++i) {
        auto child = this->currentNode->children[i];
        std::string name = child->name + fileTypeToString(child->type).second;

        std::cout << std::setw(6) << std::left << i
            << std::setw(16) << std::left << (name.length() > 12 ? name.substr(0, 12) + "..." : name)
            << std::setw(12) << std::left << fileTypeToString(child->type).first
            << std::setw(10) << std::right << child->size << std::endl;
    }
    for (int j = 0; j < 10 - i; ++j) std::cout << std::endl;
    std::cout << std::endl << "--------------------------------------------------" << std::endl;
    std::cout << "**************************************************" << std::endl;
}
bool FileManager::handleAdd(std::string name, FileNodeType type) {
    if (this->currentNode->permission == FilePermission::READ_ONLY || this->currentNode->permission == FilePermission::EXECUTE_ONLY)
    {
		CallBack("��ǰĿ¼û��дȨ�ޣ��޷�����ļ���Ŀ¼\n");
		return false;
    }
    FileNode* T = new FileNode(this, name, type);
    this->currentNode->children.push_back(T);
    if(type== FileNodeType::DIRECTORY){
	this->currentPath = this->prePath+SEPARATOR + name ;
	T->path = this->currentPath;
    this->prePath = this->currentPath;
    }
    else {
        this->currentPath =this->prePath+ SEPARATOR + name;
    }
    pathMap[T->path] = T;
    //if (T->path != this->rootNode->path)
    //    this->pathMap[T->path + "\\" ] = T;//C:\\picture\\1.txt
    //else
    //{
    //    this->pathMap[T->path ] = T;
    //}
    //int xx = 1;
    //return false;
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
    for (auto it = currentNode->children.begin(); it != currentNode->children.end(); ++it) {
        if ((*it)->name == targetName &&                                   //0.���ж������Ƿ�һ��
            ((fileTypeToString((*it)->type).second == "." + targetType) ||       //1.ɾ���ļ� �����������Ŀ¼�е��ļ��������Ƿ���һ��
                fileTypeToString((*it)->type).second == "" && (targetType == ""))) {//2.ɾ���ļ��� û���൱�������
            targetNode = *it;
            // ��pathMap���Ƴ�
            std::string fullPath = (*it)->path ;
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
bool FileManager::handleGoto(std::string path) {
    
    if (path[0]!= SEPARATOR) {
		path = PathUtils::join(this->currentPath, path);
    }
    if (pathMap[path]==nullptr) {
        CallBack("��·��������\n");
		return false;
	}
	this->currentPath =path;
	currentNode = pathMap[currentPath];
}
bool FileManager::handleBack() {
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
bool FileManager::isNameAvailable(std::string name) {
    if(pathMap[currentPath])
    for (auto& it : this->currentNode->children) {
        if (it->name == name)
            return false;
        return true;
    }
}
