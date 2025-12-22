#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <algorithm>
#include "FileSystemCore.h"

class CMDManager {
private:
    // 单例模式
    CMDManager();
    CMDManager(const CMDManager&) = delete;
    CMDManager& operator=(const CMDManager&) = delete;

    FileSystemCore fs_core;  // 文件系统核心实例
    std::string output_buffer;  // 输出缓冲区

    // 命令映射表
    std::unordered_map<std::string,
        std::function<void(const std::vector<std::string>&)>> command_map;

    // 初始化命令映射
    void initCommands();

    // 命令处理函数
    void handleHelp(const std::vector<std::string>& tokens);
    void handleDir(const std::vector<std::string>& tokens);
    void handleMkdir(const std::vector<std::string>& tokens);
    void handleTouch(const std::vector<std::string>& tokens);
    void handleDel(const std::vector<std::string>& tokens);
    void handleMove(const std::vector<std::string>& tokens);
    void handleRename(const std::vector<std::string>& tokens);
    void handleCd(const std::vector<std::string>& tokens);
    void handleCls(const std::vector<std::string>& tokens);
    void handlePwd(const std::vector<std::string>& tokens);
    void handleExists(const std::vector<std::string>& tokens);

    // 工具函数
    static std::vector<std::string> parseCommand(const std::string& cmd);
    static std::string toLower(const std::string& str);
    void showError(const std::string& msg);

public:
    // 单例访问点
    static CMDManager& getInstance() {
        static CMDManager instance;
        return instance;
    }

    // 主运行循环
    void run();

    // 执行单条命令（用于测试）
    void executeCommand(const std::string& command);

    // 输出管理
    void appendOutput(const std::string& text);
    void clearOutput();
    const std::string& getOutput() const;
    void showOutput();
};