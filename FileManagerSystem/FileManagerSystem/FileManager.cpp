
#include<iostream>
#include<iomanip>
#include "FileManager.h"
#include "CMDManager.h"
//FileManager::FileManager() {
//   
//    m_NM = new FileManager(this);
//

//}//没用
void FileManager::CallBack(std::string content) {
    CMDManager::getInstance().appendContent(content);
}
FileManager::FileManager(std::string name) {
	std::string rootName = name + ":" + SEPARATOR;
    this->rootNode = new FileNode(this,rootName,FileNodeType::DIRECTORY,FilePermission::NONE_CONTROL);
    this->currentNode = rootNode;//!!!!   
    rootNode->path = "";
    this->pathMap[currentPath+SEPARATOR+rootName] = rootNode;
    /*this->pathHistory.push(SEPARATOR+rootName);*/ //不推 细节问ljx
	//比如节点 c:\ 那么容器[\Project,\FileManager,\File] 当前在File下的某个节点 处理相对路径 比如 cd . 会弹出栈顶元素 (这里指File)
	// cd .. 会弹出栈2次 (FileManager) 就能返回上级目录 还能处理相对路径

};

void FileManager::Show() {
    std::cout << "**************************************************" << std::endl;

    // 表头 - 对齐
    std::cout << std::setw(6) << std::left << "序号"
        << std::setw(20) << std::left << "名称"
        << std::setw(12) << std::left << "类型"
        << std::setw(10) << std::right << "大小(B)" << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;

    // 数据行
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
		CallBack("当前目录没有写权限，无法添加文件或目录\n");
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
}//对树进行添加
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
    // 在当前节点的子节点中查找
    for (auto it = currentNode->children.begin(); it != currentNode->children.end(); ++it) {
        if ((*it)->name == targetName &&                                   //0.先判断名称是否一样
            ((fileTypeToString((*it)->type).second == "." + targetType) ||       //1.删除文件 输入的类型与目录中的文件的类型是否是一样
                fileTypeToString((*it)->type).second == "" && (targetType == ""))) {//2.删除文件夹 没输相当于输入的
            targetNode = *it;
            // 从pathMap中移除
            std::string fullPath = (*it)->path ;
            pathMap.erase(fullPath);
            // 删除节点对象
            delete* it;
            // 从children中移除
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
        CallBack("该路径不存在\n");
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
