//��һ

#pragma once
#include <iostream> 
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
//#include "FileManager.h"
// ʹ��ǰ���������ֱ�Ӱ���������ѭ������
class FileManager;

class CMDManager {
private:
    // ˽�й��캯��
    CMDManager();

    // ��ֹ�����͸�ֵ
    CMDManager(const CMDManager&) = delete;
    CMDManager& operator=(const CMDManager&) = delete;

    FileManager* m_Fm;

    std::unordered_map<std::string,
        std::function<void(const std::vector<std::string>&)>> commandMap;

    std::string CONTENT;
    std::string DIR;

    // �������
    void handleRgt(const std::vector<std::string>& tokens);
    void handleCls(const std::vector<std::string>& tokens);
    void handleBack(const std::vector<std::string>& tokens);
    void handleAdd(const std::vector<std::string>& tokens);
    void handleDelete(const std::vector<std::string>& tokens);
    void handleGoto(const std::vector<std::string>& tokens);
    void handleList(const std::vector<std::string>& tokens);
    void handleHelp(const std::vector<std::string>& tokens);

    // ���ߺ���
    bool isPureNumber(const std::string& str);
    std::string toLower(const std::string& str);  // ����������
    void duiQi(size_t t);
public:
    // ��ȡ����ʵ��
    static CMDManager& getInstance() {
        static CMDManager instance;
        return instance;
    }

    // ԭ�еĹ�������
    void Run();
    void RunCMD(const std::vector<std::string>& tokens);
    void Show();

    //��ȡ�ļ�����
    FileManager* getFileManager() { return this->m_Fm; }
    void setFileManager(FileManager* fm) { this->m_Fm = fm; }

    // ��ȡ��ǰ���ݣ�������ʾ��
    const std::string& getContent() const { return CONTENT; }
    void clearContent() { CONTENT.clear(); }
    void appendContent(const std::string& text) { 
        CONTENT += text;
        int x = 1;
    }
    void showContent() { std::cout << this->getContent(); }

    // ����/��ȡ��ǰĿ¼
    void setDirectory(const std::string& dir) { 
        DIR = dir; 
    }
    const std::string& getDirectory() const { return DIR; }

}; 