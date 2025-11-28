
#include "FileManager.h"
#include "CMDManager.h"
#include <functional>

#pragma region 构造函数
FileManager::FileManager() {
   
    this->pathMap["C:"]= rootDirectory;
	this->rootDirectory = new DirectoryNode("C:", "C:");//创建根目录
    this->currentDirectory = rootDirectory;
	this->currentPath ="C:";
	this->SetNodeInPathMap(currentPath, rootDirectory);
	/*this->rootDirectory->AddChild(new DirectoryNode("users",currentPath+SEPARATOR+"user"));
	this->rootDirectory->AddChild(new DirectoryNode("program files", currentPath + SEPARATOR + "user"));*/
 
};
#pragma endregion

#pragma region 操作函数

bool FileManager::handleMkdir(std::string name) {
    
    if (this->currentDirectory->isNameAvailable(name)) {
        DirectoryNode* T = new DirectoryNode(name, this->currentPath + SEPARATOR + name);
        this->currentDirectory->AddChild(T);
		return true;
    }
    else {
       
		CallBack("\033[31m当前目录已有"+name + "文件夹\033[0m\n");
 
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
            CallBack("\033[31m错误: 目标不是目录\033[0m\n");
			return false;
        }
    }
    else {
        CallBack("\033[31m错误: 路径"+path+"不存在\033[0m\n");
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
				CallBack("\033[31m错误: 删除失败\033[0m\n");
            }
        }

    }
    else {
		CallBack("\033[31m错误: 路径" + path + "不存在\033[0m\n");
    }
}
bool FileManager::HandleCreateFile(std::string name,std::string extension) {
    std::string fullFileName = name + extension; //变量名像链家性说的那样驼峰命名
    if (this->currentDirectory->isNameAvailable(fullFileName)) {
        FileNode* T = FileNode::Create(name, extension, this->currentPath + SEPARATOR + fullFileName);
        this->currentDirectory->AddChild(T);
        return true;
    }
    else {

        CallBack("\033[31m目录" + this->currentPath + "已有" + fullFileName +"\033[0m"+"\n");
    
        return false;
    }
}

bool FileManager::HandleCreateFile(std::string name, std::string extension, std::string path) {
    path = getAbsolutePath(path); // 确保路径为绝对路径（已有逻辑，保留）

    // 查找目标目录节点（已有逻辑，保留）
    DirectoryNode* T1 = dynamic_cast<DirectoryNode*>(FindNodeByPath(path));
    if (T1 == nullptr) 
    {
        CallBack("\033[31m错误: 路径" + path + "不存在\033[0m\n");
        return false;
    }

    // 检查文件名是否可用（已有逻辑，保留）
    std::string fullFileName = name + extension; //变量名像链家性说的那样驼峰命名
    if (!T1->isNameAvailable(fullFileName)) 
    {    //这个比源代码更短一点，看起来更容易懂一些
        CallBack("\033[31m目录" + path + "已有" + fullFileName + "\033[0m\n");
        return false;
    }

    // 关键：拼接文件路径时添加路径分隔符SEPARATOR
    std::string filePath = path + SEPARATOR + fullFileName; // 如 "C:\program" + "\" + "a.txt" → "C:\program\a.txt"
    FileNode* T2 =FileNode::Create(name, extension, filePath);
    T1->AddChild(T2);//本来想写 SetNodeInPathMap(filePath, T2); // 这个步骤在AddChild中已经处理，无需重复调用
    return true;
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
// 在FileManager的操作函数区域添加：
bool FileManager::handleRename(std::string oldPath, std::string newName) {
    oldPath = getAbsolutePath(oldPath);
    TreeNode* node = FindNodeByPath(oldPath);
    if (node == nullptr) {
        CallBack("错误: 原路径" + oldPath + "不存在\n");
        return false;
    }

    std::string parentPath = PathUtils::getDirectory(oldPath);
    DirectoryNode* parentNode = dynamic_cast<DirectoryNode*>(FindNodeByPath(parentPath));
    if (parentNode == nullptr) {
        CallBack("错误: 父目录不存在\n");
        return false;
    }

    TreeNode* tempNode = nullptr;
    std::string newTempPath = PathUtils::join(parentPath, newName);

    if (node->GetType() == TreeNodeType::DIRECTORY) {
        tempNode = new DirectoryNode(newName, newTempPath);
    }
    else {
        std::string oldFullName = node->GetName() + treeNodeTypeToString(node->GetType()).first;
        std::string ext = PathUtils::getExtension(oldFullName);
        std::string newFileFullPath = newTempPath + ext;
        tempNode = new FileNode(newName, node->GetType(), newFileFullPath);
    }

    if (!parentNode->isNameAvailable(newName)) {
        CallBack("错误: 父目录中已存在同名同类型的节点\n");
        delete tempNode;
        return false;
    }
    delete tempNode;

    std::string newPath = PathUtils::join(parentPath, newName);
    if (node->GetType() != TreeNodeType::DIRECTORY) {
        std::string oldFullName = node->GetName() + treeNodeTypeToString(node->GetType()).first;
        std::string ext = PathUtils::getExtension(oldFullName);
        newPath += ext;
    }

    RemoveNodeFromPathMap(oldPath);
    RemoveNodeFromPathMap(oldPath + SEPARATOR); 

    node->SetName(newName);
    node->SetPath(newPath);

    SetNodeInPathMap(newPath, node);
    if (node->GetType() == TreeNodeType::DIRECTORY) {
        SetNodeInPathMap(newPath + SEPARATOR, node); 
    }

    if (node->GetType() == TreeNodeType::DIRECTORY) {
        DirectoryNode* dirNode = dynamic_cast<DirectoryNode*>(node);
        updateChildPaths(dirNode, oldPath, newPath);
    }

    CallBack("成功: 重命名为" + newName + "\n");
    return true;
}
void FileManager::updateChildPaths(DirectoryNode* dirNode, std::string oldParentPath, std::string newParentPath) {
    for (TreeNode* child : dirNode->GetChild()) {
        std::string oldChildPath = child->GetPath();
        std::string newChildPath = oldChildPath.replace(0, oldParentPath.length(), newParentPath);

        RemoveNodeFromPathMap(oldChildPath);
        child->SetPath(newChildPath);
        SetNodeInPathMap(newChildPath, child);

        if (child->GetType() == TreeNodeType::DIRECTORY) {
            updateChildPaths(dynamic_cast<DirectoryNode*>(child), oldParentPath, newParentPath);
        }
    }
}
#pragma endregion
#pragma region 纯工具
DirectoryNode* FileManager::mkdirRecursive(std::string path) {

	DirectoryNode* node = dynamic_cast<DirectoryNode*>(FindNodeByPath(path));//查找该目录是否存在
	if (node == nullptr) {//不存在该目录 则创建
		auto Path = PathUtils::split(path);//分割路径
		auto dirPath = Path.first;//目录路径
		auto name = Path.second;//目录名称
		node = new DirectoryNode(name, path);//创建目录节点
		mkdirRecursive(dirPath)->AddChild(node);//递归创建上级目录 并添加子节点
    }
    return node;  
}
std::string FileManager::getAbsolutePath(std::string path) {
    if (PathUtils::isAbsolute(path)) {
        if (path[0] == SEPARATOR) {
            path = PathUtils::join(this->rootDirectory->GetPath(),path);
        }
    }
    else{
        path = PathUtils::join(this->currentPath, path);
    }
	return path;
}
#pragma endregion


