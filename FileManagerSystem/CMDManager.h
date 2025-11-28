
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

    std::unordered_map<std::string,
        std::function<void(const std::vector<std::string>&)>> commandMap;

    std::string CONTENT;//展示内容
    void handleCls(const std::vector<std::string>& tokens);//清屏
    void handleMkdir(const std::vector<std::string>& tokens);//添加文件夹
	void HandleCreateFile(const std::vector<std::string>& tokens);//添加文件
    void handleDelete(const std::vector<std::string>& tokens);//删除
    void handleGoto(const std::vector<std::string>& tokens);//跳转
    //void handleBack(const std::vector<std::string>& tokens);多余
    void handleDir(const std::vector<std::string>& tokens);//!
    void handleHelp(const std::vector<std::string>& tokens);//帮助
	void handleRename(const std::vector<std::string>& tokens);//重命名
    // 工具函数
    bool isPureNumber(const std::string& str);//判断纯数字
    std::string toLower(const std::string& str);  // 添加这个声明

    void nl(int t);//换行
 
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
    
    // 获取当前内容（用于显示）
    const std::string& getContent() const;
    void clearContent();
    void appendContent(const std::string& text);
    void showContent();


};