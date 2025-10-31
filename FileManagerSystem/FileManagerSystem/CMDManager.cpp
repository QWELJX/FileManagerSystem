
#include <algorithm>
#include <sstream>
#include <cctype> 
#include "CMDManager.h"
#include "FileManager.h" 

#pragma region ���캯��
CMDManager::CMDManager():CONTENT("") {
    //��ʼ������ӳ��
    {

        commandMap["clear"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleCls(tokens);
            };

        commandMap["cls"] = commandMap["clear"];

        commandMap["back"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleBack(tokens);
            };

        commandMap["b"] = commandMap["back"];

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

        commandMap["list"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleSet(tokens);
            };

        commandMap["ls"] = commandMap["list"];

        commandMap["help"] = [this](const std::vector<std::string>& tokens) -> void {
            this->handleHelp(tokens);
            };
    }

};
#pragma endregion



void CMDManager::Run() {
    this->appendContent("���� help �鿴����\n");
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
        this->appendContent("�޷�ʶ������: " + tokens[0] + "\n" + "���� 'help' �鿴��������\n");
    }
}

void CMDManager::Show() {
    system("cls");
    FileManager::getInstance().Show();
	this->appendContent(FileManager::getInstance().GetCurrentPath() + "> ");//ֱ�ӻ�ȡʵ�� �������ж�ָ��
    this->showContent();
}

#pragma region ����

void CMDManager::handleCls(const std::vector<std::string>& tokens) {
    if (tokens.size() != 1) {
        this->appendContent("����: cls �����ж������\n");
        return;
    }
    this->clearContent();
}
void CMDManager::handleBack(const std::vector<std::string>& tokens) {
    //if (tokens.size() != 1) {
    //    this->appendContent("����: back �����Ҫ����\n");  // ����������Ϣ
    //    return;  // ���return
    //}
    //else {
    //    FileNode* T = this->m_Fm->rootNode;
    //    if (T->path == "") {
    //        this->appendContent("�ѵ���Ŀ¼���޷��ٺ���\n");
    //        return;
    //    }
    //    this->m_Fm->handleBack();
    //    return;
    //}

}
void CMDManager::handleMkdir(const std::vector<std::string>& tokens) {
    size_t t = tokens.size();
    if (t < 2) {
        this->appendContent("����: ȱ�����Ʋ���\n");
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
        this->appendContent("����: �������\n");
        return;
    }
}
void CMDManager::HandleCreateFile(const std::vector<std::string>& tokens) {

}
void CMDManager::handleDelete(const std::vector<std::string>& tokens) {
   /* if (tokens.size() >= 4 || tokens.size() <= 1)
    {
        this->appendContent("��ǰ����Ϸ���ֻ������������Ŷ�������� del name txt\n");return;
    }
    if (this->m_Fm->handleDelete(tokens));
    else if (tokens.size() == 3) {
        this->appendContent("��ǰĿ¼û��" + tokens[1] + "." + tokens[2] + "\n");
    }
    else {
        this->appendContent("��ǰĿ¼û�� �ļ���" + tokens[1] + "\n");
    }*/
}

void CMDManager::handleGoto(const std::vector<std::string>& tokens) {
  /*  if (tokens.size() <= 1) { this->appendContent("��ǰ������Ϲ涨"); return; }
	else if (tokens.size() >= 3) { this->appendContent("��ǰ�������ֻ��2��"); return; }
	m_Fm->handleGoto(tokens[1]);*/
   
}
void CMDManager::handleSet(const std::vector<std::string>& tokens) {
    
}
void CMDManager::handleHelp(const std::vector<std::string>& tokens) {

    this->appendContent("  register <username>                 - ע���û�\n");
    this->appendContent("  login <username>                    - ��¼�û�\n");
    this->appendContent("  cls/clear                           - ����\n");
    this->appendContent("  back/b                              - �����ϼ�Ŀ¼\n");
    this->appendContent("  add <name> [<type>] [<path>]        - ����ļ�/Ŀ¼\n");//���
    this->appendContent("  del/delete <name>/<index> <type>    - ɾ��\n");
    this->appendContent("  goto/cd <index>                     - ����Ŀ¼\n");
    this->appendContent("  set                                 - ����Ȩ��\n");
    this->appendContent("  help                                - ��ʾ����\n");
    this->appendContent("  quit                                - �˳�����\n");
}
#pragma endregion

#pragma region �ӿڷ�װ
const std::string& CMDManager::getContent() const { return CONTENT; }
void CMDManager::clearContent() { CONTENT.clear(); }
void CMDManager::appendContent(const std::string& text) { CONTENT += text; }
void CMDManager::showContent() { std::cout << this->getContent(); }
#pragma endregion

// ���ߺ���ʵ��
#pragma region ����
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


