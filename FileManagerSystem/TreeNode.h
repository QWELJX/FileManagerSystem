//第四个

#pragma once
#include<vector>
#include "TreeNodeType.h"
class FileManager;
class TreeNode {
private:
	//FileManager* m_Fm;//指针负责管理所有FileNode的节点，//不再去维护指针了
	//节点名字
	std::string name;
	//路径
	std::string path;
	//类型
	TreeNodeType type;
	//大小
	size_t size;
	//放在私有里面 避免在类外部被随意修改
public:
	
	TreeNode(std::string name, TreeNodeType type, std::string path);//构造函数
	TreeNode(std::string name, TreeNodeType type);//构造函数
	TreeNode(std::string name);//构造函数
	virtual ~TreeNode();
	//需要继承的方法
	virtual void Show() = 0;//纯虚函数 显示信息

	//获取方法
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
	std::vector<TreeNode*> children;//放在类里 避免在类外部被随意修改
	//构造函数
	
	
public:
	DirectoryNode(std::string name, std::string path);
	DirectoryNode(std::string name);
	~DirectoryNode();
	//重写Show方法
	void Show() override;

	bool isNameAvailable(std::string fileName);
	//判断名字是否可用
	
	//添加子节点
	void AddChild(TreeNode* child);
	//获取子节点数量
	size_t GetChildrenSize();
	//获取子节点
	TreeNode* GetOneChild(size_t index);
	//删除子节点
	bool RemoveChild(const std::string& childName);
	bool RemoveChild(TreeNode* p);
	const std::vector<TreeNode*>& GetChild() const;

};
class FileNode : public TreeNode {
public:
	FileNode(std::string name,TreeNodeType type,std::string path);
	FileNode(std::string name,TreeNodeType type);
public:
	static FileNode* Create(std::string name, std::string extension, std::string path);
	~FileNode();
	void Show() override;
};

