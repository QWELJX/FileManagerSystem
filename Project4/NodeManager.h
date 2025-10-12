//����

#pragma once
#include<string>
#include<unordered_map>
#include<stack>
#include "FileNode.h"
#include "FileNodeType.h"
#include "PathUtils.h"
class FileManager;

class NodeManager {
private:
	FileManager* m_Fm;
public:
	

	FileNode* rootNode;//���ڵ�
	FileNode* currentNode;//��ǰ�ڵ�
	std::string currentPath;//��ǰ·��
	std::unordered_map<std::string, FileNode*> pathMap;//·����(�����ҽڵ㣬���ھ���·��)

	std::stack<std::string> pathHistory;// ·����ʷջ��֧�ֶ༶����,�������·��

	
	//------------------------------------------------------------------------------------------------
	NodeManager(FileManager* fm);
	
	
	
	/*FileNode* SearchNode(std::string);*/
	//����
	//����ļ�
	bool handleAdd(std::string name, FileNodeType type=FileNodeType::DIRECTORY);
	//ɾ���ļ�
	bool handleDelete(const std::vector<std::string>& tokens);
	////��ת 
	bool handleGoto(const std::vector<std::string>& tokens);
	////����
	bool handleBack();
	bool CValid(std::string name);
};
