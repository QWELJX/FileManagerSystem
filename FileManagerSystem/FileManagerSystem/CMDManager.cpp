
#include <algorithm>
#include <sstream>
#include <cctype> 
#include "CMDManager.h"
#include "FileManager.h" 
CMDManager::CMDManager(){
    //初始化命令映射
    {
        commandMap["register"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleRgt(tokens);
            };

        commandMap["clear"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleCls(tokens);
            };

        commandMap["cls"] = commandMap["clear"];

        commandMap["back"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleBack(tokens);
            };

        commandMap["b"] = commandMap["back"];

        commandMap["add"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleAdd(tokens);
            };

        commandMap["delete"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleDelete(tokens);
            };

        commandMap["del"] = commandMap["delete"];

        commandMap["goto"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleGoto(tokens);
            };

        commandMap["cd"] = commandMap["goto"];

        commandMap["list"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleSet(tokens);
            };

        commandMap["ls"] = commandMap["list"];

        commandMap["help"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleHelp(tokens);
            };
	}
    
};

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
        this->appendContent("无法识别命令: " + tokens[0] + "\n" + "输入 'help' 查看可用命令\n");
    }
}

void CMDManager::Show() {
    system("cls");
    FileManager::getInstance().Show();//获取实例输出
	/*  std::cout << std::endl << "--------------------------------------------------------------" << std::endl;*///封装再FileManager里了
	this->appendContent(FileManager::getInstance().GetCurrentPath() + "> ");//直接获取实例 不用再判断指针
    this->showContent();
}
void CMDManager::handleRgt(const std::vector<std::string>& tokens) {
    //if (tokens.size() != 2) {
    //    this->appendContent("错误: register 命令多余或缺少参数\n");
    //    return;
    //}
    //std::string name = (tokens[1].length()>5)?tokens[1].substr(0,5):tokens[1];//register name 这个name是文件管理器的名字
    //FileManager* newFm = new FileManager(name);
    //this->setFileManager(newFm);
}
void CMDManager::handleLogin(const std::vector<std::string>& tokens) {
    //if (tokens.size() != 2) {
    //    this->appendContent("错误: login 命令多余或缺少参数\n");
    //    return;
    //}
    //std::string name = (tokens[1].length() > 5) ? tokens[1].substr(0, 5) : tokens[1];//login name 这个name是文件管理器的名字
    //FileManager* newFm = new FileManager(name);
    //this->setFileManager(newFm);
}

void CMDManager::handleCls(const std::vector<std::string>& tokens) {
    if (tokens.size() != 1) {
        this->appendContent("错误: cls 命令有多余参数\n");
        return; 
    }
    this->clearContent();
}
void CMDManager::handleAdd(const std::vector<std::string>& tokens) {

    //if (!m_Fm) {
    //    this->appendContent("错误: CMDManager 未初始化\n");
    //    return;
    //}
    //size_t t = tokens.size();
    //if (t < 2) {
    //    this->appendContent("错误: 缺少名称参数\n");
    //    return;
    //}
    //std::string name = tokens[1];
    //if (t == 2) {
    //    this->m_Fm->handleAdd(name);
    //    return;
    //}
    //else if (t == 3) {
    //    std::string type = tokens[2];
    //    this->m_Fm->handleAdd(name, stringToFileType(type));
    //    return;
    //}
    //else if (t == 4) {
    //    std::string type = tokens[2];
    //    std::string path = tokens[3];
    //    //...
    //    this->m_Fm->handleAdd(name, stringToFileType(type));
    //    return;
    //}
    //else {
    //    this->appendContent("错误: 多余参数\n");
    //    return;
    //}
}
void CMDManager::handleDelete(const std::vector<std::string>& tokens) {
   /* if (tokens.size() >= 4 || tokens.size() <= 1)
    {
        this->appendContent("当前命令不合法，只能有三个参数哦——例如 del name txt\n"); return;
    }
    if (this->m_Fm->handleDelete(tokens));
    else if (tokens.size() == 3) {
        this->appendContent("当前目录没有" + tokens[1] + "." + tokens[2] + "\n");
    }
    else {
        this->appendContent("当前目录没有 文件夹" + tokens[1] + "\n");
    }*/
}
void CMDManager::handleGoto(const std::vector<std::string>& tokens) {
    //if (tokens.size() <= 1) { this->appendContent("当前命令不符合规定"); return; }
    //if (this->m_Fm->handleGoto(tokens)) {
    //    /*std::cout << "已经"; this->setDirectory(tokens[1]);*/
    //    //this->appendContent(this->m_Fm->getNM()->currentNode->m_path);
    //    int x = 1;
    //}
    //else { ; }
}
void CMDManager::handleBack(const std::vector<std::string>& tokens) {
    //if (tokens.size() != 1) {
    //    this->appendContent("错误: back 命令不需要参数\n");  // 修正错误信息
    //    return;  // 添加return
    //}
    //else {
    //    FileNode* T = this->m_Fm->rootNode;
    //    if (T->path == "") {
    //        this->appendContent("已到根目录，无法再后退\n");
    //        return;
    //    }
    //    this->m_Fm->handleBack();
    //    return;
    //}

}
void CMDManager::handleSet(const std::vector<std::string>& tokens) {
    /*if (!m_Fm) {
        this->appendContent("错误: CMDManager 未初始化\n");
        return;
    }
    size_t t = tokens.size();
    if (t < 2) {
        this->appendContent("错误: 缺少权限参数\n");
        return;
    }
    std::string permission = tokens[1];
    if (t == 2) {
        this->m_Fm->handleSet(permission);
        return;
    }
    else {
        this->appendContent("错误: 多余参数\n");
        return;
    }*/
}

void CMDManager::handleHelp(const std::vector<std::string>& tokens) {
    
    this->appendContent("  register <username>                 - 注册用户\n");
	this->appendContent("  login <username>                    - 登录用户\n");
    this->appendContent("  cls/clear                           - 清屏\n");
    this->appendContent("  back/b                              - 返回上级目录\n");
    this->appendContent("  add <name> [<type>] [<path>]        - 添加文件/目录\n");//添加
    this->appendContent("  del/delete <name>/<index> <type>    - 删除\n");
    this->appendContent("  goto/cd <index>                     - 进入目录\n");
    this->appendContent("  set                                 - 设置权限\n");
    this->appendContent("  help                                - 显示帮助\n");
    this->appendContent("  quit                                - 退出程序\n");
}

// 工具函数实现
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
