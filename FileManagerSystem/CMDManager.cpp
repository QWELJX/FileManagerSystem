
#include <algorithm>
#include <sstream>
#include <cctype> 
#include "CMDManager.h"
#include "FileManager.h" 

#pragma region 构造函数
CMDManager::CMDManager():CONTENT("") {
    //初始化命令映射
    {

        commandMap["clear"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleCls(tokens);
            };

        commandMap["cls"] = commandMap["clear"];

        commandMap["mkdir"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleMkdir(tokens);
            };

		commandMap["md"] = commandMap["mkdir"];
        commandMap["create"] = [this](const std::vector<std::string>& tokens) -> void {
            this->HandleCreateFile(tokens);
            };
        commandMap["touch"] = commandMap["create"];

        commandMap["delete"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleDelete(tokens);
            };

        commandMap["del"] = commandMap["delete"];

        commandMap["goto"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleGoto(tokens);
            };

        commandMap["cd"] = commandMap["goto"];

        commandMap["dir"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleDir(tokens);
            };


        commandMap["help"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleHelp(tokens);
            };

		commandMap["move"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleMove(tokens);
			};
        
		commandMap["mov"] = commandMap["move"];
    }

};
#pragma endregion



void CMDManager::Run() {
    this->appendContent("输入 help 查看帮助\n");
    while (true) {
        this->Show();
        std::string content;
        std::getline(std::cin, content);
        this->appendContent(content + "\n");

        std::stringstream ss(content);
        std::vector<std::string> tokens;
        std::string token;

        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            continue;
        }
        else if (tokens[0] == "quit") {
            break;
        }
        this->RunCMD(tokens);
    }
}

void CMDManager::RunCMD(const std::vector<std::string>& tokens) {
    std::string command = toLower(tokens[0]);
    auto it = commandMap.find(command);
    if (it != commandMap.end()) {
        it->second(tokens);
    }
    else {
        this->appendContent("\033[31m无法识别命令: \"" + tokens[0] + "\" 请输入 'help' 查看可用命令\033[0m\n");
    }
}

void CMDManager::Show() {
    system("cls");
    FileManager::getInstance().Show();
	this->appendContent(FileManager::getInstance().GetCurrentPath() + "> ");//直接获取实例 不用再判断指针
    this->showContent();
}

#pragma region 函数

void CMDManager::handleCls(const std::vector<std::string>& tokens) {
    if (tokens.size() != 1) {
        this->appendContent("\033[31m错误: cls 命令有多余参数 \033[0m\n");
        return;
    }
    this->clearContent();
}

void CMDManager::handleMkdir(const std::vector<std::string>& tokens) {
    size_t t = tokens.size();
    if (t < 2) {
        this->appendContent("\033[31m错误: 缺少名称参数\033[0m\n");
        return;
    }
    std::string name = tokens[1];
    if (t == 2) {
        FileManager::getInstance().handleMkdir(name);
        return;
    }
    else if (t == 3) {
        std::string path = tokens[2];
        FileManager::getInstance().handleMkdir(name,path);
        return;
    }
    else {
        this->appendContent("\033[31m错误: md多余参数->["+tokens[3] + "" + "\033[0m\n");
        return;
    }
}
void CMDManager::HandleCreateFile(const std::vector<std::string>& tokens) {
    size_t t = tokens.size();
    if (t < 2) {
        this->appendContent("\033[31m错误: create缺少名称参数\033[0m\n");
        return;
    }
    std::string name = tokens[1];
    if (t == 2) {
        FileManager::getInstance().HandleCreateFile(PathUtils::getStem(name),PathUtils::getExtension(name));
        return;
    }
    else if (t == 3) {
        std::string path = tokens[2];
        FileManager::getInstance().HandleCreateFile(PathUtils::getStem(name), PathUtils::getExtension(name), path);
        return;
	}
    else {
        this->appendContent("\033[31m错误: 多余参数\033[0m\n");
        return;
    }
}
void CMDManager::handleDelete(const std::vector<std::string>& tokens) {
    size_t t = tokens.size();
    if (t < 2) {
        this->appendContent("\033[31m错误: Delete缺少名称参数\033[0m\n");
        return;
    }
    std::string path = tokens[1];
    if (t == 2) {
        FileManager::getInstance().handleDelete(path);   
	    return;      
    }
    else {
        this->appendContent("\033[31m错误: 多余参数\033[0m\n");
        return;
    }
}

void CMDManager::handleGoto(const std::vector<std::string>& tokens) {
    if (tokens.size() <= 1) { this->appendContent("\033[31mcd 缺少参数\033[0m\n"); return; }
	else if (tokens.size() >= 3) { this->appendContent("\033[31mcd 多余参数\033[0m\n"); return; }
	FileManager::getInstance().handleGoto(tokens[1]);
   
}
void CMDManager::handleDir(const std::vector<std::string>& tokens) {
    
}
void CMDManager::handleHelp(const std::vector<std::string>& tokens) {
	this->appendContent("  create <name> [path]                - 添加文件\n");
    this->appendContent("  cls/clear                           - 清屏\n");
    this->appendContent("  md <name> [path]                    - 添加目录\n");//添加
    this->appendContent("  del/delete <name>                   - 删除\n");
    this->appendContent("  goto/cd <name>                      - 进入目录\n");
    this->appendContent("  help                                - 显示帮助\n");
    this->appendContent("  quit                                - 退出程序\n");
	this->appendContent("  move/mov <oldPath> <newPath>            - 移动文件或文件夹\n");
}
void CMDManager::handleMove(const std::vector<std::string>& tokens) {
    if (tokens.size() <= 1) { this->appendContent("\033[31mmove 缺少参数\033[0m\n"); return; }
    else if (tokens.size() >= 4) { this->appendContent("\033[31mmove 多余参数\033[0m\n"); return; }
    FileManager::getInstance().handleMove(tokens[1], tokens[2]);

}
#pragma endregion

#pragma region 接口封装
const std::string& CMDManager::getContent() const { return CONTENT; }
void CMDManager::clearContent() { CONTENT.clear(); }
void CMDManager::appendContent(const std::string& text) { CONTENT += text; }
void CMDManager::showContent() { std::cout << this->getContent(); }
#pragma endregion

// 工具函数实现
#pragma region 工具
bool CMDManager::isPureNumber(const std::string& str) {
    return !str.empty() &&
        std::all_of(str.begin(), str.end(),
            [](char c) { return std::isdigit(static_cast<unsigned char>(c)); });
}

std::string CMDManager::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}
void CMDManager::nl(int t) {
    for (int i = 0; i < t; ++i)
        std::cout << std::endl;
}
#pragma endregion


