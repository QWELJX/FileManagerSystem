
#include "FileManager.h"
#include "CMDManager.h"


#pragma region 构造函数
FileManager::FileManager() {
   

    this->rootDirectory = new DirectoryNode("C:","");
    this->currentDirectory = rootDirectory;
	this->currentPath ="C:";
    this->pathMap[currentPath] = rootDirectory;
	this->SetNodeInPathMap(currentPath, rootDirectory);
	this->rootDirectory->AddChild(new DirectoryNode("users",currentPath+SEPARATOR+"user"));
	this->rootDirectory->AddChild(new DirectoryNode("program files", currentPath + SEPARATOR + "user"));
     
};
#pragma endregion

#pragma region 操作函数
void FileManager::Show() {
    this->currentDirectory->Show();
	/*CMDManager::getInstance().showContent();*/
}
bool FileManager::handleMkdir(std::string name, std::string path){
    
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

    //std::string targetName = tokens[1];
    //std::string targetType = "";
    //if (tokens.size() == 2)
    //{
    //    targetType = "";
    //}
    //else if (tokens.size() == 3) {
    //    targetType = tokens[2];
    //}
    //FileNode* targetNode = nullptr;
    //// 在当前节点的子节点中查找
    //for (auto it = currentDirectory->children.begin(); it != currentDirectory->children.end(); ++it) {
    //    if ((*it)->name == targetName &&                                   //0.先判断名称是否一样
    //        ((fileTypeToString((*it)->type).second == "." + targetType) ||       //1.删除文件 输入的类型与目录中的文件的类型是否是一样
    //            fileTypeToString((*it)->type).second == "" && (targetType == ""))) {//2.删除文件夹 没输相当于输入的
    //        targetNode = *it;
    //        // 从pathMap中移除

    //      /*  pathMap.erase(fullPath);*/
    //        // 删除节点对象
    //        delete* it;
    //        // 从children中移除
    //        currentDirectory->children.erase(it);
    //        return true;
    //    }
    //}
    return false;
}
bool FileManager::handleGoto(const std::vector<std::string>& tokens) {

   /* std::string targetName = tokens[1];
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
    }*/
    return false;
}
bool FileManager::handleBack() {
  /*  if (pathHistory.size() <= 1) return false;
    pathHistory.pop();
    std::string prevPath = pathHistory.top();
    auto it = pathMap.find(prevPath);
    if (it != pathMap.end()) {
        currentDirectory = it->second;
        currentPath = prevPath;
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
	pathMap[path1+SEPARATOR] = node;
}
#pragma endregion
#pragma region 信息工具接口
void FileManager::CallBack(std::string content) {
    CMDManager::getInstance().appendContent(content);
}
#pragma endregion


