
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
	FileManager(std::string name);
	// 禁止拷贝和赋值
	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;
	//属性
	DirectoryNode* rootDirectory;//根节点
	DirectoryNode* currentDirectory;//当前节点
	std::string currentPath;//当前路径
	std::unordered_map<std::string, TreeNode*> pathMap;//路径表(快速找节点，利于绝对路径)
public:
	static FileManager& getInstance() {
		static FileManager instance;
		return instance;
	}
	//getter
	DirectoryNode* GetRootNode()const { return rootDirectory; }
	DirectoryNode* GetCurrentNode()const { return currentDirectory; }
	std::string GetCurrentPath() { return currentPath; }
	TreeNode* FindNodeByPath(const std::string& path) const {
		auto it = pathMap.find(path);
		return (it != pathMap.end()) ? it->second : nullptr;
	}
	//setter
	void SetCurrentNode(DirectoryNode* node) { currentDirectory = node; }
	void SetCurrentPath(const std::string& path) { currentPath = path; }
	void SetNodeInPathMap(const std::string& path, TreeNode* node) { pathMap[path] = node; }
	
	//std::stack<std::string> pathHistory;// 路径历史栈，支持多级返回,利于相对路径//不需要

	void Show();
	void CallBack(std::string);//文件管理器回调函数 用于给CMD返回信息
	//------------------------------------------------------------------------------------------------
	/*FileNode* SearchNode(std::string);*/
	//操作
	//添加文件
	bool handleAdd(std::string name, TreeNodeType type = TreeNodeType::DIRECTORY);
	//删除文件
	bool handleDelete(const std::vector<std::string>& tokens);
	////跳转 
	bool handleGoto(const std::vector<std::string>& tokens);
	////回退
	bool handleBack();
	//
	
};
