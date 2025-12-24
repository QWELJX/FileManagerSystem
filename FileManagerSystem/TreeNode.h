// 树节点类

#pragma once
#include <vector>
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
	
	TreeNode(std::string name, TreeNodeType type, std::string path);//���캯��
	TreeNode(std::string name, TreeNodeType type);//���캯��
	TreeNode(std::string name);//���캯��
	virtual ~TreeNode();
	//��Ҫ�̳еķ���
	virtual void Show() = 0;//���麯�� ��ʾ��Ϣ

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
	//���캯��
	
	
public:
	DirectoryNode(std::string name, std::string path);
	DirectoryNode(std::string name);
	~DirectoryNode();
	//��дShow����
	void Show() override;

	bool isNameAvailable(std::string fileName);
	//�ж������Ƿ����
	
	//�����ӽڵ�
	void AddChild(TreeNode* child);
	//��ȡ�ӽڵ�����
	size_t GetChildrenSize();
	//��ȡ�ӽڵ�
	TreeNode* GetOneChild(size_t index);
	//ɾ���ӽڵ�
	bool RemoveChild(const std::string& childName);
	bool RemoveChild(TreeNode* p);
	const std::vector<TreeNode*>& GetChild() const;

};
class FileNode : public TreeNode {
private:
	FileNode(std::string name,TreeNodeType type,std::string path);
	FileNode(std::string name,TreeNodeType type);
public:
	static FileNode* Create(std::string name, std::string extension, std::string path);
	~FileNode();
	void Show() override;
};

