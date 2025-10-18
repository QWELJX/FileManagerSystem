
#pragma once
#include <string>
#include<unordered_map>
#include<stack>
#include "TreeNode.h"
#include "TreeNodeType.h"
#include "PathUtils.h"
class FileManager {
private:
	// ˽�й��캯��
	FileManager();
	FileManager(std::string name);
	// ��ֹ�����͸�ֵ
	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;
	//����
	DirectoryNode* rootDirectory;//���ڵ�
	DirectoryNode* currentDirectory;//��ǰ�ڵ�
	std::string currentPath;//��ǰ·��
	std::unordered_map<std::string, TreeNode*> pathMap;//·����(�����ҽڵ㣬���ھ���·��)
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
	
	//std::stack<std::string> pathHistory;// ·����ʷջ��֧�ֶ༶����,�������·��//����Ҫ

	void Show();
	void CallBack(std::string);//�ļ��������ص����� ���ڸ�CMD������Ϣ
	//------------------------------------------------------------------------------------------------
	/*FileNode* SearchNode(std::string);*/
	//����
	//����ļ�
	bool handleAdd(std::string name, TreeNodeType type = TreeNodeType::DIRECTORY);
	//ɾ���ļ�
	bool handleDelete(const std::vector<std::string>& tokens);
	////��ת 
	bool handleGoto(const std::vector<std::string>& tokens);
	////����
	bool handleBack();
	//
	
};
