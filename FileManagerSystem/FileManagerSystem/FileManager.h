//�ڶ�

#pragma once
#include <string>
#include<unordered_map>
#include<stack>
#include "FileNode.h"
#include "FileNodeType.h"
#include "PathUtils.h"
class FileManager {

private:

	
public:
	
	//�Զ���������
	//std::string name;//����������//������� ���ڵ������ 

	FileNode* rootNode;//���ڵ�
	FileNode* currentNode;//��ǰ�ڵ�
	std::string currentPath;//��ǰ·��
	std::unordered_map<std::string, FileNode*> pathMap;//·����(�����ҽڵ㣬���ھ���·��)
	std::stack<std::string> pathHistory;// ·����ʷջ��֧�ֶ༶����,�������·��

	FileManager(std::string name);
	void Show();
	void CallBack(std::string);//�ļ��������ص����� ���ڸ�CMD������Ϣ
	//------------------------------------------------------------------------------------------------
	/*FileNode* SearchNode(std::string);*/
	//����
	//����ļ�
	bool handleAdd(std::string name, FileNodeType type = FileNodeType::DIRECTORY);
	//ɾ���ļ�
	bool handleDelete(const std::vector<std::string>& tokens);
	////��ת 
	bool handleGoto(const std::vector<std::string>& tokens);
	////����
	bool handleBack();
	bool isNameAvailable(std::string name);
};
