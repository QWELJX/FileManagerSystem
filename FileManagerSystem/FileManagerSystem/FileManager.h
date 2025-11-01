
#pragma once
#include <string>
#include<unordered_map>
#include<stack>
#include "TreeNode.h"
#include "TreeNodeType.h"
#include "PathUtils.h"
class FileManager {
private:
	// 私有构造函数
	FileManager();
	// 禁止拷贝和赋值
	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;
	//属性
	DirectoryNode* rootDirectory;//根节点
	DirectoryNode* currentDirectory;//当前节点
	std::string currentPath;//当前路径
	std::unordered_map<std::string, TreeNode*> pathMap;//路径表(快速找节点，利于绝对路径)
	DirectoryNode* mkdirRecursive(std::string path);
	std::string getAbsolutePath(std::string path);
public:
	static FileManager& getInstance() {
		static FileManager instance;
		return instance;
	}
	//getter
	    DirectoryNode* GetRootNode()const;
	    DirectoryNode* GetCurrentNode()const;
		std::string GetCurrentPath();
		TreeNode* FindNodeByPath(const std::string& path) const;
	//setter
		void SetCurrentNode(DirectoryNode* node);
		void SetCurrentPath(const std::string& path);
		void SetNodeInPathMap(const std::string& path, TreeNode* node);
		void RemoveNodeFromPathMap(const std::string& path);
	


	void Show();
	void CallBack(std::string);//文件管理器回调函数 用于给CMD返回信息
	//------------------------------------------------------------------------------------------------
	/*FileNode* SearchNode(std::string);*/
	//操作
	//添加文件
	bool handleMkdir(std::string name,std::string path);
	bool handleMkdir(std::string name);
	bool HandleCreateFile(std::string name,std::string extension);
	bool HandleCreateFile(std::string name,std::string extension,std::string path);
	//删除文件
	bool handleDelete(std::string path);
	////跳转 
	bool handleGoto(std::string path);
	////回退

	//
	
};
