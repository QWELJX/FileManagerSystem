
#include "FileManager.h"
#include "CMDManager.h"


#pragma region 构造函数
FileManager::FileManager() {
   

    this->rootDirectory = new DirectoryNode("C:","");
    this->currentDirectory = rootDirectory;
	this->currentPath ="C:";

	this->SetNodeInPathMap(currentPath, rootDirectory);
	this->rootDirectory->AddChild(new DirectoryNode("users",currentPath+SEPARATOR+"user"));
	this->rootDirectory->AddChild(new DirectoryNode("program files", currentPath + SEPARATOR + "user"));
     
};
#pragma endregion

#pragma region 操作函数
void FileManager::Show() {
    this->currentDirectory->Show();

}
bool FileManager::handleMkdir(std::string name, std::string path){
    
    //if (this->currentNode->permission == FilePermission::READ_ONLY || this->currentNode->permission == FilePermission::EXECUTE_ONLY)
    //{
    //    CallBack("当前目录没有写权限，无法添加文件或目录\n");
    //    return false;
    //}
    //FileNode* T = new FileNode(this, name, type);
    //this->currentNode->children.push_back(T);
    //std::string path;
    //if (this->currentPath[0] != SEPARATOR) {
    //    path = PathUtils::join(this->currentPath, name);
    //}
    //if (type == FileNodeType::DIRECTORY) {
    //    this->prePath = this->currentPath;
    //    //this->currentPath = this->prePath+SEPARATOR + name ;
    //    T->path = path;

    //}
    //else {
    //    T->path = path;
    //}
    //pathMap[path] = T;
    //int xx = 1;
    ////if (T->path != this->rootNode->path)
    ////    this->pathMap[T->path + "\\" ] = T;//C:\\picture\\1.txt
    ////else
    ////{
    ////    this->pathMap[T->path ] = T;
    ////}
    ////int xx = 1;
    ////return false;
    //FileNode* T = new FileNode(this, name, type);
    //this->currentDirectory->children.push_back(T);
    //this->pathMap[this->currentPath + SEPARATOR + T->name] = T;//C:\\picture\\1.txt
    return true;
}
bool FileManager::handleMkdir(std::string name) {

    //FileNode* T = new FileNode(this, name, type);
    //this->currentDirectory->children.push_back(T);
    //this->pathMap[this->currentPath + SEPARATOR + T->name] = T;//C:\\picture\\1.txt
    return true;
}
bool FileManager::handleDelete(const std::vector<std::string>& tokens) {


bool FileManager::handleGoto(std::string path) {
    }
    return false;
    }
    }
    else {
        int x = 1;
    }*/
    return false;
}
bool FileManager::handleBack() {
  /*  if (pathHistory.size() <= 1) return false;
    pathHistory.pop();
    std::string prevPath = pathHistory.top();
    auto it = pathMap.find(prevPath);
    if (it != pathMap.end()) {
    pathHistory.pop();
    std::string prevPath = pathHistory.top();
    auto it = pathMap.find(prevPath);
    if (it != pathMap.end()) {
        currentDirectory = it->second;
        currentPath = prevPath;
        pathHistory.pop();
        return true;
    }*/
    return false;
}
#pragma endregion

#pragma region 接口封装
DirectoryNode* FileManager::GetRootNode()const { return rootDirectory; }
DirectoryNode* FileManager::GetCurrentNode()const { return currentDirectory; }
std::string FileManager::GetCurrentPath() { return currentPath; }
TreeNode* FileManager::FindNodeByPath(const std::string& path) const {
    auto it = pathMap.find(path);
    return (it != pathMap.end()) ? it->second : nullptr;
}
//setter
void FileManager::SetCurrentNode(DirectoryNode* node) { currentDirectory = node; }
void FileManager::SetCurrentPath(const std::string& path) { currentPath = path; }
void FileManager::SetNodeInPathMap(const std::string& path, TreeNode* node) {
    std::string path1 = PathUtils::normalize(path);
    pathMap[path1] = node;
    pathMap[path1 + SEPARATOR] = node;
}
#pragma endregion
#pragma region 信息工具接口
void FileManager::CallBack(std::string content) {
    CMDManager::getInstance().appendContent(content);
}
#pragma endregion


