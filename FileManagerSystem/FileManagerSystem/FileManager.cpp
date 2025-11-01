
#include "FileManager.h"
#include "CMDManager.h"
#include <functional>

#pragma region ���캯��
FileManager::FileManager() {
   

    this->rootDirectory = new DirectoryNode("C:","C:");
    this->currentDirectory = rootDirectory;
	this->currentPath ="C:";
	this->SetNodeInPathMap(currentPath, rootDirectory);
	/*this->rootDirectory->AddChild(new DirectoryNode("users",currentPath+SEPARATOR+"user"));
	this->rootDirectory->AddChild(new DirectoryNode("program files", currentPath + SEPARATOR + "user"));*/
 
};
#pragma endregion

#pragma region ��������

bool FileManager::handleMkdir(std::string name) {
    DirectoryNode* T = new DirectoryNode(name, this->currentPath + SEPARATOR + name);
    if (this->currentDirectory->isNameAvailable(T)) {
        this->currentDirectory->AddChild(T);
		return true;
    }
    else {
       
		CallBack("��ǰĿ¼����"+T->GetName() + "�ļ���\n");
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
            CallBack("����: Ŀ�겻��Ŀ¼\n");
			return false;
        }
    }
    else {
        CallBack("����: ·��"+path+"������\n");
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
				CallBack("����: ɾ��ʧ��\n");
            }
        }

    }
    else {
		CallBack("����: ·��" + path + "������\n");
    }
}
bool FileManager::HandleCreateFile(std::string name,std::string extension) {
	FileNode* T = new FileNode(name,stringToTreeNodeType(extension), this->currentPath + SEPARATOR + name + extension);
    if (this->currentDirectory->isNameAvailable(T)) {
        this->currentDirectory->AddChild(T);
        return true;
    }
    else {

        CallBack("��ǰĿ¼����" + T->GetName() +extension+ "\n");
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
            CallBack("Ŀ¼" + path + "����" + T2->GetName() + extension + "\n");
            delete T2;
            return false;
		}
    }
    else {
        CallBack("����: ·��" + path + "������\n");
		return false;
    }
   
}

#pragma endregion

#pragma region �ӿڷ�װ
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
#pragma region ��Ϣ���߽ӿ�
void FileManager::Show() {
    this->currentDirectory->Show();

}
void FileManager::CallBack(std::string content) {
    CMDManager::getInstance().appendContent(content);
}
#pragma endregion
#pragma region ������
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


