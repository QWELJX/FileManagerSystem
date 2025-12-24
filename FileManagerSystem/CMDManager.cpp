#include "CMDManager.h"
#include <limits>

// 构造函数：初始化命令映射
CMDManager::CMDManager() {
    initCommands();
    appendOutput("文件管理器已启动。输入 'help' 查看命令列表。\n");
    appendOutput("当前初始目录: " + fs_core.getCurrentPath().string() + "\n");
}

void CMDManager::initCommands() {
    command_map = { {"help", [this](auto& t) { handleHelp(t); }},
                   {"dir", [this](auto& t) { handleDir(t); }},
                   {"ls", [this](auto& t) { handleDir(t); }}, // 别名
                   {"mkdir", [this](auto& t) { handleMkdir(t); }},
                   {"md", [this](auto& t) { handleMkdir(t); }},//别名
                   {"touch", [this](auto& t) { handleTouch(t); }},
                   {"del", [this](auto& t) { handleDel(t); }},
                   {"rm", [this](auto& t) { handleDel(t); }}, // 别名
                   {"move", [this](auto& t) { handleMove(t); }},
                   {"mv", [this](auto& t) { handleMove(t); }}, // 别名
                   {"rename", [this](auto& t) { handleRename(t); }},
                   {"cd", [this](auto& t) { handleCd(t); }},
                   {"cls", [this](auto& t) { handleCls(t); }},
                   {"clear", [this](auto& t) { handleCls(t); }}, // 别名
                   {"pwd", [this](auto& t) { handlePwd(t); }},
                   {"exists", [this](auto& t) { handleExists(t); }} };
}

// 解析命令为令牌
std::vector<std::string> CMDManager::parseCommand(const std::string& cmd) {
    std::vector<std::string> tokens;
    std::istringstream iss(cmd);
    std::string token;
    const std::size_t MAX_TOKEN_LEN = 4096;

    while (iss >> token) {
        // 处理带引号的参数
        if (!token.empty() && token.front() == '"') {
            std::string quoted;
            quoted = token.substr(1);

            bool closed = false;

            // 当前 token 同时包含首尾引号的情况
            if (!quoted.empty() && quoted.back() == '"') {
                quoted.pop_back(); // 移除结尾引号
                closed = true;
            }
            else {
                while (iss >> token) {
                    quoted += " " + token;
                    if (!token.empty() && token.back() == '"') {
                        quoted.pop_back(); // 移除结尾引号
                        closed = true;
                        break;
                    }
                    if (quoted.size() > MAX_TOKEN_LEN) {
                        break;
                    }
                }
            }

            // 如果没有正常闭合，这里仍然把已有内容作为一个整体参数交给后续处理
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
const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";
void CMDManager::showError(const std::string& msg) {
    appendOutput(RED + "[错误] " + msg + RESET + "\n");
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
    int n = tokens.size();
    if (n == 1) {
        appendOutput(fs_core.listDirectory());
    }
    else if (n == 2) {
        if (tokens[1] == "/s")
            appendOutput(fs_core.listDirectory(false, true));
        else if (tokens[1] == "/d")
            appendOutput(fs_core.listDirectory(true, false));
        else showError(tokens[1] + "符号未知");
    }
    else {
        showError("暂不支持此功能");
    }

}

void CMDManager::handleMkdir(const std::vector<std::string>& tokens) {
    int n = tokens.size();
    if (n <= 1) {
        showError("用法: mkdir <目录名>");
        return;
    }
    else if (n == 2) {
        if (!fs_core.createDirectory(tokens[1])) {
            showError("目录创建失败: " + fs_core.getLastError());
        }
    }
    else if (n == 3) {
        if (!fs_core.createDirectory(tokens[2], (tokens[1] == "/p" || tokens[1] == "-p"))) {
            showError("目录创建失败: " + fs_core.getLastError());
        }
    }
    else {
        showError("用法: mkdir [/p] <目录名>");
    }
    appendOutput("目录创建成功: " + tokens[1] + "\n");

}

void CMDManager::handleTouch(const std::vector<std::string>& tokens) {
    if (tokens.size() != 2) {
        showError("用法: touch <文件名>");
        return;
    }

    if (!fs_core.createFile(tokens[1])) {
        showError("文件创建失败: " + fs_core.getLastError());
        return;
    }

    appendOutput("文件创建成功: " + tokens[1] + "\n");
}

void CMDManager::handleDel(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2 || tokens.size() > 3) {
        showError("用法: del <路径> [/r]");
        return;
    }

    bool recursive = (tokens.size() > 2 && (tokens[2] == "/r" || tokens[2] == "-r"));

    std::cout << "确认删除 " << tokens[1] << "? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
        '\n'); // 清除本行剩余输入

    if (confirm != 'y' && confirm != 'Y') {
        appendOutput("删除已取消\n");
        return;
    }

    if (!fs_core.deletePath(tokens[1], recursive)) {
        showError("删除失败: " + fs_core.getLastError());
        return;
    }

    appendOutput("删除成功: " + tokens[1] + "\n");
}

void CMDManager::handleMove(const std::vector<std::string>& tokens) {
    if (tokens.size() != 3) {
        showError("用法: move <源路径> <目标路径>");
        return;
    }

    if (!fs_core.movePath(tokens[1], tokens[2])) {
        showError("移动失败: " + fs_core.getLastError());
        return;
    }

    appendOutput("移动成功: " + tokens[1] + " -> " + tokens[2] + "\n");
}

void CMDManager::handleRename(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3) {
        showError("用法: rename <旧名称> <新名称>");
        return;
    }

    if (!fs_core.renamePath(tokens[1], tokens[2])) {
        showError("重命名失败: " + fs_core.getLastError());
        return;
    }

    appendOutput("重命名成功: " + tokens[1] + " -> " + tokens[2] + "\n");
}

void CMDManager::handleCd(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        // 模仿cmd 不响应
        return;
    }

    std::string target = tokens[1];
    if (target == "..") {
        target = fs_core.getParentPath();
    }
    else if (target == ".") {
        return; // 保持当前目录
    }

    if (!fs_core.setCurrentPath(target)) {
        showError("切换目录失败: " + fs_core.getLastError());
        return;
    }
    appendOutput("目录已切换到: " + fs_core.getCurrentPath().string() + "\n");
}

void CMDManager::handleCls(const std::vector<std::string>&) {
    FileSystemCore::clearScreen();
    clearOutput();
    appendOutput("屏幕已清空。当前目录: " + fs_core.getCurrentPath().string() +
        "\n");
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
void CMDManager::Show() {
    std::cout << "==============================================================="
        "=================\n";
    std::cout << "     C++ 文件管理器 \n";
    std::cout << "     基于 std::filesystem\n";
    std::cout << "==============================================================="
        "=================\n";
    std::cout << fs_core.listDirectory(true, false);
    std::cout << "==============================================================="
        "=================\n";
    showOutput();
}
void CMDManager::appendOutput(const std::string& text) {
    output_buffer += text;
}

void CMDManager::clearOutput() { output_buffer.clear(); }

const std::string& CMDManager::getOutput() const { return output_buffer; }

void CMDManager::showOutput() { std::cout << output_buffer; }

// 执行单条命令
void CMDManager::executeCommand(const std::string& command) {
    auto tokens = parseCommand(command);
    if (tokens.empty())
        return;

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

        appendOutput("\n" + fs_core.getCurrentPath().string() + "> ");
        Show();

        // 获取用户输入
        std::getline(std::cin, input);
        // 处理流
        appendOutput(input + "\n");
        // 执行命令

        executeCommand(input);

        FileSystemCore::clearScreen();
        /*  system("cls");*/
    }
}