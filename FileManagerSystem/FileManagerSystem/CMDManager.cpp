#include <algorithm>
#include <sstream>
#include <cctype> 
#include "CMDManager.h"
#include "FileManager.h" 
CMDManager::CMDManager() : m_Fm(nullptr), DIR("") {


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
        this->handleList(tokens);
        };

    commandMap["ls"] = commandMap["list"];

    commandMap["help"] = [this](const std::vector<std::string>& tokens) -> void {
        this->handleHelp(tokens);
        };
};

void CMDManager::Run() {
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
    if (m_Fm) {
        this->m_Fm->Show();
        this->duiQi(4);
    }
    else {
        this->duiQi(20);
    }

    std::cout << std::endl << "--------------------------------------------------" << std::endl;
    this->appendContent(DIR + "> ");
    this->showContent();
}

void CMDManager::handleRgt(const std::vector<std::string>& tokens) {
    if (tokens.size() != 2) {
        this->appendContent("����: register ��������ȱ�ٲ���\n");
        return;
    }
    std::string name = tokens[1];
    this->setDirectory(name);
    FileManager* newFm = new FileManager(name);
    this->setFileManager(newFm);

}

void CMDManager::handleCls(const std::vector<std::string>& tokens) {
    if (tokens.size() != 1) {
        this->appendContent("����: cls �����ж������\n");
        return;  // ���return
    }
    this->clearContent();//asd
}

void CMDManager::handleBack(const std::vector<std::string>& tokens) {
    if (tokens.size() != 1) {
        this->appendContent("����: back �����Ҫ����\n");  // ����������Ϣ
        return;  // ���return
    }

    //// ���ʵ�ʵĺ����߼�
    //if (m_Fm && m_Fm->getNodeManager()) {
    //    m_Fm->getNodeManager()->GoToParent();
    //    m_Fm->getNodeManager()->Refresh();
    //}
}

void CMDManager::handleAdd(const std::vector<std::string>& tokens) {

    if (!m_Fm) {
        this->appendContent("����: CMDManager δ��ʼ��\n");
        return;
    }
    size_t t = tokens.size();
    if (t < 2) {
        this->appendContent("����: ȱ�ٲ���\n");
        return;
    }
    std::string name = tokens[1];
    if (t == 2) {
        this->m_Fm->getNM()->handleAdd(name);
        return;
    }
    else if (t == 3) {
        std::string type = tokens[2];
        this->m_Fm->getNM()->handleAdd(name, stringToFileType(type));
        return;
    }
    else {
        this->appendContent("����: �������\n");
        return;
    }


}

// ����������������ʵ��
void CMDManager::handleDelete(const std::vector<std::string>& tokens) {
    this->appendContent("ɾ�����ܴ�ʵ��\n");
}

void CMDManager::handleGoto(const std::vector<std::string>& tokens) {
    this->appendContent("��ת���ܴ�ʵ��\n");
}

void CMDManager::handleList(const std::vector<std::string>& tokens) {
    /*if (m_Fm && m_Fm->getNodeManager()) {
        m_Fm->getNodeManager()->Refresh();
    }*/
}

void CMDManager::handleHelp(const std::vector<std::string>& tokens) {
    this->appendContent("��������:\n");
    this->appendContent("  register <name>              - ע���ļ�������\n");
    this->appendContent("  cls/clear                    - ����\n");
    this->appendContent("  back/b                       - �����ϼ�Ŀ¼\n");
    this->appendContent("  add <name> <type>            - ����ļ�/Ŀ¼\n");
    this->appendContent("  del/delete <name>/<index>    - ɾ��\n");
    this->appendContent("  goto/cd <index>              - ����Ŀ¼\n");
    this->appendContent("  list/ls                      - ˢ����ʾ\n");
    this->appendContent("  help                         - ��ʾ����\n");
    this->appendContent("  quit                         - �˳�����\n");
}

// ���ߺ���ʵ��
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
void CMDManager::duiQi(size_t t) {
    for (int i = 0; i < t; ++i)
        std::cout << std::endl;
}