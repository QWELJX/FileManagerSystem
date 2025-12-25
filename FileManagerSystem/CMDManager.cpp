#include "CMDManager.h"
#include <fstream>
#include <limits>
// 构造函数：初始化命令映射
CMDManager::CMDManager() {
    initCommands();
    loadShortcuts(); // 加载快捷目录
    appendOutput("文件管理器已启动。输入 'help' 查看命令列表。\n");
    appendOutput("当前初始目录: " + fs_core.getCurrentPath().string() + "\n");
}

void CMDManager::initCommands() {
    command_map = { {"help", [this](auto& t) { handleHelp(t); }},
                   {"dir", [this](auto& t) { handleDir(t); }},
                   {"ls", [this](auto& t) { handleDir(t); }}, // 别名
                   {"mkdir", [this](auto& t) { handleMkdir(t); }},
                   {"md", [this](auto& t) { handleMkdir(t); }}, // 别名
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
                   {"exists", [this](auto& t) { handleExists(t); }},
        // 快捷目录命令
        {"mark", [this](auto& t) { handleMark(t); }},
        // 运行程序命令
        {"run", [this](auto& t) { handleRun(t); }},
        // 打开文件命令
        {"open", [this](auto& t) { handleOpen(t); }} };
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
                        quoted.pop_back(); // 秽除结尾引号
                        closed = true;
                        break;
                    }
                    if (quoted.size() > MAX_TOKEN_LEN) {
                        break;
                    }
                }
            }

            // 如果没有正常闭合，这里仍然把已有内容作为一个整体参数交给后续处理
            tokens.push_back(expandShortcut(quoted));
        }
        else {
            tokens.push_back(expandShortcut(token));
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
const std::string COLOR_RED = "\033[31m";
const std::string COLOR_RESET = "\033[0m";
void CMDManager::showError(const std::string& msg) {
    appendOutput(COLOR_RED + "[错误] " + msg + COLOR_RESET + "\n");
}

// === 命令处理函数实现 ===

void CMDManager::handleHelp(const std::vector<std::string>&) {
    appendOutput("可用命令:\n");
    appendOutput("  help                   - 显示此帮助信息\n");
    appendOutput("  dir, ls [/r/d]         - 列出当前目录内容\n");
    appendOutput("  mkdir [/r] <目录名>    - 创建新目录\n");
    appendOutput("  touch <文件名>         - 创建新文件\n");
    appendOutput("  del <路径>             - 删除文件或目录\n");
    appendOutput("  move <源> <目标>       - 移动/复制文件或目录\n");
    appendOutput("  rename <旧> <新>       - 重命名文件或目录\n");
    appendOutput("  cd <路径>              - 切换当前目录\n");
    appendOutput("  cls, clear             - 清屏\n");
    appendOutput("  pwd                    - 显示当前目录\n");
    appendOutput("  exists <路径>          - 检查路径是否存在\n");
    appendOutput("  mark <标记> <路径>     - 设置快捷标记\n");
    appendOutput("  mark del <标记>        - 删除快捷标记\n");
    appendOutput("  mark list              - 列出所有快捷标记\n");
    appendOutput("  run <exe文件>          - 运行exe文件\n");
    appendOutput("  open <txt文件>         - 用记事本打开txt文件\n");
    appendOutput("  exit, quit             - 退出程序\n");
    appendOutput("\n");
    appendOutput("快捷标记用法:\n");
    appendOutput("  mark work D:\\Code\\Project    - 设置 'work' 标记\n");
    appendOutput("  cd ${work}                    - 使用快捷标记跳转目录\n");
    appendOutput(
        "  cd ${work}/src                - 复合路径：跳转到标记目录的子目录\n");
}

void CMDManager::handleDir(const std::vector<std::string>& tokens) {
    int n = tokens.size();
    if (n == 1) {
        appendOutput(fs_core.listDirectory());
    }
    else if (n == 2) {
        if (tokens[1] == "/r" || tokens[1] == "-r")
            appendOutput(fs_core.listDirectory(false, true));
        else if (tokens[1] == "/d" || tokens[1] == "-d")
            appendOutput(fs_core.listDirectory(true, false));
        else
            showError(tokens[1] + "符号未知");
    }
    else {
        showError("暂不支持此功能");
    }
}

void CMDManager::handleMkdir(const std::vector<std::string>& tokens) {
    int n = tokens.size();
    if (n <= 1) {
        showError("用法: mkdir [/r] <目录名>");
        return;
    }
    else if (n == 2) {
        if (!fs_core.createDirectory(tokens[1])) {
            showError("目录创建失败: " + fs_core.getLastError());
        }
    }
    else if (n == 3) {
        if (!fs_core.createDirectory(tokens[2],
            (tokens[1] == "/p" || tokens[1] == "-p"))) {
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

    bool recursive =
        (tokens.size() > 2 && (tokens[2] == "/r" || tokens[2] == "-r"));

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
    appendOutput("目录已切换到: " +
        FileSystemCore::WideToUTF8(fs_core.getCurrentPath().wstring()) +
        "\n");
}

void CMDManager::handleCls(const std::vector<std::string>&) {
    FileSystemCore::clearScreen();
    clearOutput();
    appendOutput("屏幕已清空。当前目录: " +
        FileSystemCore::WideToUTF8(fs_core.getCurrentPath().wstring()) +
        "\n");
}

void CMDManager::handlePwd(const std::vector<std::string>&) {
    appendOutput("当前目录: " +
        FileSystemCore::WideToUTF8(fs_core.getCurrentPath().wstring()) +
        "\n");
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

// 处理 mark 命令：快捷标记管理
void CMDManager::handleMark(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        showError("用法: mark <标记> <路径> | mark del <标记> | mark list");
        return;
    }

    std::string subcmd = tokens[1];

    if (subcmd == "list") {
        // 显示所有快捷标记
        if (shortcuts.empty()) {
            appendOutput("暂无快捷标记。使用 'mark <标记> <路径>' 添加快捷标记\n");
            return;
        }

        appendOutput("快捷标记列表:\n");
        appendOutput("================================\n");

        for (const auto& pair : shortcuts) {
            appendOutput("  " + pair.first + " -> " + pair.second + "\n");
        }

        appendOutput("================================\n");
        appendOutput("共 " + std::to_string(shortcuts.size()) + " 个快捷标记\n");
        appendOutput(
            "提示: 可以使用 ${标记} 或 ${标记}/子路径 在命令中引用快捷路径\n");
    }
    else if (subcmd == "del") {
        // 删除快捷标记
        if (tokens.size() < 3) {
            showError("用法: mark del <标记>");
            return;
        }

        std::string mark = tokens[2];

        // 检查标记是否存在
        if (shortcuts.find(mark) == shortcuts.end()) {
            showError("快捷标记不存在: " + mark);
            return;
        }

        // 删除快捷标记
        shortcuts.erase(mark);
        saveShortcuts();
        appendOutput("快捷标记已删除: " + mark + "\n");
    }
    else {
        // 添加快捷标记：mark <标记> <路径>
        if (tokens.size() < 3) {
            showError("用法: mark <标记> <路径>");
            return;
        }

        std::string mark = tokens[1];
        std::string path = tokens[2];

        // 检查路径是否存在
        if (!fs_core.pathExists(path)) {
            showError("路径不存在: " + path);
            return;
        }

        // 添加快捷标记
        shortcuts[mark] = path;
        saveShortcuts();
        appendOutput("快捷标记已设置: " + mark + " -> " + path + "\n");
        appendOutput("提示: 现在可以使用 'cd ${" + mark + "}' 或 'cd ${" + mark +
            "}/子目录' 跳转目录\n");
    }
}

// 处理 run 命令：运行exe文件
void CMDManager::handleRun(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        showError("用法: run <exe文件路径>");
        return;
    }

    std::string exePath = tokens[1];

    // 检查文件是否存在
    if (!fs_core.pathExists(exePath)) {
        showError("exe文件不存在: " + exePath);
        return;
    }

    // 检查是否为exe文件
    std::string extension;
    size_t dotPos = exePath.find_last_of('.');
    if (dotPos != std::string::npos) {
        extension = exePath.substr(dotPos + 1);
        std::transform(extension.begin(), extension.end(), extension.begin(),
            ::tolower);
    }

    if (extension != "exe") {
        showError("只支持运行exe文件");
        return;
    }

    // 简单地使用system命令运行exe
    std::string command = "\"" + exePath + "\"";
    int result = system(command.c_str());

    if (result == 0 ||
        result == -1) { // system返回-1表示无法执行，但程序可能已经启动
        appendOutput("程序已启动: " + exePath + "\n");
    }
    else {
        showError("启动程序失败: " + exePath);
    }
}

// 处理 open 命令：打开txt文件
void CMDManager::handleOpen(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2) {
        showError("用法: open <txt文件路径>");
        return;
    }

    std::string filePath = tokens[1];

    // 检查文件是否存在
    if (!fs_core.pathExists(filePath)) {
        showError("文件不存在: " + filePath);
        return;
    }

    // 检查是否为txt文件
    std::string extension;
    size_t dotPos = filePath.find_last_of('.');
    if (dotPos != std::string::npos) {
        extension = filePath.substr(dotPos + 1);
        std::transform(extension.begin(), extension.end(), extension.begin(),
            ::tolower);
    }

    if (extension != "txt") {
        showError("只支持打开txt文件");
        return;
    }

    // 简单地使用system命令打开txt文件
    std::string command = "notepad \"" + filePath + "\"";
    int result = system(command.c_str());

    if (result == 0) {
        appendOutput("文件已打开: " + filePath + "\n");
    }
    else {
        showError("打开文件失败: " + filePath);
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

        appendOutput(
            "\n" + FileSystemCore::WideToUTF8(fs_core.getCurrentPath().wstring()) +
            "> ");
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

// === 快捷目录工具函数实现 ===

// 从文件加载快捷目录映射
void CMDManager::loadShortcuts() {
    shortcuts.clear();
    std::ifstream file(SHORTCUTS_FILE);
    if (!file.is_open()) {
        // 文件不存在是正常的，静默跳过
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // 跳过空行和注释行
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // 解析格式：标记=路径
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string mark = line.substr(0, pos);
            std::string path = line.substr(pos + 1);
            // 去除前后空格
            mark.erase(mark.begin(),
                std::find_if(mark.begin(), mark.end(), [](unsigned char ch) {
                    return !std::isspace(ch);
                    }));
            mark.erase(
                std::find_if(mark.rbegin(), mark.rend(),
                    [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
                mark.end());
            path.erase(path.begin(),
                std::find_if(path.begin(), path.end(), [](unsigned char ch) {
                    return !std::isspace(ch);
                    }));
            path.erase(
                std::find_if(path.rbegin(), path.rend(),
                    [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
                path.end());

            if (!mark.empty() && !path.empty()) {
                shortcuts[mark] = path;
            }
        }
    }
    file.close();
}

// 保存快捷目录映射到文件
void CMDManager::saveShortcuts() {
    std::ofstream file(SHORTCUTS_FILE);
    if (!file.is_open()) {
        showError("无法创建快捷目录文件: " + SHORTCUTS_FILE);
        return;
    }

    // 添加文件头注释
    file << "# 快捷目录标记文件\n";
    file << "# 格式: 标记=路径\n";
    file << "# 使用 'mark 标记 路径' 添加快捷方式\n\n";

    // 写入所有快捷标记
    for (const auto& pair : shortcuts) {
        file << pair.first << "=" << pair.second << "\n";
    }

    file.close();
}

// 展开快捷标记：将${标记}替换为实际路径，支持复合路径
std::string CMDManager::expandShortcut(const std::string& token) {
    std::string result = token;
    size_t pos = 0;

    // 查找并替换所有的 ${标记} 模式
    while ((pos = result.find("${", pos)) != std::string::npos) {
        size_t endPos = result.find("}", pos + 2);
        if (endPos != std::string::npos) {
            // 提取标记名
            std::string mark = result.substr(pos + 2, endPos - pos - 2);
            auto it = shortcuts.find(mark);
            if (it != shortcuts.end()) {
                // 替换 ${标记} 为实际路径
                result.replace(pos, endPos - pos + 1, it->second);
                // 更新位置，跳过替换后的内容
                pos += it->second.length();
            }
            else {
                // 标记不存在，跳过这个 ${...}
                pos = endPos + 1;
            }
        }
        else {
            // 没有找到匹配的 }，跳过
            pos += 2;
        }
    }

    return result;
}

#ifndef SE_ERR_DLLNOTFOUND
#define SE_ERR_DLLNOTFOUND 32
#endif