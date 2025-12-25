#pragma once
#include "FileSystemCore.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
class CMDManager {
private:
    // 单例模式
    CMDManager();
    CMDManager(const CMDManager&) = delete;
    CMDManager& operator=(const CMDManager&) = delete;

    FileSystemCore fs_core;    // 文件系统核心实例
    std::string output_buffer; // 输出缓冲区

    // 快捷目录跳转相关
    std::unordered_map<std::string, std::string> shortcuts; // 标记->路径映射
    const std::string SHORTCUTS_FILE = "shortcuts.txt";     // 快捷目录文件

    // 命令映射表
    std::unordered_map<std::string,
        std::function<void(const std::vector<std::string>&)>>
        command_map;

    // 初始化命令映射
    void initCommands();

    // 命令处理函数
    // 显示帮助信息
    void handleHelp(const std::vector<std::string>& tokens);
    // 列出目录内容
    void handleDir(const std::vector<std::string>& tokens);
    // 创建目录
    void handleMkdir(const std::vector<std::string>& tokens);
    // 创建空文件
    void handleTouch(const std::vector<std::string>& tokens);
    // 删除文件或目录
    void handleDel(const std::vector<std::string>& tokens);
    // 移动或复制文件/目录
    void handleMove(const std::vector<std::string>& tokens);
    // 重命名文件或目录
    void handleRename(const std::vector<std::string>& tokens);
    // 切换当前目录
    void handleCd(const std::vector<std::string>& tokens);
    // 清屏
    void handleCls(const std::vector<std::string>& tokens);
    // 显示当前目录
    void handlePwd(const std::vector<std::string>& tokens);
    // 检查路径是否存在
    void handleExists(const std::vector<std::string>& tokens);
    // 快捷目录管理
    void handleMark(const std::vector<std::string>& tokens);
    // 运行可执行文件
    void handleRun(const std::vector<std::string>& tokens);
    // 打开文件（使用系统默认程序）
    void handleOpen(const std::vector<std::string>& tokens);

    // 工具函数
    // 解析命令为令牌列表
    std::vector<std::string> parseCommand(const std::string& cmd);
    // 将字符串转换为小写
    static std::string toLower(const std::string& str);
    // 显示错误信息
    void showError(const std::string& msg);

    // 快捷目录工具函数
    // 从文件加载快捷目录映射
    void loadShortcuts();
    // 保存快捷目录映射到文件
    void saveShortcuts();
    // 展开快捷标记：将${标记}替换为实际路径
    std::string expandShortcut(const std::string& token);

public:
    // 单例访问点
    // 返回：CMDManager的唯一实例
    static CMDManager& getInstance() {
        static CMDManager instance;
        return instance;
    }

    // 主运行循环
    // 启动命令行界面并处理用户输入
    void run();

    // 执行单条命令（用于测试）
    // 参数：command - 要执行的命令字符串
    void executeCommand(const std::string& command);

    // 输出管理
    // 显示输出缓冲区内容
    void Show();
    // 向输出缓冲区追加文本
    // 参数：text - 要追加的文本内容
    void appendOutput(const std::string& text);
    // 清空输出缓冲区
    void clearOutput();
    // 获取输出缓冲区内容
    // 返回：输出缓冲区的字符串引用
    const std::string& getOutput() const;
    // 显示输出缓冲区内容（同Show）
    void showOutput();
};