//第一

#pragma once
#include <iostream> 
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
//#include "FileManager.h"
// 使用前向声明替代直接包含，避免循环依赖
class FileManager;

class CMDManager {
private:
    // 私有构造函数
    CMDManager();

    // 禁止拷贝和赋值
    CMDManager(const CMDManager&) = delete;
    CMDManager& operator=(const CMDManager&) = delete;

    FileManager* m_Fm;

    std::unordered_map<std::string,
        std::function<void(const std::vector<std::string>&)>> commandMap;

    std::string CONTENT;
    std::string DIR;

    // 命令处理函数
    void handleRgt(const std::vector<std::string>& tokens);
    void handleCls(const std::vector<std::string>& tokens);
    void handleBack(const std::vector<std::string>& tokens);
    void handleAdd(const std::vector<std::string>& tokens);
    void handleDelete(const std::vector<std::string>& tokens);
    void handleGoto(const std::vector<std::string>& tokens);
    void handleList(const std::vector<std::string>& tokens);
    void handleHelp(const std::vector<std::string>& tokens);

    // 工具函数
    bool isPureNumber(const std::string& str);
    std::string toLower(const std::string& str);  // 添加这个声明
    void duiQi(size_t t);
public:
    // 获取单例实例
    static CMDManager& getInstance() {
        static CMDManager instance;
        return instance;
    }

    // 原有的公共方法
    void Run();
    void RunCMD(const std::vector<std::string>& tokens);
    void Show();

    //获取文件管理
    FileManager* getFileManager() { return this->m_Fm; }
    void setFileManager(FileManager* fm) { this->m_Fm = fm; }

    // 获取当前内容（用于显示）
    const std::string& getContent() const { return CONTENT; }
    void clearContent() { CONTENT.clear(); }
    void appendContent(const std::string& text) { 
        CONTENT += text;
        int x = 1;
    }
    void showContent() { std::cout << this->getContent(); }

    // 设置/获取当前目录
    void setDirectory(const std::string& dir) { 
        DIR = dir; 
    }
    const std::string& getDirectory() const { return DIR; }

}; 