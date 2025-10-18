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
	//权限
	FilePermission permission;
	//类型
	TreeNodeType type;
	//大小
	size_t size;
	//放在私有里面 避免在类外部被随意修改
public:
	
	//删去指针 FileNode* m_Fm;//指向文件管理器的指针
	//构造函数
	TreeNode(std::string name, FileNodeType type , FilePermission permission);
	//需要继承的方法
	virtual void Show() = 0;//搞成纯虚函数 方便多态
	//获取方法
	std::string GetName() { return name; }
	std::string GetPath() { return path; }
	FilePermission GetPermission() { return permission; }
	FileNodeType GetType() { return type; }
	size_t GetSize() { return size; }
	


	
};
class DirectoryNode : public TreeNode {
private:
	std::vector<TreeNode*> children;//放在类里 避免在类外部被随意修改
public:
	
	//构造函数
	DirectoryNode(std::string name, FilePermission permission = FilePermission::FULL_CONTROL)
		:TreeNode(name, FileNodeType::DIRECTORY, permission) {

	}
	//重写Show方法
	void Show() override;
	//判断名字是否可用
	bool isNameAvailable(std::string name);
	//添加子节点
	void AddChild(TreeNode* child) {
		children.push_back(child);
	}
	//获取子节点数量
	size_t GetChildrenSize() { return children.size(); }
	//获取子节点
	TreeNode* GetChild(size_t index);/* {
		if (index < children.size()) {
			return children[index];
		}
		return nullptr;
	}*/
	//删除子节点
	bool RemoveChild(const std::string& childName);

};
class NotDirectoryNode : public TreeNode {

	//非文件节点不应该有children 所以分开两个类
};

