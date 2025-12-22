#include "CMDManager.h"

// 构造函数：初始化命令映射
CMDManager::CMDManager() {
    initCommands();
    appendOutput("文件管理器已启动。输入 'help' 查看命令列表。\n");
    appendOutput("当前目录: " + fs_core.getCurrentPath().string() + "\n");
}

void CMDManager::initCommands() {
    command_map = {
        {"help",    [this](auto& t) { handleHelp(t); }},
        {"dir",     [this](auto& t) { handleDir(t); }},
        {"ls",      [this](auto& t) { handleDir(t); }},  // 别名
        {"mkdir",   [this](auto& t) { handleMkdir(t); }},
        {"touch",   [this](auto& t) { handleTouch(t); }},
        {"del",     [this](auto& t) { handleDel(t); }},
        {"rm",      [this](auto& t) { handleDel(t); }},  // 别名
        {"move",    [this](auto& t) { handleMove(t); }},
        {"mv",      [this](auto& t) { handleMove(t); }}, // 别名
        {"rename",  [this](auto& t) { handleRename(t); }},
        {"cd",      [this](auto& t) { handleCd(t); }},
        {"cls",     [this](auto& t) { handleCls(t); }},
        {"clear",   [this](auto& t) { handleCls(t); }},  // 别名
        {"pwd",     [this](auto& t) { handlePwd(t); }},
        {"exists",  [this](auto& t) { handleExists(t); }}
    };
}

// 解析命令为令牌
std::vector<std::string> CMDManager::parseCommand(const std::string& cmd) {
    std::vector<std::string> tokens;
    std::istringstream iss(cmd);
    std::string token;

    while (iss >> token) {
        // 处理带引号的参数
        if (!token.empty() && token.front() == '"') {
            std::string quoted;
            quoted = token.substr(1);

            while (iss >> token) {
                quoted += " " + token;
                if (token.back() == '"') {
                    quoted.pop_back();  // 移除结尾引号
                    break;
                }
            }
            tokens.push_back(quoted);
        }
        else {
            tokens.push_back(token);
        }
    }
    return tokens;
}

// 转换为小写
std::string CMDManager::toLower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

// 显示错误信息
void CMDManager::showError(const std::string& msg) {
    appendOutput("[错误] " + msg + "\n");
}

// === 命令处理函数实现 ===

void CMDManager::handleHelp(const std::vector<std::string>&) {
    appendOutput("可用命令:\n");
    appendOutput("  help              - 显示此帮助信息\n");
    appendOutput("  dir, ls           - 列出当前目录内容\n");
    appendOutput("  mkdir <目录名>    - 创建新目录\n");
    appendOutput("  touch <文件名>    - 创建新文件\n");
    appendOutput("  del <路径>        - 删除文件或目录\n");
    appendOutput("  move <源> <目标>  - 移动/复制文件或目录\n");
    appendOutput("  rename <旧> <新>  - 重命名文件或目录\n");
    appendOutput("  cd <路径>         - 切换当前目录\n");
    appendOutput("  cls, clear        - 清屏\n");
    appendOutput("  pwd               - 显示当前目录\n");
    appendOutput("  exists <路径>     - 检查路径是否存在\n");
    appendOutput("  exit, quit        - 退出程序\n");
}

void CMDManager::handleDir(const std::vector<std::string>& tokens) {
    bool detailed = false;
    if (tokens.size() > 1 && (tokens[1] == "-l" || tokens[1] == "/l")) {
        detailed = true;
    }
    appendOutput(fs_core.listDirectory(detailed));
}

void CMDManager::handleMkdir(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        showError("用法: mkdir <目录名>");
        return;
    }

    if (fs_core.createDirectory(tokens[1])) {
        appendOutput("目录创建成功: " + tokens[1] + "\n");
    }
}

void CMDManager::handleTouch(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        showError("用法: touch <文件名>");
        return;
    }

    if (fs_core.createFile(tokens[1])) {
        appendOutput("文件创建成功: " + tokens[1] + "\n");
    }
}

void CMDManager::handleDel(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        showError("用法: del <路径> [/r]");
        return;
    }

    bool recursive = (tokens.size() > 2 && (tokens[2] == "/r" || tokens[2] == "-r"));

    std::cout << "确认删除 " << tokens[1] << "? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();  // 清除换行符

    if (confirm == 'y' || confirm == 'Y') {
        if (fs_core.deletePath(tokens[1], recursive)) {
            appendOutput("删除成功: " + tokens[1] + "\n");
        }
    }
    else {
        appendOutput("删除已取消\n");
    }
}

void CMDManager::handleMove(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3) {
        showError("用法: move <源路径> <目标路径>");
        return;
    }

    if (fs_core.movePath(tokens[1], tokens[2])) {
        appendOutput("移动成功: " + tokens[1] + " -> " + tokens[2] + "\n");
    }
}

void CMDManager::handleRename(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3) {
        showError("用法: rename <旧名称> <新名称>");
        return;
    }

    if (fs_core.renamePath(tokens[1], tokens[2])) {
        appendOutput("重命名成功: " + tokens[1] + " -> " + tokens[2] + "\n");
    }
}

void CMDManager::handleCd(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        // 显示当前目录
        appendOutput("当前目录: " + fs_core.getCurrentPath().string() + "\n");
        return;
    }

    std::string target = tokens[1];
    if (target == "..") {
        target = fs_core.getParentPath();
    }
    else if (target == ".") {
        return;  // 保持当前目录
    }

    if (fs_core.setCurrentPath(target)) {
        appendOutput("目录已切换到: " + fs_core.getCurrentPath().string() + "\n");
    }
}

void CMDManager::handleCls(const std::vector<std::string>&) {
    FileSystemCore::clearScreen();
    clearOutput();
    appendOutput("屏幕已清空。当前目录: " + fs_core.getCurrentPath().string() + "\n");
}

void CMDManager::handlePwd(const std::vector<std::string>&) {
    appendOutput("当前目录: " + fs_core.getCurrentPath().string() + "\n");
}

void CMDManager::handleExists(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        showError("用法: exists <路径>");
        return;
    }

    if (fs_core.pathExists(tokens[1])) {
        appendOutput("路径存在: " + tokens[1] + "\n");
    }
    else {
        appendOutput("路径不存在: " + tokens[1] + "\n");
    }
}

// 输出管理
void CMDManager::appendOutput(const std::string& text) {
    output_buffer += text;
}

void CMDManager::clearOutput() {
    output_buffer.clear();
}

const std::string& CMDManager::getOutput() const {
    return output_buffer;
}

void CMDManager::showOutput() {
    std::cout << output_buffer;
    clearOutput();
}

// 执行单条命令
void CMDManager::executeCommand(const std::string& command) {
    auto tokens = parseCommand(command);
    if (tokens.empty()) return;

    std::string cmd_name = toLower(tokens[0]);

    if (cmd_name == "exit" || cmd_name == "quit") {
        appendOutput("再见！\n");
        showOutput();
        exit(0);
    }

    auto it = command_map.find(cmd_name);
    if (it != command_map.end()) {
        it->second(tokens);
    }
    else {
        showError("未知命令: " + cmd_name);
        appendOutput("输入 'help' 查看可用命令。\n");
    }
}

// 主运行循环
void CMDManager::run() {
    std::string input;

    while (true) {
        // 显示提示符
        std::cout << "\n" << fs_core.getCurrentPath().string() << "> ";

        // 获取用户输入
        std::getline(std::cin, input);

        // 执行命令
        executeCommand(input);

        // 显示输出
        showOutput();
    }
}