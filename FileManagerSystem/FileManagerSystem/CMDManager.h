
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

    // 命令处理函数

    void handleRgt(const std::vector<std::string>& tokens);//注册用户
	void handleLogin(const std::vector<std::string>& tokens);//登录用户
    void handleCls(const std::vector<std::string>& tokens);//清屏
    void handleAdd(const std::vector<std::string>& tokens);//添加
    void handleDelete(const std::vector<std::string>& tokens);//删除
    void handleGoto(const std::vector<std::string>& tokens);//跳转
    void handleBack(const std::vector<std::string>& tokens);//回退
    void handleSet(const std::vector<std::string>& tokens);//设置文件权限
    void handleHelp(const std::vector<std::string>& tokens);//帮助

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
    const std::string& getContent() const { return CONTENT; }
    void clearContent() { CONTENT.clear(); }
    void appendContent(const std::string& text) {CONTENT += text;}
    void showContent() { std::cout << this->getContent(); }


};