//�ڶ�

#pragma once
#include <string>
#include "NodeManager.h"
class FileManager {

private:
	NodeManager* m_NM;
public:
	//�Զ���������
	std::string name;

	FileManager();
	FileManager(std::string name);
	void Show();
	NodeManager* getNM() { return this->m_NM; }

};