//���ĸ�

#pragma once
#include<vector>
#include "TreeNodeType.h"
class FileManager;
class TreeNode {
private:
	//FileManager* m_Fm;//ָ�븺���������FileNode�Ľڵ㣬//����ȥά��ָ����
	//�ڵ�����
	std::string name;
	//·��
	std::string path;
	//����
	TreeNodeType type;
	//��С
	size_t size;
	//����˽������ ���������ⲿ�������޸�
public:
	
	TreeNode(std::string name, TreeNodeType type,std::string path);
	TreeNode(std::string name, TreeNodeType type );
	TreeNode(std::string name);
	//��Ҫ�̳еķ���
	virtual void Show() = 0;

	//��ȡ����
	std::string GetName();
	std::string GetPath();
	TreeNodeType GetType();
	size_t GetSize();
	void SetName(std::string n);
	void SetPath(std::string p);
	void SetType(TreeNodeType t);
	void SetSize(size_t s);
};
class DirectoryNode : public TreeNode {
private:
	std::vector<TreeNode*> children;//�������� ���������ⲿ�������޸�
public:
	
	//���캯��
	DirectoryNode(std::string name, std::string path);
	DirectoryNode(std::string name);
	//��дShow����
	void Show() override;

	bool isNameAvailable(DirectoryNode T);
	//�ж������Ƿ����
	
	//����ӽڵ�
	void AddChild(TreeNode* child);
	//��ȡ�ӽڵ�����
	size_t GetChildrenSize();
	//��ȡ�ӽڵ�
	TreeNode* GetOneChild(size_t index);
	//ɾ���ӽڵ�
	bool RemoveChild(const std::string& childName);
	bool RemoveChild(size_t t);
	const std::vector<TreeNode*>& GetChild() const;

};
class FileNode : public TreeNode {
	FileNode(std::string name, std::string path);
	FileNode(std::string name);
	
};

