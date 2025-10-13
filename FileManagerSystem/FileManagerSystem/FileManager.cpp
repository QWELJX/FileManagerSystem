#include<iostream>
#include<iomanip>
#include "FileManager.h"
FileManager::FileManager() {
    name = "VisualProject";
    m_NM = new NodeManager(this);


}
FileManager::FileManager(std::string name) {
    this->name = name;
    m_NM = new NodeManager(this);

};

void FileManager::Show() {
    std::cout << "**************************************************" << std::endl;

    // 表头 - 对齐
    std::cout << std::setw(6) << std::left << "序号"
        << std::setw(20) << std::left << "名称"
        << std::setw(12) << std::left << "类型"
        << std::setw(10) << std::right << "大小(B)" << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;

    // 数据行
    int i;
    for (i = 0; i < this->m_NM->currentNode->GetSize(); ++i) {
        auto child = this->m_NM->currentNode->children[i];
        std::string name = child->name + fileTypeToString(child->type).second;

        std::cout << std::setw(6) << std::left << i
            << std::setw(20) << std::left << (name.length() > 14 ? name.substr(0, 14) + "..." : name)
            << std::setw(12) << std::left << fileTypeToString(child->type).first
            << std::setw(10) << std::right << child->size << std::endl;
    }
    for (int j = 0; j < 10 - i; ++j) std::cout << std::endl;
    std::cout << std::endl << "--------------------------------------------------" << std::endl;
    std::cout << "**************************************************" << std::endl;
}