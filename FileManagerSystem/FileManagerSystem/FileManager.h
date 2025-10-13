//第二

#pragma once
#include <string>
#include "NodeManager.h"
class FileManager {

private:
	NodeManager* m_NM;
public:
	//自定义命令行
	std::string name;

	FileManager();
	FileManager(std::string name);
	void Show();
	NodeManager* getNM() { return this->m_NM; }

};