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
	//Ȩ��
	FilePermission permission;
	//����
	TreeNodeType type;
	//��С
	size_t size;
	//����˽������ ���������ⲿ�������޸�
public:
	
	//ɾȥָ�� FileNode* m_Fm;//ָ���ļ���������ָ��
	//���캯��
	TreeNode(std::string name, FileNodeType type , FilePermission permission);
	//��Ҫ�̳еķ���
	virtual void Show() = 0;//��ɴ��麯�� �����̬
	//��ȡ����
	std::string GetName() { return name; }
	std::string GetPath() { return path; }
	FilePermission GetPermission() { return permission; }
	FileNodeType GetType() { return type; }
	size_t GetSize() { return size; }
	


	
};
class DirectoryNode : public TreeNode {
private:
	std::vector<TreeNode*> children;//�������� ���������ⲿ�������޸�
public:
	
	//���캯��
	DirectoryNode(std::string name, FilePermission permission = FilePermission::FULL_CONTROL)
		:TreeNode(name, FileNodeType::DIRECTORY, permission) {

	}
	//��дShow����
	void Show() override;
	//�ж������Ƿ����
	bool isNameAvailable(std::string name);
	//����ӽڵ�
	void AddChild(TreeNode* child) {
		children.push_back(child);
	}
	//��ȡ�ӽڵ�����
	size_t GetChildrenSize() { return children.size(); }
	//��ȡ�ӽڵ�
	TreeNode* GetChild(size_t index);/* {
		if (index < children.size()) {
			return children[index];
		}
		return nullptr;
	}*/
	//ɾ���ӽڵ�
	bool RemoveChild(const std::string& childName);

};
class NotDirectoryNode : public TreeNode {

	//���ļ��ڵ㲻Ӧ����children ���Էֿ�������
};

