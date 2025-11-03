
#include "FileManager.h"
#include "CMDManager.h"
#include <functional>

#pragma region 构造函数
FileManager::FileManager() {
   

    this->rootDirectory = new DirectoryNode("C:","C:");
    this->currentDirectory = rootDirectory;
	this->currentPath ="C:";
	this->SetNodeInPathMap(currentPath, rootDirectory);
	/*this->rootDirectory->AddChild(new DirectoryNode("users",currentPath+SEPARATOR+"user"));
	this->rootDirectory->AddChild(new DirectoryNode("program files", currentPath + SEPARATOR + "user"));*/
 
};
#pragma endregion

#pragma region 操作函数

bool FileManager::handleMkdir(std::string name) {
    DirectoryNode* T = new DirectoryNode(name, this->currentPath + SEPARATOR + name);
    if (this->currentDirectory->isNameAvailable(T)) {
        this->currentDirectory->AddChild(T);
		return true;
    }
    else {
       
		CallBack("当前目录已有"+T->GetName() + "文件夹\n");
        delete T;
		return false;
    }
  
}
bool FileManager::handleMkdir(std::string name, std::string path){
	
	path = getAbsolutePath(path);
	this->mkdirRecursive(path+SEPARATOR+name);
    return true;
}
bool FileManager::handleGoto(std::string path) {
	path = getAbsolutePath(path);
    TreeNode* node = FindNodeByPath(path);
    if (node != nullptr) {
        if (node->GetType() == TreeNodeType::DIRECTORY) {
            this->currentDirectory = dynamic_cast<DirectoryNode*>(node);
			this->currentPath = path;
        }
        else {
            CallBack("错误: 目标不是目录\n");
			return false;
        }
    }
    else {
        CallBack("错误: 路径"+path+"不存在\n");
		return false;
    }
    return true;
}
bool FileManager::handleDelete(std::string path) {
    path = getAbsolutePath(path);
    TreeNode* node = FindNodeByPath(path);
    if (node != nullptr) {
        DirectoryNode* parentNode = dynamic_cast<DirectoryNode*>(FindNodeByPath(PathUtils::getDirectory(path)));
        if (parentNode != nullptr) {
            if (parentNode->RemoveChild(node)) {
                return true;
            }
            else {
				CallBack("错误: 删除失败\n");
            }
        }

    }
    else {
		CallBack("错误: 路径" + path + "不存在\n");
    }
}
bool FileManager::HandleCreateFile(std::string name,std::string extension) {
	FileNode* T = new FileNode(name,stringToTreeNodeType(extension), this->currentPath + SEPARATOR + name + extension);
    if (this->currentDirectory->isNameAvailable(T)) {
        this->currentDirectory->AddChild(T);
        return true;
    }
    else {

        CallBack("当前目录已有" + T->GetName() +extension+ "\n");
        delete T;
        return false;
    }
}
bool FileManager::HandleCreateFile(std::string name,std::string extension, std::string path) {
    DirectoryNode* T1 = dynamic_cast<DirectoryNode*>(FindNodeByPath(path));
    if (T1 != nullptr) {
        FileNode* T2 = new FileNode(name, stringToTreeNodeType(extension), path + name + extension);
        if(T1->isNameAvailable(T2)){
            T1->AddChild(T2);
            return true;
        }
        else {
            CallBack("目录" + path + "已有" + T2->GetName() + extension + "\n");
            delete T2;
            return false;
		}
    }
    else {
        CallBack("错误: 路径" + path + "不存在\n");
		return false;
    }
   
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
    pathMap[path] = node;
    pathMap[path + SEPARATOR] = node;
}
void FileManager::RemoveNodeFromPathMap(const std::string& path){
    pathMap.erase(path);
    pathMap.erase(path + SEPARATOR);
}
#pragma endregion
#pragma region 信息工具接口
void FileManager::Show() {
    this->currentDirectory->Show();

}
void FileManager::CallBack(std::string content) {
    CMDManager::getInstance().appendContent(content);
}
#pragma endregion
#pragma region 纯工具
DirectoryNode* FileManager::mkdirRecursive(std::string path) {

    DirectoryNode* node = dynamic_cast<DirectoryNode*>(FindNodeByPath(path));
    if (node == nullptr) {
        auto Path = PathUtils::split(path);
        auto dirPath = Path.first;
        auto name = Path.second;
        node = new DirectoryNode(name, path);
       mkdirRecursive(dirPath)->AddChild(node);
    }
    return node;  
}
std::string FileManager::getAbsolutePath(std::string path) {
    if (PathUtils::isAbsolute(path)) {
        if (path[0] = SEPARATOR) {
            path = PathUtils::join(this->rootDirectory->GetPath(),path);
        }
    }
    else {
        path = PathUtils::join(this->currentPath, path);
    }
	return path;
}
#pragma endregion


