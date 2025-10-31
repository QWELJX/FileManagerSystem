
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
	    DirectoryNode* GetRootNode()const;
	    DirectoryNode* GetCurrentNode()const;
		std::string GetCurrentPath();
		TreeNode* FindNodeByPath(const std::string& path) const;
	//setter
		void SetCurrentNode(DirectoryNode* node);
		void SetCurrentPath(const std::string& path);
		void SetNodeInPathMap(const std::string& path, TreeNode* node);
	


	void Show();
	void CallBack(std::string);//�ļ��������ص����� ���ڸ�CMD������Ϣ
	//------------------------------------------------------------------------------------------------
	/*FileNode* SearchNode(std::string);*/
	//����
	//����ļ�
	bool handleMkdir(std::string name,std::string path);
	bool handleMkdir(std::string name);
	//ɾ���ļ�
	bool handleDelete(const std::vector<std::string>& tokens);
	////��ת 
	bool handleGoto(std::string path);
	////����
	bool handleBack();
	//
	
};
